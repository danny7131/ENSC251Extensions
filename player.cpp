#include "player.h"
#include <iostream>
#include <string>

using namespace std;

Player::Player(const string& playerName) //player initialize
    : name(playerName), busted(false) {
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
                 << newCard.toString() << ".\n";

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

bool Player::isBusted() const {
    return busted;
}