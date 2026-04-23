/*
 * Name:       Prayush Panta
 * UID:        PP1008
 * Team:       Group 11 - Team Galactic - Space Casino
 * Course:     CSCE 3444 Software Engineering
 * Instructor: Bahareh M. Dorri
 * Description: Implementation of the SessionStats class managing session data and cross-game totals.
 */

#include "SessionStats.h"
#include "../games/blackjack/BlackjackGame.h"
#include <cmath>

using std::string;


//  Constructor

SessionStats::SessionStats(double startBalance)
    : bankroll(startBalance),
      totalRoundsAllGames(0),
      gamesPlayed(0),
      playedBlackjack(false),
      playedRoulette(false),
      blackjackStats(startBalance),
      slotsStats(startBalance),
      rouletteStats(startBalance),
      sessionStarted(false)
{
}


//  Session lifecycle

void SessionStats::startSession()
{
    sessionStart   = steady_clock::now();
    sessionStarted = true;
}

void SessionStats::endSession()
{
    sessionStarted = false;
}

double SessionStats::getSessionDuration() const
{
    if (!sessionStarted) return 0.0;
    auto now     = steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - sessionStart);
    return static_cast<double>(elapsed.count());
}


// (Terminal functions removed)
