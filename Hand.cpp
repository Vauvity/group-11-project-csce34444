#include "Hand.h"
#include <sstream>

using std::stringstream;

void Hand::addCard(const Card& card)
{
    cards.push_back(card);
}

void Hand::clear()
{
    cards.clear();
}

int Hand::getValue() const
{
    int total = 0;
    int aceCount = 0;

    for (const Card& card : cards)
    {
        Rank rank = card.getRank();

        if (rank == Rank::Ace)
        {
            total += 11;
            aceCount++;
        }
        else if (rank == Rank::Ten ||
                 rank == Rank::Jack ||
                 rank == Rank::Queen ||
                 rank == Rank::King)
        {
            total += 10;
        }
        else
        {
            total += static_cast<int>(rank) + 2;
        }
    }

    while (total > 21 && aceCount > 0)
    {
        total -= 10;
        aceCount--;
    }

    return total;
}

bool Hand::isBust() const
{
    return getValue() > 21;
}

bool Hand::isBlackjack() const
{
    return cards.size() == 2 && getValue() == 21;
}

bool Hand::isSoft() const
{
    int total = 0;
    int aceCount = 0;

    for (const Card& card : cards)
    {
        Rank rank = card.getRank();

        if (rank == Rank::Ace)
        {
            total += 11;
            aceCount++;
        }
        else if (rank == Rank::Ten ||
                 rank == Rank::Jack ||
                 rank == Rank::Queen ||
                 rank == Rank::King)
        {
            total += 10;
        }
        else
        {
            total += static_cast<int>(rank) + 2;
        }
    }

    while (total > 21 && aceCount > 0)
    {
        total -= 10;
        aceCount--;
    }

    return aceCount > 0;
}

vector<Card> Hand::getCards() const
{
    return cards;
}

string Hand::toString() const
{
    stringstream ss;

    for (int i = 0; i < static_cast<int>(cards.size()); i++)
    {
        ss << cards[i].toString();

        if (i < static_cast<int>(cards.size()) - 1)
        {
            ss << " ";
        }
    }

    return ss.str();
}