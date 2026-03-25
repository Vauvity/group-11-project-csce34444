#include "Shoe.h"
#include <algorithm>
#include <chrono>
#include <stdexcept>

using std::random_device;
using std::runtime_error;

Shoe::Shoe(int numberOfDecks)
    : deckCount(numberOfDecks), nextCardIndex(0)
{
    unsigned seed = static_cast<unsigned>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()
    );

    rng.seed(seed);
    reset();
}

void Shoe::buildShoe()
{
    cards.clear();

    for (int deck = 0; deck < deckCount; deck++)
    {
        for (int suitValue = static_cast<int>(Suit::Clubs);
             suitValue <= static_cast<int>(Suit::Spades);
             suitValue++)
        {
            Suit suit = static_cast<Suit>(suitValue);

            for (int rankValue = static_cast<int>(Rank::Two);
                 rankValue <= static_cast<int>(Rank::Ace);
                 rankValue++)
            {
                Rank rank = static_cast<Rank>(rankValue);
                cards.push_back(Card(rank, suit));
            }
        }
    }
}

void Shoe::shuffle()
{
    std::shuffle(cards.begin(), cards.end(), rng);
    nextCardIndex = 0;
}

void Shoe::reset()
{
    buildShoe();
    shuffle();
}

Card Shoe::dealCard()
{
    if (isEmpty())
    {
        throw runtime_error("Cannot deal from an empty shoe.");
    }

    Card nextCard = cards[nextCardIndex];
    nextCardIndex++;

    return nextCard;
}

int Shoe::getCardsRemaining() const
{
    return static_cast<int>(cards.size()) - nextCardIndex;
}

int Shoe::getTotalCards() const
{
    return static_cast<int>(cards.size());
}

bool Shoe::isEmpty() const
{
    return nextCardIndex >= static_cast<int>(cards.size());
}