#include "Card.hpp"
#include "Player.hpp"
#include "GUI.hpp"
#include "Game.hpp"

// Define and initialize the static member variable
Game* GUI::game = nullptr;

const Point GUI::PLAYER_CARD_POSITIONS[2] = {{92, 32}, {100, 32}};
const Point GUI::COMMUNITY_CARD_POSITIONS[5] = {{80, 16}, {88, 16}, {96, 16}, {104, 16}, {112, 16}};
const Point GUI::PLAYER_NAME_POSITIONS[8] = {{100, 39}, {50,32}, {28, 19}, {50, 3}, {100, 2}, {150, 3}, {171, 19}, {150,32}};

void GUI::setGame(Game* game) {
    GUI::game = game;
}

Game& GUI::getGame() {
    return *GUI::game;
}

/**
 * Clear the terminal screen
 */
void GUI::clearScreen() {
    // Check the os of the user 
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * Get user move from the terminal
 */
string GUI::getUserMove(bool canCheck, bool canRaise, bool canFold, bool canCall) {
    // Get user move 
    // TODO: Test input validation

    // Create message to user based on possible actions
    // TODO: format nicely
    string message = "Enter your move: (";
    if (canFold) {
        message += "fold = f";
    }
    if (canCall) {
        message += ", call = c";
    }
    if (canCheck) {
        message += ", check = a";
    }
    if (canRaise) {
        message += ", raise = r";
    }
    message += ") ";


    std::string move; 
    std::cout << message; // instead of this we would call display game state which auto adds message 
    std::cin >> move; 
    while((move == "f" && !canFold) || 
          (move == "a" && !canCheck) || 
          (move == "c" && !canCall) || 
          (move == "r" && !canRaise) ||
          (move != "f" && move != "a" && move != "c" && move != "r")) {
        std::cout << "Invalid move. Please enter a valid move: "; // Chnage message to this 
        std::cin >> move; 
    }

    return move; 
}

/**
 * Get user bet sizing from the terminal
 * 
 * @param minBet: int - Minimum bet size
 * @param maxBet: int - Maximum bet size
 */

int GUI::getBetSizing(int minBet, int maxBet) {
    // Get user bet size
    // TODO: Test bet sizing input validation
    int bet_sizing; 
    std::cout << "Enter your bet sizing: ";
    while (true) {
        std::cin >> bet_sizing;

        // Check if the input is valid
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a valid integer bet size: ";
            continue;
        }

        // Check if the bet is within the valid range
        if (bet_sizing >= minBet && bet_sizing <= maxBet) {
            break; // Valid bet size
        }

        std::cout << "Invalid bet size. Please enter a bet size between " << minBet << " and " << maxBet << ": ";
    }

    return bet_sizing;
}

/** 
 * Display community cards to the terminal
 * 
 * @param community_cards: vector<Card> - Community cards to display
 */
void GUI::displayCommunityCards(const std::vector<Card>& community_cards) {
    // Display community cards
    for (Card card : community_cards) {
        std::cout << card.get_rank() << " of " << card.get_suit() << std::endl;
    }
}   

/** 
 * Display all player hands to the terminal
 * 
 * @param players: vector<Player*> - Players to display hands for
 */
void GUI::displayAllPlayerHands(const std::vector<Player*>& players) {
    for (Player* player : players) {
        std::cout << player->get_name() << "'s hand: " << std::endl;
        for (Card& card : player->get_hand()) {
            std::cout << card.get_rank() << " of " << card.get_suit() << std::endl;
        }
        std::cout << "--------------" << std::endl;
    }
}

/** 
 * Display a player's hand to the terminal 
 * 
 * @param player: Player* - Player to display hand for
 */
void GUI::displayPlayerHand(Player* player) {
    std::cout << player->get_name() << "'s hand: " << std::endl;
    for (Card card : player->get_hand()) {
        std::cout << card.get_rank() << " of " << card.get_suit() << std::endl;
    }
    std::cout << "--------------" << std::endl;
}

