#include "player.h"
#include <iostream>
#include <string>

using namespace std;

//starting Bankroll and initial betting variables
Player::Player(const string& playerName)
    : name(playerName), busted(false) {

    //starting chips: 5 black ($500), 10 green ($250), 40 red ($200), 50 white ($50)
    inventory = {5, 10, 40, 50};
    currentBet = {0, 0, 0, 0};
}

void Player::displayHand() const { //show first hands
    cout << name << "'s hand:\n";

    const vector<Card>& cards = hand.getCards();

    for (const Card& card : cards) {
        cout << "- " << card.toString() << '\n';
    }

    cout << "Total: " << hand.calculateTotal() << '\n';
}

void Player::takeTurn(Deck& deck) {
    string choice;

    cout << "\n" << name << "'s turn\n";
    displayHand();

    //next move
    while (!hand.isBust()) {
        cout << "hit or stand? (h/s): ";
        cin >> choice;

        //if hit
        if (choice == "h" || choice == "H") {
            if (deck.cardsRemaining() == 0) {
                cout << "empty deck.\n";
                return;
            }

            //add a card
            Card newCard = deck.draw();
            hand.addCard(newCard);

            cout << name << " drew "
                 << newCard.toString() << ".\n\n";

            displayHand();

            //busted?
            if (hand.isBust()) {
                busted = true;
                cout << name << " busted.\n";
            } else if (hand.calculateTotal() == 21) {
                cout << name << " reached 21.\n";
                return;
            }
            //if stand
        } else if (choice == "s" || choice == "S") {
            cout << name << " stands with "
                 << hand.calculateTotal() << ".\n";
            return;
        } else {
            cout << "Invalid input. Enter h or s.\n";
        }
    }
}

//new setup
void Player::resetForRound() {
    hand.reset();
    busted = false;
}

const string& Player::getName() const {
    return name;
}

const Hand& Player::getHand() const {
    return hand;
}
Hand& Player::getHand() {
    return hand;
}

bool Player::isBusted() const {
    return busted;
}

//chip logic
int Player::getInventoryValue() const {
    return inventory.getTotalValue();
}

int Player::getCurrentBetValue() const {
    return currentBet.getTotalValue();
}

const ChipSet& Player::getInventory() const {
    return inventory;
}

bool Player::placeBet(int b, int g, int r, int w) {
    //check if player actually has enough of each specific chip
    if (b > inventory.black || g > inventory.green || r > inventory.red || w > inventory.white) {
        return false;
    }
    //prevent $0 bets
    if (b==0 && g==0 && r==0 && w==0) {
        return false;
    }
    //deduct chips from inventory
    inventory.black -= b;
    inventory.green -= g;
    inventory.red -= r;
    inventory.white -=w;
    //put them on the table
    currentBet = {b, g, r, w};
    return true;
}

void Player::addChipsFromValue(int value) {
    //greedy algorithm: dealer makes change using the largest chips possible
    int remaining = value;

    inventory.black += remaining/100;
    remaining %= 100;

    inventory.green += remaining/25;
    remaining %= 25;

    inventory.red += remaining/5;
    remaining %= 5;

    inventory.white += remaining;
}

void Player::winBet() {
    //return the original chips the player bet
    inventory.black += currentBet.black;
    inventory.green += currentBet.green;
    inventory.red += currentBet.red;
    inventory.white += currentBet.white;

    //pay out the winnings in efficient chips
    addChipsFromValue(currentBet.getTotalValue());

    currentBet = {0, 0, 0, 0};
}

void Player::loseBet() {
    //dealer takes the chips. just resets the table bet
    currentBet = {0, 0, 0, 0};
}

void Player::pushBet() {
    //tie: give the exact chips back to the player
    inventory.black += currentBet.black;
    inventory.green += currentBet.green;
    inventory.red += currentBet.red;
    inventory.white += currentBet.white;

    currentBet = {0, 0, 0, 0};
}

bool Player::isBankrupt() const {
    return getInventoryValue() == 0;
}

/*
//betting Methods

int Player::getBankroll() const {
    return bankroll;
}

int Player::getCurrentBet() const {
    return currentBet;
}

void Player::placeBet(int amount) {
    currentBet = amount;
    bankroll -= amount; //deduct bet from bankroll immediately
}

void Player::winBet() {
    bankroll += (currentBet * 2); //return original bet + winnings (1:1 payout)
    currentBet = 0;
}

void Player::loseBet() {
    currentBet = 0; //bet was already deducted during placeBet()
}

void Player::pushBet() {
    bankroll += currentBet; //return the bet to the bankroll
    currentBet = 0;
}

bool Player::isBankrupt() const {
    return bankroll <= 0;
}
*/