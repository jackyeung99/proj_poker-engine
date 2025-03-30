#ifndef Deck_HPP
#define Deck_HPP

#include <iostream>
#include <vector>
#include <string>

class Deck {
    public:
        Deck(); 
        void build_deck();
        void shuffle_deck();
        const std::vector<std::string>& getDeck() const; 
    
    private:
        std::vector<std::string> DeckofCards;
};



#endif