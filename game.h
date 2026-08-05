#ifndef GAME_H
#define GAME_H
#include <vector>
#include "dealer.h"
#include "deck.h"
#include "player.h"

class Game {
private: //users no need to know
    Deck deck;
    std::vector<Player> players;
    Dealer dealer;

    void setupPlayers();
    void startRound();
    void resetRound();
    void prepareDeck();
    void dealInitialCards();

    void displayOpeningHands() const;
    void displayPlayerHand(const Player& player) const;
    void displayResults() const;

    bool allPlayersBusted() const;
    bool askPlayAgain() const;

public:
    Game();
    ~Game() = default;

    void run();
};

#endif