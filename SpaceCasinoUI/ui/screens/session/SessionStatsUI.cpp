#include "SessionStatsUI.h"
#include <iomanip>
#include <sstream>

SessionStatsUI::SessionStatsUI(sf::Font& sharedFont)
    : font(sharedFont),
      titleText(font, "SESSION STATS", 46),
      subTitleText(font, "Full session tracking across all games", 22),
      backButton({180.f, 50.f}),
      backText(font, "BACK", 20)
{
    titleText.setFillColor(sf::Color(255, 210, 90));
    titleText.setPosition({320.f, 24.f});
    subTitleText.setFillColor(sf::Color::White);
    subTitleText.setPosition({270.f, 80.f});
    backButton.setPosition({785.f, 660.f});
    backButton.setFillColor(sf::Color(180, 65, 85));
    backButton.setOutlineThickness(2.f);
    backButton.setOutlineColor(sf::Color(255, 210, 90));
    backText.setFillColor(sf::Color::White);
    centerTextInButton(backText, backButton);
}

void SessionStatsUI::centerTextInButton(sf::Text& text, const sf::RectangleShape& button)
{
    auto bounds = text.getLocalBounds();
    auto pos = button.getPosition();
    auto size = button.getSize();
    text.setPosition({ pos.x + (size.x - bounds.size.x) / 2.f - bounds.position.x,
                       pos.y + (size.y - bounds.size.y) / 2.f - bounds.position.y });
}

void SessionStatsUI::handleMouseClick(sf::Vector2f mousePos, bool& backToMenu)
{
    backToMenu = backButton.getGlobalBounds().contains(mousePos);
}

void SessionStatsUI::drawPanel(sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2f size, const std::string& title) const
{
    sf::RectangleShape panel(size);
    panel.setPosition(pos);
    panel.setFillColor(sf::Color(28, 32, 48));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(255, 210, 90));
    window.draw(panel);

    sf::Text header(font, title, 24);
    header.setFillColor(sf::Color(255, 210, 90));
    header.setPosition({pos.x + 15.f, pos.y + 10.f});
    window.draw(header);
}

void SessionStatsUI::drawStatLine(sf::RenderWindow& window, const std::string& label, const std::string& value, float x, float y, float width, unsigned int size) const
{
    sf::Text left(font, label, size);
    left.setFillColor(sf::Color::White);
    left.setPosition({x, y});
    window.draw(left);
    sf::Text right(font, value, size);
    right.setFillColor(sf::Color(210, 235, 255));
    auto bounds = right.getLocalBounds();
    right.setPosition({x + width - bounds.size.x - bounds.position.x, y});
    window.draw(right);
}

std::string SessionStatsUI::money(double value) const
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << "$" << value;
    return out.str();
}

std::string SessionStatsUI::percent(double value) const
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(1) << (value * 100.0) << "%";
    return out.str();
}

