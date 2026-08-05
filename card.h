#ifndef CARD_H
#define CARD_H
#include <string>
using namespace std;


class Card{
    private: 
        int rank;
        int suit;

    public: 
        Card(int r, int s);
        ~Card() = default;

        int getRank() const;
        int getSuit() const;
        int getValue() const;

        string toString() const;

};

#endif