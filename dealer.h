#ifndef DEALER_H
#define DEALER_H
#include "deck.h"
#include "hand.h"

class Dealer {
    private:
    Hand hand;
    bool secondCardHidden;

    public:
    Dealer();
    ~Dealer() = default;

    void takeTurn(Deck& deck);
    void resetForRound();
    void displayHand() const;
    void revealHiddenCard();
    
    Hand& getHand();
    const Hand& getHand() const;
    bool isSecondCardHidden() const;

};



#endif DEALER_H