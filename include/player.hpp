#ifndef player_H
#define player_H

#include <string> 

class Player{
    public:
        std::string name; 
        float balance = 0;
        int action();

};

#endif