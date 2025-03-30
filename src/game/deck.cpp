#include "deck.hpp"
#include <iostream> 
#include <vector>
#include <string>
#include <random>
#include <algorithm>


using namespace std;

Deck::Deck() {
    build_deck();
}


void Deck::build_deck(){

    const vector<string> SUIT = {"D", "H", "C", "S"};
    const vector<string> RANK = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

    for (string suit: SUIT) {
        for (string rank: RANK){
            DeckofCards.push_back(rank+suit);

        }
    }
    // cout << DeckofCards.size();

}

void Deck::shuffle_deck(){
    random_device rd;
    mt19937 g(rd()); 
    shuffle(DeckofCards.begin(), DeckofCards.end(), g);
}

const vector<string>& Deck::getDeck() const {
    return DeckofCards;
}
