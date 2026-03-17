#ifndef HAND_H
#define HAND_H

#include <vector>
#include <string>
#include "Card.h"

using std::string;
using std::vector;

class Hand
{
private:
    vector<Card> cards;

public:
    void addCard(const Card& card);
    void clear();

    int getValue() const;
    bool isBust() const;
    bool isBlackjack() const;
    bool isSoft() const;

    vector<Card> getCards() const;
    string toString() const;
};

#endif