#ifndef CARD_H
#define CARD_H

#include <string>

using std::string;

enum class Rank
{
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
};

enum class Suit
{
    Clubs,
    Diamonds,
    Hearts,
    Spades
};

class Card
{
private:
    Rank rank;
    Suit suit;

public:
    Card(Rank newRank, Suit newSuit);

    Rank getRank() const;
    Suit getSuit() const;

    string toString() const;
};

#endif