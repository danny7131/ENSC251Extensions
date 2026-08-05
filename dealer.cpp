#include "dealer.h"
#include <iostream>
#include <vector>
using namespace std;

//initialize
Dealer::Dealer()
    : secondCardHidden(true) {
}

//show dealer hand
void Dealer::displayHand() const {
    cout << "Dealer's hand:\n";

    //add cards
    const vector<Card>& cards = hand.getCards();

    // visible cards?
    for (int i = 0; i < static_cast<int>(cards.size()); ++i) {
        if (i == 1 && secondCardHidden) {
            cout << "- [Hidden card]\n";
        } else {
            cout << "- " << cards[i].toString() << '\n';
        }
    }

    //show visible card
    if (secondCardHidden && !cards.empty()) {
        cout << "Visible total: "
             << cards[0].getValue() << '\n';
    //show calculated total
    } else {
        cout << "Total: "
             << hand.calculateTotal() << '\n';
    }
}

//dealer turn
void Dealer::takeTurn(Deck& deck) {
    cout << "\nDealer's turn\n";

    revealHiddenCard();
    displayHand();

    //dealer draw mech
    while (hand.calculateTotal() < 17) {
        if (deck.cardsRemaining() == 0) {
            cout << "empty deck.\n";
            return;
        }

        Card newCard = deck.draw();
        hand.addCard(newCard);

        cout << "Dealer drew "
             << newCard.toString() << ".\n";

        displayHand();
    }

    //result
    if (hand.isBust()) {
        cout << "Dealer busted.\n";
    } else {
        cout << "Dealer stands with "
             << hand.calculateTotal() << ".\n";
    }
}

//same as player

void Dealer::resetForRound() {
    hand.reset();
    secondCardHidden = true;
}

void Dealer::revealHiddenCard() {
    secondCardHidden = false;
}

Hand& Dealer::getHand() {
    return hand;
}

const Hand& Dealer::getHand() const {
    return hand;
}

bool Dealer::isSecondCardHidden() const {
    return secondCardHidden;
}