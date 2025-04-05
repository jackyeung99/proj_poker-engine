#ifndef bitmap_HPP
#define bitmap_HPP

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <sstream>

class CardBitmap {
    private:
        uint64_t bitmap;
    
    public:
        CardBitmap() : bitmap(0) {}
        explicit CardBitmap(uint64_t b) : bitmap(b) {}
    
        void add(int position) {
            bitmap |= (1ULL << position);
        }
    
        void remove(int position) {
            // least significant bit is 1
            // shift by card length bit map with 1 where card is and 0 for everything else 
            //  set bit to 0
            bitmap &= ~(1ULL << position);
        }
    
        bool contains(int position) const {
            return bitmap & (1ULL << position);
        }
    
        int count() const {
            return __builtin_popcountll(bitmap);
        }
    
        std::vector<std::string> to_cards() const {
            static const char* ranks = "23456789TJQKA";
            static const char* suits = "CDHS";
            std::vector<std::string> cards;
            uint64_t temp = bitmap;
    
            while (temp) {
                int pos = __builtin_ctzll(temp);
                int rank = pos % 13;
                int suit = pos / 13;
                cards.push_back(std::string(1, ranks[rank]) + suits[suit] );
                temp &= temp - 1;
            }
            return cards;
        }
    
        std::string to_string() const {
            auto cards = to_cards();
            std::stringstream ss;
            for (const auto& card : cards) ss << card << " ";
            return ss.str();
        }
    
        uint64_t value() const { return bitmap; }
    
        CardBitmap operator|(const CardBitmap& other) const {
            return CardBitmap(bitmap | other.bitmap);
        }
    
        CardBitmap operator&(const CardBitmap& other) const {
            return CardBitmap(bitmap & other.bitmap);
        }
    };
    

#endif