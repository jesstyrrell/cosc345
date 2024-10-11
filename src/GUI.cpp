#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "Card.hpp"
#include "Player.hpp"
#include "GUI.hpp"
#include "Game.hpp"
#include "CSVWorker.hpp"

// Define and initialize the static member variable
Game* GUI::game = nullptr;

const Point GUI::PLAYER_CARD_POSITIONS[8][2] = {
    { {96, 39}, {104, 39} },
    { {30, 37}, {38, 37} },
    { {10, 24}, {18, 24} },
    { {30, 8}, {38, 8} },
    { {97, 2}, {105, 2} },
    { {164, 8}, {172, 8} },
    { {186, 24}, {194, 24} },
    { {164, 37}, {172, 37} },
};
const Point GUI::COMMUNITY_CARD_POSITIONS[5] = { {84, 23}, {92, 23}, {100, 23}, {108, 23}, {116, 23} };
const Point GUI::PLAYER_NAME_POSITIONS[8] = { {104, 46}, {54, 39}, {32, 26}, {54, 10}, {104, 9}, {154, 10}, {175, 26}, {154, 39} };
const Point GUI::PLAYER_CURRENT_BETS[8] = { {104, 36}, {62, 34}, {50, 26}, {62, 17}, {104, 15}, {146, 17}, {158, 26}, {146, 34} };
const Point GUI::PLAYER_BUTTON_POSITIONS[8] = { {112, 36}, {68, 36}, {50, 28}, {54, 18}, {94, 15}, {138, 15}, {158, 24}, {152, 32} };
const Point GUI::PLAYER_EQUITY_POSITION[2] = {{10, 10}, {10, 11}};

void GUI::setGame(Game* game) {
    GUI::game = game;
}

Game& GUI::getGame() {
    return *GUI::game;
}

string getFileContents(string filePath) {
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

void moveTo(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

/**
 * Get user move from the terminal
 */
string GUI::getUserMove(bool canCheck, bool canRaise, bool canFold, bool canCall) {
    // Get user move 
    // TODO: Test input validation

    // Create message to user based on possible actions
    // TODO: format nicely
    string message = "";
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
    if (message.length() >= 2 && message.substr(0, 2) == ", ") {
        message = message.substr(2);
    }
    message = "Enter your move: (" + message + ") ";


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
    clearScreen();
    std::cout << title << std::endl;
    std::cout << "--------------------------------" << std::endl;
}

string GUI::getFilePathStart(){
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

    clearScreen();

    string startPath = GUI::getFilePathStart();

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
            moveTo(0, 0);
        }
    }
    displayStartScreen();

    //std::cout << imageASCII << std::endl;
    std::cout << "--------------------------------" << std::endl;
}

MenuOption GUI::displayMenu() {
    vector<string> acceptedInputs = {"", "p", "q", "1", "2", "3", "r"};

    std::cout << "1. Start Game (press Enter)" << std::endl;
    std::cout << "2. View rules (r)" << std::endl;
    std::cout << "3. Quit (q)" << std::endl;

    std::string input;
    std::getline(std::cin, input);  // Read the entire line, allowing us to detect Enter

    // While the user input is not in acceptedInputs, prompt the user for a valid input
    while (std::find(acceptedInputs.begin(), acceptedInputs.end(), input) == acceptedInputs.end()) {
        std::cout << "Invalid input. Please enter a valid option: ";
        std::getline(std::cin, input);  // Use getline to capture the next input
    }

    // Handle the user input
    switch (input[0]) {
        case 'q':
            return QUIT;
        case '3':
            return QUIT;
        case 'r':
            return GUI::displayRules();
        case '2':
            return GUI::displayRules();
        default:
            return START_GAME;
    }
}

