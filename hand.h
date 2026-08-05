#ifndef HAND_H
#define HAND_H
#include <vector>
#include "card.h"
//prefer not to use namespace std in header files

class Hand {
private:
    std::vector<Card> cards;

public:
    Hand();
    ~Hand() = default;

    void addCard(const Card& card); //add one card to hand
    void reset();   //clear hand

    int calculateTotal() const; 
    bool isBust() const;    //if over 21
    bool isBlackjack() const; //21 w/ 2cards?

    const std::vector<Card>& getCards() const; //get card info
};

#endif