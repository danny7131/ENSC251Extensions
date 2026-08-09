#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "deck.h"
#include "hand.h"

//structure to hold chip counts
struct ChipSet {
    int black; //$100
    int green; //$25
    int red; //$5
    int white; //$1

    //helper to calculate total $ value of the chips
    int getTotalValue() const {
        return (black * 100) + (green * 25) + (red * 5) + (white * 1);
    }
};


class Player{
    private: //player profile
    std::string name;
    Hand hand;
    bool busted;

    //chip inventories instead of an int bankroll
    ChipSet inventory;
    ChipSet currentBet;

    /*
    //betting variables
    int bankroll;
    int currentBet;
    */

    void displayHand() const;

    public:
    //removed startingBankroll parameter
    Player(const std::string& playerName); //, int startingBankroll = 1000);
    ~Player() = default;

    void takeTurn(Deck& deck);
    void resetForRound();

    const std::string& getName() const;
    const Hand& getHand() const;
    Hand& getHand();

    bool isBusted() const;

    //betting methods
    int getInventoryValue() const;
    int getCurrentBetValue() const;
    const ChipSet& getInventory() const;

    //returns true if they have the chips, false if they don't
    bool placeBet(int black, int green, int red, int white);

    void winBet();
    void loseBet();
    void pushBet();
    bool isBankrupt() const;

    //helper for the dealer to pay out in efficient chips
    void addChipsFromValue(int value);
    
    /*
    int getBankroll() const;
    int getCurrentBet() const;
    void placeBet(int amount);
    void winBet();
    void loseBet();
    void pushBet();
    bool isBankrupt() const;
    */
};

#endif