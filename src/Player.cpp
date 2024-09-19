#include <random>

#include "Player.hpp"

using namespace std;

Player::Player(const std::string& name, int stack) {
    this->name = name;
    this->stack = stack;
}

void Player::bet(int amount) {
    if(amount > this->stack + this->current_bet) {
        cout << "You don't have enough chips to bet that amount. Betting all in." << endl;
        cout << amount << endl;
        while(true){}
    }
    this->stack -= amount - this->current_bet;
    this->current_bet = amount;
}

int Player::deduct_blind(int amount) {
    this->stack -= amount;
    this->current_bet = amount;
    return amount;
}

void Player::win(int amount) {
    this->stack += amount;
}

int Player::get_stack() {
    return this->stack;
}

string Player::get_name() {
    return this->name;
}

vector<Card> Player::get_hand() {
    return this->hand;
}

void Player::add_card_to_hand(Card card) {
    this->hand.push_back(card);
}

void Player::clear_hand() {
    this->hand.clear();
}

int Player::get_current_bet() {
    return this->current_bet;
}

void Player::show_hand() {
    for (Card card : hand) {
        cout << card.get_rank() << " of " << card.get_suit() << endl;
    }
}

void Player::reset_current_bet() {
    this->current_bet = 0;
}

string Player::generate_random_name() {
    std::vector<string> animals = {"Dog", "Cat", "Fish", "Bird", "Elephant", "Lion", "Tiger", "Bear", "Penguin", "Panda", "Giraffe", "Horse", "Cow", "Pig", "Sheep", "Goat", "Chicken", "Duck", "Goose", "Turkey", "Ostrich", "Kangaroo", "Koala", "Sloth", "Monkey", "Gorilla", "Chimpanzee", "Orangutan", "Rabbit", "Frog", "Toad", "Turtle", "Snake", "Lizard", "Iguana", "Chameleon", "Alligator", "Crocodile", "Shark", "Whale", "Dolphin", "Octopus", "Squid", "Jellyfish", "Starfish", "Seahorse", "Crab", "Lobster", "Shrimp", "Clam", "Oyster", "Mussel", "Scallop", "Snail", "Slug", "Butterfly", "Moth", "Caterpillar", "Ant", "Bee", "Wasp", "Hornet", "Fly", "Mosquito", "Beetle", "Ladybug", "Grasshopper", "Cricket", "Dragonfly", "Damselfly", "Centipede", "Millipede", "Spider", "Tarantula", "Scorpion", "Tick", "Mite", "Flea", "Bedbug", "Cockroach", "Termite", "Praying Mantis", "Walking Stick", "Earwig", "Silverfish", "Firefly", "Glowworm", "Earthworm", "Leech", "Slug", "Snail", "Clam", "Oyster", "Mussel", "Scallop", "Squid", "Octopus", "Cuttlefish", "Nautilus", "Ammonite", "Trilobite", "Crab", "Lobster", "Shrimp", "Krill", "Barnacle", "Crayfish", "Cockroach", "Termite", "Praying Mantis", "Walking Stick", "Earwig", "Silverfish", "Firefly", "Glowworm", "Earthworm", "Leech", "Slug"};
    std::vector<string> adjectives = {"Happy", "Sad", "Angry", "Excited", "Bored", "Tired", "Energetic", "Lazy", "Calm", "Anxious", "Nervous", "Confident", "Shy", "Brave", "Scared", "Proud", "Embarrassed", "Ashamed", "Guilty", "Jealous", "Envious", "Grateful", "Thankful", "Hopeful", "Hopeless", "Optimistic", "Pessimistic", "Curious", "Inquisitive", "Impatient", "Patient", "Polite", "Rude", "Kind", "Mean", "Generous", "Greedy", "Honest", "Dishonest", "Loyal", "Unfaithful", "Responsible", "Irresponsible", "Reliable", "Unreliable", "Trustworthy", "Untrustworthy", "Fair", "Unfair", "Forgiving", "Unforgiving", "Tolerant", "Intolerant", "Understanding", "Misunderstanding", "Sympathetic", "Unsympathetic", "Empathetic", "Apathetic", "Compassionate", "Heartless", "Caring", "Uncaring", "Affectionate", "Cold", "Warm", "Friendly", "Unfriendly", "Sociable", "Unsociable", "Outgoing", "Shy", "Introverted", "Extroverted", "Optimistic", "Pessimistic", "Cheerful", "Gloomy", "Joyful", "Sorrowful", "Playful", "Serious", "Silly", "Serious", "Clever", "Stupid", "Wise", "Foolish", "Smart", "Dumb", "Intelligent", "Ignorant", "Knowledgeable", "Uninformed", "Educated", "Uneducated", "Informed", "Uninformed", "Experienced", "Inexperienced", "Skilled", "Unskilled", "Talented", "Untalented", "Gifted", "Ungifted", "Creative", "Uncreative", "Imaginative", "Unimaginative", "Innovative", "Uninnovative", "Resourceful", "Unresourceful", "Adventurous" };
    
    random_device rd;
    mt19937 gen(rd());
    std::uniform_int_distribution<> animalIndex(0, animals.size() - 1);
    std::uniform_int_distribution<> adjectiveIndex(0, adjectives.size() - 1);

    string randomNumber = std::to_string(rand() % 1000 + 1);

    return adjectives[adjectiveIndex(gen)] + " " + animals[animalIndex(gen)] + " " + randomNumber;
}