MenuOption GUI::displayRules(){
    string startPath = GUI::getFilePathStart();
    string rulesPath = startPath + "/images/pokerTutorial.txt";

   string rules = getFileContents(rulesPath);

   cout << rules + "\n" << endl;
    cout << "Press Enter to return to the main menu" << endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // clear the screen
    clearScreen();
    // display the start screen
    displayStartScreen();
    MenuOption m = GUI::displayMenu();
    return m;

}

int GUI::getNumberOfPlayers() {
    std::cout << "Enter the number of players: ";

    int numPlayers;

    // Asking the user for the number of players - bounded between 2 and 8
    do {
        std::cin >> numPlayers;

        // Check if the input is valid
        if (std::cin.fail() || numPlayers < 2 || numPlayers > 8) {
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a number between 2 and 8: ";
        }
    } while (numPlayers < 2 || numPlayers > 8);

    return numPlayers;
}

int GUI::getBotDifficulty() {
    std::cout << "Enter the bot difficulty (1, 2, or 3): ";

    int difficulty;

    // Asking the user for the number of players - bounded between 2 and 8
    do {
        std::cin >> difficulty;

        // Check if the input is valid
        if (std::cin.fail() || difficulty < 1 || difficulty > 3) {
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a number between 1 and 3: ";
        }
    } while (difficulty < 1 || difficulty > 3);

    return difficulty;
}

PlayerProfile GUI::signInMenu() {
    enum MenuOption { SIGN_IN = 1, CREATE_PROFILE, PLAY_AS_GUEST };
    const std::vector<std::string> acceptedInputs = {"1", "2", "3"};

    std::cout << "Select one of the following options:" << std::endl;
    std::cout << "1. Sign in with a name" << std::endl;
    std::cout << "2. Create profile" << std::endl;
    std::cout << "3. Play as guest" << std::endl;

    std::string input;
    do {
        std::getline(std::cin, input);
        if (std::find(acceptedInputs.begin(), acceptedInputs.end(), input) == acceptedInputs.end()) {
            std::cout << "Invalid input. Please enter a valid option: ";
        }
    } while (std::find(acceptedInputs.begin(), acceptedInputs.end(), input) == acceptedInputs.end());

    MenuOption choice = static_cast<MenuOption>(std::stoi(input));

    switch (choice) {
        case SIGN_IN: {
            std::string name;
            std::cout << "Enter your name: ";
            std::getline(std::cin, name);
            return GUI::getProfile(name);
        }

        case CREATE_PROFILE:
            return GUI::createProfile();

        case PLAY_AS_GUEST: {
            std::string guestName;
            std::cout << "Enter a name for guest play: ";
            std::getline(std::cin, guestName);
            PlayerProfile *temp = new PlayerProfile({guestName});
            temp->isGuest = true;
            return *temp;
        }

        default:
            throw std::runtime_error("Unexpected menu option");
    }
}

int GUI::endOfRoundMenu() {
    std::cout << "1. Continue (enter)" << std::endl;
    std::cout << "2. Main menu (m)" << std::endl;
    std::cout << "3. Quit (q)" << std::endl;

    std::string input;
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::getline(std::cin, input);  // Read the entire line, allowing us to detect Enter

    while (input != "q" && input != "" && input != "m" && input != "1" && input != "2" && input != "3") {
        std::cout << "Invalid input. Please enter a valid option: ";
        std::getline(std::cin, input);  // Use getline to capture the next input
    }

    if (input == "q" || input == "3") {
        return 0;
    }
    if(input == "m" || input == "2"){
        return 2;
    }
    return 1;
}

void GUI::displayPlayerStack(Player* player) {
    std::cout << player->get_name() << "'s stack: " << player->get_stack() << std::endl;
    std::cout << "    -----    " << std::endl;
}

