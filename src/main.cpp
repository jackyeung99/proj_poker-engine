#include "deck.hpp"
#include <iostream> 
#include <vector>


int main(){

    Deck deck;
    deck.build_deck();
    deck.shuffle_deck();

    for (const auto&card : deck.getDeck()) {
        std::cout << card << " ";
    }   
    std::cout << std::endl;

    return 0;
}