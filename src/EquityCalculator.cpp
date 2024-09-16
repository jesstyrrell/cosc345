#include "EquityCalculator.hpp"

using namespace std;

EquityCalculator::EquityCalculator() {

}

string getFileStartPath() {
	// Get os type
#ifdef _WIN32
	std::string os = "Windows";
#elif __APPLE__
	std::string os = "MacOS";
#elif __linux__
	std::string os = "Linux";
#else
	std::string os = "Unknown";
#endif

	string startPath;

	if (os == "Windows")
	{
		startPath = "../../..";
	}
	else if (os == "MacOS")
	{
		startPath = "..";
	}
	else if (os == "Linux")
	{
		startPath = "..";
	}
	else
	{
		std::cerr << "Unsupported OS" << std::endl;
		return "";
	}
	return startPath;
}

bool fileExists(const std::string& filename) {
	struct stat buffer;
	return (stat(filename.c_str(), &buffer) == 0);
}

vector<float> findEquity(const std::string& filename, const std::vector<std::string>& searchValues) {
	vector<float> equity;
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return equity;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string field;
		std::vector<std::string> row;

		while (std::getline(ss, field, ',')) {
			row.push_back(field);
		}

		if (row.size() >= 6) {
			bool match = true;
			for (size_t i = 0; i < 4; ++i) {
				if (i >= searchValues.size() || row[i] != searchValues[i]) {
					match = false;
					break;
				}
			}

			if (match) {
				file.close();
				equity.push_back(stof(row[4]));
				equity.push_back(stof(row[5]));
				return equity;
			}
		}
	}

	file.close();
	return equity;
}

vector<float> EquityCalculator::calculateHandEquity(const vector<Card>& hand, const vector<Card>& communityCards, Deck deck, int numPlayers) {
	if (communityCards.size() > 0) {
		return evaluateHand(hand, communityCards, deck, numPlayers);
	}

	if (!fileExists(getFileStartPath() + "/preflopEquity.csv")) { buildPreflopEquityCSV(); }

	vector<string> search;
	search.push_back(hand[0].get_rank());
	search.push_back(hand[1].get_rank());
	search.push_back(hand[0].get_suit() == hand[1].get_suit() ? "true" : "false");
	search.push_back(to_string(numPlayers));

	return findEquity(getFileStartPath() + "/preflopEquity.csv", search);
}

vector<float> EquityCalculator::evaluateHand(const vector<Card>& hand, const vector<Card>& communityCards, Deck deck, int numPlayers) {

	int iterations = 0;
	double timeToCalculate = 1 * 1000000000; // 1 second in nano seconds
	auto start = std::chrono::high_resolution_clock::now();

	int wins = 0;
	int draws = 0;
	int losses = 0;
	while (true) {

		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::nano> elapsed = now - start;
 		double num = elapsed.count();
		if (elapsed.count() > timeToCalculate) { break; }

		iterations++;
		bool lose = false;
		bool draw = false;
		Deck deckCopy(deck);
		deckCopy.shuffle();
		vector<Card> communityCardsFull(communityCards);
		while (communityCardsFull.size() < 5) {
			communityCardsFull.push_back(deckCopy.deal());
		}
		for (int player = 0; player < numPlayers; player++) {
			if (lose) { continue; }
			// create random hand for opponent
			vector<Card> otherHand;
			for (int i = 0; i < 2; i++) { otherHand.push_back(deckCopy.deal()); }
			// check if we beat opponent's hand
			int outcome = handEvaluator.compareHands(hand, otherHand, communityCardsFull);
			lose = outcome == LOSE;
			if (!draw) {
				draw = outcome == DRAW;
			}
		}
		if (lose) { losses++; continue; }
		if (draw) { draws++; continue; }
		wins++;
	}

	return { 1.0f * wins / iterations, 1.0f * draws / iterations,  1.0f * (iterations - (wins + draws)) / iterations };
}

void EquityCalculator::buildPreflopEquityCSV() {
	// Define the suits and ranks
	vector<string> suits = { "Hearts", "Diamonds", "Clubs", "Spades" };
	vector<string> ranks = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
	int maxPlayers = 2;

	// Vector to hold all cards
	vector<Card> communityCards;

	EquityCalculator equityCalculator;

	Deck deck;

	int totalHands = 169;
	double currentHand = 0;

	// Open a CSV file for writing
	ofstream outFile(getFileStartPath() + "/preflopEquity.csv");
	if (!outFile) {
		cerr << "Error opening file for writing." << endl;
		return;
	}
	outFile << "FirstCardRank,SecondCardRank,suited,players,winEquity,drawEquity" << endl;
	
	// calculate pocket pairs
	for (string rank : ranks) {
		vector<Card> hand;
		hand.emplace_back(suits[0], rank);
		hand.emplace_back(suits[1], rank);
		Deck deckCopy(deck);
		deckCopy.remove_card(hand[0]);
		deckCopy.remove_card(hand[1]);
		for (int p = 2; p <= maxPlayers; p++) {
			vector<float> result = equityCalculator.evaluateHand(hand, communityCards, deckCopy, p);
			
			// Save results to CSV file
			outFile << rank << ","
				<< rank << ","
				<< "false" << ","
				<< p << ","
				<< result[0] << ","
				<< result[1] << endl;
		}
		currentHand++;
		cout << 100 * currentHand / totalHands << "%" << endl;
	}

	// calculate suited hands
	for (int i = 0; i < ranks.size(); i++) {
		for (int j = i+1; j < ranks.size(); j++) {
			string rank1 = ranks[i];
			string rank2 = ranks[j];
			vector<Card> hand;
			hand.emplace_back(suits[0], rank1);
			hand.emplace_back(suits[0], rank2);
			Deck deckCopy(deck);
			deckCopy.remove_card(hand[0]);
			deckCopy.remove_card(hand[1]);
			for (int p = 2; p <= maxPlayers; p++) {
				vector<float> result = equityCalculator.evaluateHand(hand, communityCards, deckCopy, p);

				// Save results to CSV file
				outFile << rank1 << ","
					<< rank2 << ","
					<< "true" << ","
					<< p << ","
					<< result[0] << ","
					<< result[1] << endl;
				outFile << rank2 << ","
					<< rank1 << ","
					<< "true" << ","
					<< p << ","
					<< result[0] << ","
					<< result[1] << endl;
			}
			currentHand++;
			cout << 100 * currentHand / totalHands << "%" << endl;
		}
	}

	// calculate non-suited hands
	for (int i = 0; i < ranks.size(); i++) {
		for (int j = i + 1; j < ranks.size(); j++) {
			string rank1 = ranks[i];
			string rank2 = ranks[j];
			vector<Card> hand;
			hand.emplace_back(suits[0], rank1);
			hand.emplace_back(suits[1], rank2);
			Deck deckCopy(deck);
			deckCopy.remove_card(hand[0]);
			deckCopy.remove_card(hand[1]);
			for (int p = 2; p <= maxPlayers; p++) {
				vector<float> result = equityCalculator.evaluateHand(hand, communityCards, deckCopy, p);

				// Save results to CSV file
				outFile << rank1 << ","
					<< rank2 << ","
					<< "false" << ","
					<< p << ","
					<< result[0] << ","
					<< result[1] << endl;
				outFile << rank2 << ","
					<< rank1 << ","
					<< "false" << ","
					<< p << ","
					<< result[0] << ","
					<< result[1] << endl;
			}
			currentHand++;
			cout << 100 * currentHand / totalHands << "%" << endl;
		}
	}

}