string addString(string baseString, string newString, int x1, int y1) {
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


string getCardString(Card& card) {
    string suit = card.get_suit();
     
    string rank = card.get_rank();
     
    string startPath = GUI::getFilePathStart();
   
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

void GUI::displayGameState() {
    Game game = getGame();
    vector<Player*> players = game.getPlayers();
    vector<Card> communityCards = game.getCommunityCards();
    int button = game.getButton();

    moveTo(0, 0);
    // TODO: Implement this method, will be called as each hand progresses and display 
    // table, chips, cards, stack sizes, players names, etc.

    // Get the contents of the table.txt file and print it to the terminal
    string startPath = GUI::getFilePathStart();
    string tablePath = startPath + "/images/table.txt";

    string tableContent = getFileContents(tablePath);

    string buttonPath = startPath + "/images/button.txt";
    string buttonString = getFileContents(buttonPath);
  
    
    for(int i = 0; i < communityCards.size(); i++){
        string cardContent = getCardString(communityCards[i]);
        tableContent = addString(tableContent, cardContent, COMMUNITY_CARD_POSITIONS[i].x, COMMUNITY_CARD_POSITIONS[i].y);
    }

    tableContent = addString(tableContent, "Pot: " + std::to_string(game.getPot()), 103 - (std::to_string(game.getPot()).length() + 5)/2, 21);

    int numPlayers = players.size();
    int seatStep = 8 / numPlayers;

    for(int i = 0; i < numPlayers; i++){
        tableContent = addString(tableContent, players[i]->get_name(), PLAYER_NAME_POSITIONS[i * seatStep].x - players[i]->get_name().length()/2, PLAYER_NAME_POSITIONS[i * seatStep].y);
        tableContent = addString(tableContent, "Stack: " + std::to_string(players[i]->get_stack()), PLAYER_NAME_POSITIONS[i * seatStep].x -((7 + std::to_string(players[i]->get_stack()).length() )/2), PLAYER_NAME_POSITIONS[i * seatStep].y + 2);
         if(players[i]->get_current_bet() != 0){
            tableContent = addString(tableContent, "Bet: " + std::to_string(players[i]->get_current_bet()), PLAYER_CURRENT_BETS[i * seatStep].x -((5 + std::to_string(players[i]->get_current_bet()).length() )/2), PLAYER_CURRENT_BETS[i * seatStep].y);
         }

         if(i == button){
            tableContent = addString(tableContent, buttonString, PLAYER_BUTTON_POSITIONS[i * seatStep].x, PLAYER_BUTTON_POSITIONS[i * seatStep].y);
         }

         if (players[i]->get_hand().size() != 0) {
             string playerCardContent1;
             string playerCardContent2;
             if (i == 0 || game.getShowdown()) {
                playerCardContent1 = getCardString(players[i]->get_hand()[0]);
                playerCardContent2 = getCardString(players[i]->get_hand()[1]);
             }
             else {
                 playerCardContent1 = getFileContents(startPath + "/images/backCard.txt");
                 playerCardContent2 = playerCardContent1;
             }

             // Add the card to the table content
             tableContent = addString(tableContent, playerCardContent1, PLAYER_CARD_POSITIONS[i * seatStep][0].x, PLAYER_CARD_POSITIONS[i* seatStep][0].y);
             tableContent = addString(tableContent, playerCardContent2, PLAYER_CARD_POSITIONS[i * seatStep][1].x, PLAYER_CARD_POSITIONS[i* seatStep][1].y);
         }
         else {
             // Show that they have folded 
         }
    }

    std::cout << tableContent << std::endl;
    moveTo(0, 0);

    
}

void GUI::displayPlayerMove(Player* player, string move, int size) {
    displayGameState();
    if (size != -1) { move += " " + to_string(size); }
    cout << player->get_name() << ": " << move << endl;
}

std::string GUI::getRandomPlayerName() {
    std::string startPath = GUI::getFilePathStart();

    // Get the contents of the adjectives.txt file
    std::string adjectives = getFileContents(startPath + "/images/adjectives.txt");

    // Split the adjective string into lines
    std::vector<std::string> adjectiveList;
    std::stringstream ssAdjectives(adjectives);
    std::string adjective;
    while (std::getline(ssAdjectives, adjective)) {
        adjectiveList.push_back(adjective);
    }

    // Get the contents of the animals.txt file
    std::string animals = getFileContents(startPath + "/images/animals.txt");

    // Split the animals string into lines
    std::vector<std::string> animalList;
    std::stringstream ssAnimals(animals);
    std::string animal;
    while (std::getline(ssAnimals, animal)) {
        animalList.push_back(animal);
    }

    // Initialize random number generator statically so it's only seeded once
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(static_cast<unsigned long>(seed));  // Seeding the generator


    // Randomly pick an adjective and animal from the lists
    std::uniform_int_distribution<> distrAdjective(0, adjectiveList.size() - 1);
    std::string randomAdjective = adjectiveList[distrAdjective(gen)];

    std::uniform_int_distribution<> distrAnimal(0, animalList.size() - 1);
    std::string randomAnimal = animalList[distrAnimal(gen)];

    return randomAdjective + randomAnimal;
}

void GUI::optionToViewStats(PlayerProfile player){
    // either display stats or return 
     std::cout << "Do you want to view your statistics? (y/n): ";

    string decision;
    // Asking the user for y/n
    do {
        std::cin >> decision;

        // Check if the input is valid
        if (decision != "y" && decision != "n") {
            std::cout << "Invalid input. Please enter y or n: ";
        }
    } while (decision != "y" && decision != "n");
    if(decision == "y"){
        displayPlayerStats(player);
    }
    return;
}

void GUI::displayPlayerStats(PlayerProfile player){
    if(player.totalHandsPlayed == 0){
        std::cout << "No hands played yet! Play some hands to view your statistics <3" << std::endl;
        return;
    }
    std::cout << "Name: " << player.name << std::endl;
    std::cout << "Total hands played: " << player.totalHandsPlayed << "\n" << std::endl;

    if(player.numHandsEasy != 0){
        std::cout << "Easy hands played: " << player.numHandsEasy << std::endl;
        std::cout << "Easy PnL per 100 hands: " << (player.easyPnl / player.numHandsEasy)*100.0 << "\n" <<std::endl;
    } else {
        std::cout << "No easy hands played" << "\n" << std::endl;
    }

    if(player.numHandsMedium != 0){
        std::cout << "Medium hands played: " << player.numHandsMedium << std::endl;
        std::cout << "Medium PnL per 100 hands: " << (player.mediumPnl / player.numHandsMedium)*100.0 << "\n" << std::endl;
    } else {
        std::cout << "No medium hands played" << "\n" << std::endl;
    }

    if(player.numHandsHard != 0){
        std::cout << "Hard hands played: " << player.numHandsHard << std::endl;
        std::cout << "Hard PnL per 100 hands: " << (player.hardPnl / player.numHandsHard)*100.0 << "\n" << std::endl;
    } else {
        std::cout << "No hard hands played" << "\n" << std::endl;
    }

    std::cout << "VPIP: " << player.numHandsVpip/player.totalHandsPlayed << std::endl;
    

    return;
}


PlayerProfile GUI::createProfile() {
    string startPath = GUI::getFilePathStart();
    CSVWorker csv(startPath + "/data/profiles.csv");

    // Check if a profile exists in the CSV file
    std::string name;
    int age;

    std::cout << "Enter your name: ";
    std::cin >> name;


    PlayerProfile playerProfile = { name };
    csv.readProfiles();
    csv.addProfile(playerProfile);
    csv.writeProfiles();

    return playerProfile;
}

PlayerProfile GUI::getProfile(const std::string& name) {
    string startPath = GUI::getFilePathStart();
    CSVWorker csv(startPath + "/data/profiles.csv");
    // Get the user's profile that has the name entered
    for (PlayerProfile profile : csv.readProfiles()) {
        if (profile.name == name) {
            return profile;
        }
    }

    cout << "Profile not found." << endl;
    return signInMenu();
}