#ifndef SHOE_H
#define SHOE_H

#include <vector>
#include <random>
#include "Card.h"

using std::vector;
using std::mt19937;

class Shoe
{
private:
    vector<Card> cards;
    int deckCount;
    int nextCardIndex;
    mt19937 rng;

    void buildShoe();

public:
    Shoe(int numberOfDecks = 6);

    void reset();
    void shuffle();

    Card dealCard();

    int getCardsRemaining() const;
    int getTotalCards() const;
    bool isEmpty() const;
};

#endif