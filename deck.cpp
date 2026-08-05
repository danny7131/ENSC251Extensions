#include "deck.h"
#include <algorithm>
#include <random>
#include <stdexcept>
using namespace std;

Deck::Deck(){
    initialize();
}

void Deck::initialize(){
    cards.clear();

    for(int suit = 0; suit < 4; ++suit){
        for(int rank = 1; rank <= 13; ++rank){
            cards.push_back(Card(rank, suit));
        }
    }
}

void Deck::shuffle(){
    random_device randomDevice;
    mt19937 generator(randomDevice());

    //to avoid self-calling, need to manually add std::
    std::shuffle(cards.begin(), cards.end(), generator);
}

Card Deck::draw(){
    if (cards.empty()) {
        throw out_of_range("deck empty");
    }

    Card drawnCard = cards.back();
    cards.pop_back();
    return drawnCard;
}

int Deck::cardsRemaining() const{
    return static_cast<int>(cards.size());
}
