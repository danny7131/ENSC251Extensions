#include "hand.h"

using namespace std;

Hand::Hand() {
}

void Hand::addCard(const Card& card) {
    cards.push_back(card);
}

void Hand::reset() {
    cards.clear();
}

int Hand::calculateTotal() const {
    int total = 0;
    int aceCount = 0;

    for (const Card& card : cards) {
        total += card.getValue();

        if (card.getRank() == 1) {
            ++aceCount;
        }
    }

    while (total > 21 && aceCount > 0) {
        total -= 10;
        --aceCount;
    }

    return total;
}

bool Hand::isBust() const {
    return calculateTotal() > 21;
}

bool Hand::isBlackjack() const {
    return cards.size() == 2 && calculateTotal() == 21;
}

const vector<Card>& Hand::getCards() const {
    return cards;
}