void GUI::displayStartScreen() {
    string title = R"(:::::::::  :::    ::: ::::    :::    ::::::::::: :::::::::::    ::::::::::: :::       ::: :::::::::::  ::::::::  :::::::::: 
:+:    :+: :+:    :+: :+:+:   :+:        :+:         :+:            :+:     :+:       :+:     :+:     :+:    :+: :+:        
+:+    +:+ +:+    +:+ :+:+:+  +:+        +:+         +:+            +:+     +:+       +:+     +:+     +:+        +:+        
+#++:++#:  +#+    +:+ +#+ +:+ +#+        +#+         +#+            +#+     +#+  +:+  +#+     +#+     +#+        +#++:++#   
+#+    +#+ +#+    +#+ +#+  +#+#+#        +#+         +#+            +#+     +#+ +#+#+ +#+     +#+     +#+        +#+        
#+#    #+# #+#    #+# #+#   #+#+#        #+#         #+#            #+#      #+#+# #+#+#      #+#     #+#    #+# #+#        
###    ###  ########  ###    ####    ###########     ###            ###       ###   ###   ###########  ########  ########## )";
    std::cout << title << std::endl;
    std::cout << "--------------------------------" << std::endl;
}

string getFilePathStart(){
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

void GUI::displayEndMessage() {

    string startPath = getFilePathStart();

    string imagePath = startPath + "/images/cardAnimation.txt";
    string delimiter = "[END OF FRAME]\n";
    int delay = 25;

    std::ifstream inputFile(imagePath);

    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // Read the file into a string
    std::ostringstream oss;
    oss << inputFile.rdbuf();
    std::string content = oss.str();
    inputFile.close();

    std::vector<std::string> frames;
    size_t start = 0;
    size_t end;

    // Split the frames
    while ((end = content.find(delimiter, start)) != std::string::npos) {
        frames.push_back(content.substr(start, end - start));
        start = end + delimiter.length();
    }
    frames.push_back(content.substr(start)); // Add the last frame

    for (int i = 0; i < 5; i++) {
        // Print each frame with a delay
        for (const std::string& frame : frames) {
            std::cout << frame << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            clearScreen();
        }
    }

    //std::cout << imageASCII << std::endl;
    std::cout << "--------------------------------" << std::endl;
}

int GUI::displayMenu() {
    std::cout << "1. Start Game (press Enter)" << std::endl;
    std::cout << "2. Quit (q)" << std::endl;

    std::string input;
    std::getline(std::cin, input);  // Read the entire line, allowing us to detect Enter

    while (input != "q" && input != "") {
        std::cout << "Invalid input. Please enter a valid option: ";
        std::getline(std::cin, input);  // Use getline to capture the next input
    }

    if (input == "q") {
        return 0;
    }
    return 1;
}


void GUI::displayPlayerStack(Player* player) {
    std::cout << player->get_name() << "'s stack: " << player->get_stack() << std::endl;
    std::cout << "    -----    " << std::endl;
}

string addString(string baseString, string newString, int x1, int y1)
{
    // Split the base string and new string into lines
    vector<string> baseLines;
    vector<string> newLines;
    stringstream ssBase(baseString), ssNew(newString);
    string line;

    while (getline(ssBase, line))
    {
        baseLines.push_back(line);
    }

    while (getline(ssNew, line))
    {
        newLines.push_back(line);
    }

    // Ensure the replacement does not go out of bounds
    for (int i = 0; i < newLines.size(); i++)
    {
        int targetLine = y1 + i;
        if (targetLine < baseLines.size())
        {
            string &baseLine = baseLines[targetLine];
            string &newLine = newLines[i];

            if (x1 < baseLine.size())
            {
                // Replace the part of the line starting from x1 with the new string
                baseLine.replace(x1, newLine.size(), newLine);
            }
            else
            {
                // If x1 is outside the base line, just append the new string
                baseLine.append(string(x1 - baseLine.size(), ' ') + newLine);
            }
        }
    }

    // Recombine the base lines into a single string
    string result;
    for (const string &baseLine : baseLines)
    {
        result += baseLine + "\n";
    }

    return result;
}

string getFileContents(string filePath){
    // Get the contents of the file at the file path
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return "";
    }

    // Read the file into a string
    std::ostringstream oss;
    oss << file.rdbuf();
    std::string content = oss.str();
    file.close();

    return content;
}

