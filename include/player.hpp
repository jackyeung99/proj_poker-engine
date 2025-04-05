#ifndef player_H
#define player_H

#include <bitmap.hpp>
#include <string> 
#include <vector> 

class Player{
    public:
        std::string name; 
        float balance = 0;
        int action();

        CardBitmap player_hand;

    private:

};

#endif