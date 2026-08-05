#include "card.h"
#include <string>

using namespace std;

//initializer list
Card::Card(int r, int s)
    : rank(r), suit(s) {
    }

int Card::getRank() const{
    return rank;
}

int Card::getSuit() const{
    return suit;
}

int Card::getValue() const{
    if(rank == 1) {
        return 11; //ace
    }
    
    if(rank >= 10) {
        return 10; //namecards
    }
    return rank;
}

string Card::toString() const{
    string rankName;
    string suitName;

    if (rank == 1) {
        rankName = "Ace";
    } else if (rank == 11) {
        rankName = "Jack";
    } else if (rank == 12) {
        rankName = "Queen";
    } else if (rank == 13) {
        rankName = "King";
    } else {
        rankName = to_string(rank);
    }

    if (suit == 0) {
        suitName = "Clubs";
    } else if (suit == 1) {
        suitName = "Diamonds";
    } else if (suit == 2) {
        suitName = "Hearts";
    } else if (suit == 3) {
        suitName = "Spades";
    } else {
        suitName = "Unknown Suit";
    }

    return rankName + " of " + suitName;
}