string getCardString(Card& card){
    string suit = card.get_suit();
     
    string rank = card.get_rank();
     
    string startPath = getFilePathStart();
   
    string cardPath = startPath + "/images/" + suit + "Card.txt";

    string cardContent = getFileContents(cardPath);

    // Replace a ? with the rank of the card
    int start = 0;

    for(int i = 0; i < 2; i++){
        size_t pos = cardContent.find("?", start);
        if(rank != "10"){
            cardContent.replace(pos, 1, rank);
        } else if(i == 0){
            cardContent.replace(pos, 2, rank);
        }else{
            cardContent.replace(pos-1, 2, rank);
        }
        start = pos + 1;
    }
    return cardContent;
}

void GUI::displayGameState(){

    // clear screen 
    clearScreen();
    // TODO: Implement this method, will be called as each hand progresses and display 
    // table, chips, cards, stack sizes, players names, etc.

    // Get the contents of the table.txt file and print it to the terminal
    string startPath = getFilePathStart();
    string tablePath = startPath + "/images/table.txt";

    string tableContent = getFileContents(tablePath);

    if(getGame().getPlayers()[0]->get_hand().size() != 0){
        string playerCardContent1 = getCardString(getGame().getPlayers()[0]->get_hand()[0]);
        string playerCardContent2 = getCardString(getGame().getPlayers()[0]->get_hand()[1]);

        // Add the card to the table content
        tableContent = addString(tableContent, playerCardContent1, PLAYER_CARD_POSITIONS[0].x, PLAYER_CARD_POSITIONS[0].y);
        tableContent = addString(tableContent, playerCardContent2, PLAYER_CARD_POSITIONS[1].x, PLAYER_CARD_POSITIONS[1].y);
    } else {
    // Show that they have folded 
    }
    // Make a list of the current community cards
    std::vector<Card> communityCards = getGame().getCommunityCards();
    
    for(int i = 0; i < communityCards.size(); i++){
        string cardContent = getCardString(communityCards[i]);
        tableContent = addString(tableContent, cardContent, COMMUNITY_CARD_POSITIONS[i].x, COMMUNITY_CARD_POSITIONS[i].y);
    }

    tableContent = addString(tableContent, "Pot: " + std::to_string(getGame().getPot()), 99 - (std::to_string(getGame().getPot()).length() + 5)/2, 14);

    int numPlayers = getGame().getPlayers().size();
    int seatStep = 8 / numPlayers;

    for(int i = 0; i < numPlayers; i++){
        tableContent = addString(tableContent, getGame().getPlayers()[i]->get_name(), PLAYER_NAME_POSITIONS[i * seatStep].x - getGame().getPlayers()[i]->get_name().length()/2, PLAYER_NAME_POSITIONS[i * seatStep].y);
        tableContent = addString(tableContent, "Stack: " + std::to_string(getGame().getPlayers()[i]->get_stack()), PLAYER_NAME_POSITIONS[i * seatStep].x -(7 + std::to_string(getGame().getPlayers()[i]->get_stack()).length())/2, PLAYER_NAME_POSITIONS[i * seatStep].y + 2);
    }

    std::cout << tableContent << std::endl;

    // If the pot is neg infinite while loop
    if(getGame().getPot() < 0){
        cout << "Pot is negative infinite" << endl;
        while(true){
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
}