void SessionStatsUI::draw(sf::RenderWindow& window, const SessionStats& sessionStats)
{
    sf::RectangleShape background({1000.f, 760.f});
    background.setFillColor(sf::Color(15, 18, 30));
    window.draw(background);
    window.draw(titleText);
    window.draw(subTitleText);

    drawPanel(window, {40.f, 130.f}, {300.f, 260.f}, "Overall Session");
    drawPanel(window, {360.f, 130.f}, {280.f, 260.f}, "Blackjack");
    drawPanel(window, {660.f, 130.f}, {300.f, 260.f}, "Slots");
    drawPanel(window, {180.f, 405.f}, {300.f, 230.f}, "Roulette");
    drawPanel(window, {520.f, 405.f}, {300.f, 230.f}, "Quick Summary");

    float y = 175.f;
    drawStatLine(window, "Starting Balance", money(sessionStats.getStartingBalance()), 55.f, y); y += 30.f;
    drawStatLine(window, "Current Balance", money(sessionStats.getCurrentBalance()), 55.f, y); y += 30.f;
    drawStatLine(window, "Net Gain/Loss", money(sessionStats.getNetGainLoss()), 55.f, y); y += 30.f;
    drawStatLine(window, "Peak Balance", money(sessionStats.getPeakBalance()), 55.f, y); y += 30.f;
    drawStatLine(window, "Lowest Balance", money(sessionStats.getLowestBalance()), 55.f, y); y += 30.f;
    drawStatLine(window, "Total Rounds", std::to_string(sessionStats.getTotalRounds()), 55.f, y); y += 30.f;
    drawStatLine(window, "Games Played", std::to_string(sessionStats.getGamesPlayed()), 55.f, y);

    const auto& bj = sessionStats.getBlackjackStats();
    y = 175.f;
    drawStatLine(window, "Rounds", std::to_string(bj.getTotalRounds()), 375.f, y, 255.f); y += 30.f;
    drawStatLine(window, "Wins", std::to_string(bj.getTotalWins()), 375.f, y, 255.f); y += 30.f;
    drawStatLine(window, "Losses", std::to_string(bj.getTotalLosses()), 375.f, y, 255.f); y += 30.f;
    drawStatLine(window, "Pushes", std::to_string(bj.getTotalPushes()), 375.f, y, 255.f); y += 30.f;
    drawStatLine(window, "Blackjacks", std::to_string(bj.getTotalBlackjacks()), 375.f, y, 255.f); y += 30.f;
    drawStatLine(window, "Win Rate", percent(bj.getWinRate()), 375.f, y, 255.f); y += 30.f;
    drawStatLine(window, "Net", money(bj.getNetProfit()), 375.f, y, 255.f);

    const auto& slots = sessionStats.getSlotsStats();
    y = 175.f;
    drawStatLine(window, "Spins", std::to_string(slots.getTotalRounds()), 675.f, y); y += 30.f;
    drawStatLine(window, "Wins", std::to_string(slots.getTotalWins()), 675.f, y); y += 30.f;
    drawStatLine(window, "Losses", std::to_string(slots.getTotalLosses()), 675.f, y); y += 30.f;
    drawStatLine(window, "3 in a Row", std::to_string(slots.getThreeInARowHits()), 675.f, y); y += 30.f;
    drawStatLine(window, "Jackpots", std::to_string(slots.getJackpotHits()), 675.f, y); y += 30.f;
    drawStatLine(window, "Win Rate", percent(slots.getWinRate()), 675.f, y); y += 30.f;
    drawStatLine(window, "Net", money(slots.getNetProfit()), 675.f, y);

    const auto& rou = sessionStats.getRouletteStats();
    y = 450.f;
    drawStatLine(window, "Rounds", std::to_string(rou.getTotalRounds()), 195.f, y); y += 30.f;
    drawStatLine(window, "Wins", std::to_string(rou.getTotalWins()), 195.f, y); y += 30.f;
    drawStatLine(window, "Losses", std::to_string(rou.getTotalLosses()), 195.f, y); y += 30.f;
    drawStatLine(window, "Straight Hits", std::to_string(rou.getStraightUpHits()), 195.f, y); y += 30.f;
    drawStatLine(window, "Win Rate", percent(rou.getWinRate()), 195.f, y); y += 30.f;
    drawStatLine(window, "Net", money(rou.getNetProfit()), 195.f, y);

    y = 450.f;
    drawStatLine(window, "Blackjack Played", sessionStats.hasPlayedBlackjack() ? "Yes" : "No", 535.f, y); y += 30.f;
    drawStatLine(window, "Slots Played", sessionStats.hasPlayedSlots() ? "Yes" : "No", 535.f, y); y += 30.f;
    drawStatLine(window, "Roulette Played", sessionStats.hasPlayedRoulette() ? "Yes" : "No", 535.f, y); y += 30.f;
    drawStatLine(window, "Session Active", sessionStats.isSessionStarted() ? "Yes" : "No", 535.f, y); y += 30.f;
    drawStatLine(window, "Duration", std::to_string(static_cast<int>(sessionStats.getSessionDuration())) + "s", 535.f, y);

    window.draw(backButton);
    window.draw(backText);
}
