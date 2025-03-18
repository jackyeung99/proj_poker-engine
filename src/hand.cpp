#include <iostream> 
#include <vector>
#include <string>

using namespace std;


class Deck {
    public:
    void build_deck();
    
};
void Deck::build_deck(){
    vector<string> DeckofCards;

    const vector<std::string> SUIT = {"D", "H", "C", "S"};
    const vector<std::string> RANK = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

    for (string suit: SUIT) {
        for (string rank: RANK){
            DeckofCards.push_back(rank+suit);

        }
    }
    cout << DeckofCards.size();

}


int main() {
    Deck deck;
    deck.build_deck();
    return 0;
}