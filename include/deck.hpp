#ifndef Deck_HPP
#define Deck_HPP

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

class Deck {
    std::vector<int> cards; // each int is 0..51
    uint64_t deck_bitmap;

public:
    Deck() {
        cards.reserve(52);
        for (int i = 0; i < 52; ++i) {
            cards.push_back(i);
        }
        shuffle_deck();
        deck_bitmap = (1ULL << 52) - 1; 
    }

   void shuffle_deck(){
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
   }

   int draw_card() {
        int card = cards.back();
        cards.pop_back();

        // least significant bit is 1
        // shift by card length bit map with 1 where card is and 0 for everything else 
        //  check that the 
        deck_bitmap &= ~(1ULL << card); 

        return card;
    }

   bool has_card(int card) const {
        // shift bits riight number of position of card 
        // check that least significant bit is 1
        
        return (deck_bitmap >> card) & 1ULL;
    }

    uint64_t get_bitmap() const {
        return deck_bitmap;
    }

   static std::string card_to_string(int card) { 
        static const char* ranks = "2345678910JQKA";
        static const char* suits = "DHSC";
        
        int rank = card % 13;
        int suit = card / 13;
        return std::string(1, ranks[rank]) + suits[suit];

   }
};


#endif