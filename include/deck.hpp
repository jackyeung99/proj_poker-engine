#ifndef Deck_HPP
#define Deck_HPP

#include <bitmap.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

class Deck {
    std::vector<int> cards; // each int is 0..51
    CardBitmap deck_bitmap { (1ULL << 52) - 1 };

public:
    Deck() {
        init_deck();
    }

    void shuffle_deck() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }

    void reset_deck() {
        init_deck();
    }

    int draw_card() {
        if (cards.empty()) {
            throw std::runtime_error("Deck is empty!");
        }
        int card = cards.back();
        cards.pop_back();
        deck_bitmap.remove(card);
        return card;
    }

    bool is_empty() const {
        return cards.empty();
    }

    int cards_remaining() const {
        return cards.size();
    }

    uint64_t get_bitmap() const {
        return deck_bitmap.value();
    }

private:
    void init_deck() {

      
        cards.clear();
        cards.reserve(52);

        for (int i = 0; i < 52; ++i) {
            cards.push_back(i);
        }
        deck_bitmap = CardBitmap((1ULL << 52) - 1);
        shuffle_deck();
    }
};

#endif