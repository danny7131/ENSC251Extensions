#ifndef DECK_H
#define DECK_H

#include <vector>
#include "card.h"

class Deck {
    private: 
    std::vector<Card> cards;

    public:
    Deck();
    ~Deck() = default;

    void initialize();  //starting 52 cards deck
    void shuffle();     //shuffle deck
    Card draw();        //pick a card
    int cardsRemaining() const; //return #of remaining cards

};


#endif 