#ifndef CASINOAPP_H
#define CASINOAPP_H

#include <SFML/Graphics.hpp>
#include <string>
#include "AppState.h"
#include "../screens/blackjack/BlackjackUI.h"
#include "../../core/session/SessionManager.h"

class Button;

class CasinoApp
{
public:
    CasinoApp();
    ~CasinoApp();

    void run();

private:
    void processEvents();
    void update();
    void render();
    void changeState(AppState newState);

    void setupButtons();
    void renderCenteredText(const std::string& text, float y, unsigned int size = 30);

    void renderWelcome();
    void renderBankrollSetup();
    void renderMainHub();

    sf::RenderWindow window;
    sf::Font font;
    SessionManager session;
    AppState currentState;

    double pendingBankroll;

    Button* startButton;
    Button* exitButton;

    Button* add5;
    Button* add25;
    Button* add100;
    Button* add500;
    Button* clearButton;
    Button* confirmButton;

    Button* blackjackButton;
    Button* backButton;

    BlackjackUI* blackjackUI;
};

#endif