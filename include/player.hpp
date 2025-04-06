#ifndef player_H
#define player_H

#include <bitmap.hpp>
#include <string> 
#include <vector> 

class Player{
    public:
        int id;
        std::string name; 
        float balance = 0;
        bool is_all_in = false;
        

        Level decide_action();
        float decide_raise_amount();



        CardBitmap player_hand;
    private:

};

#endif