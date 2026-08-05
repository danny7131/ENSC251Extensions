#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "deck.h"
#include "hand.h"

class Player{
    private: //player profile
    std::string name;
    Hand hand;
    bool busted;

    void displayHand() const;

    public:
    Player(const std::string& playerName);
    ~Player() = default;

    void takeTurn(Deck& deck);
    void resetForRound();

    const std::string& getName() const;
    const Hand& getHand() const;
    Hand& getHand();

    bool isBusted() const;

};


#endif