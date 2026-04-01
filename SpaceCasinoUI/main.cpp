#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include "MainMenu.h"
#include "GameSelect.h"
#include "BlackjackUI.h"
#include "SlotsUI.h"

enum class AppState
{
    MainMenu,
    GameSelect,
    Blackjack,
    Slots
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 760 }), "Space Casino");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("ARIAL.TTF"))
    {
        std::cout << "Failed to load ARIAL.TTF\n";
        return 1;
    }

    MainMenu mainMenu(font);
    GameSelect gameSelect(font);
    BlackjackUI blackjackUI(font);
    SlotsUI slotsUI(font);

    double sharedBankroll = 1000.0;
    bool bankrollInitialized = false;

    AppState currentState = AppState::MainMenu;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* textEntered = event->getIf<sf::Event::TextEntered>())
            {
                if (currentState == AppState::MainMenu)
                {
                    if (textEntered->unicode == 8)
                    {
                        mainMenu.handleBackspace();
                    }
                    else
                    {
                        mainMenu.handleTextEntered(textEntered->unicode);
                    }
                }
                else if (currentState == AppState::GameSelect)
                {
                    if (textEntered->unicode == 8)
                    {
                        gameSelect.handleBackspace();
                    }
                    else
                    {
                        gameSelect.handleTextEntered(textEntered->unicode);
                    }
                }
            }
            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mousePressed->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(
                        { mousePressed->position.x, mousePressed->position.y }
                    );

                    if (currentState == AppState::MainMenu)
                    {
                        bool startGame = false;
                        bool exitGame = false;
                        mainMenu.handleMouseClick(mousePos, startGame, exitGame);

                        if (startGame)
                        {
                            if (!bankrollInitialized)
                            {
                                sharedBankroll = mainMenu.getEnteredBankroll();
                                bankrollInitialized = true;
                            }

                            gameSelect.setBankroll(sharedBankroll);
                            blackjackUI.setStartingBankroll(sharedBankroll);
                            slotsUI.setStartingBankroll(sharedBankroll);
                            currentState = AppState::GameSelect;
                        }
                        else if (exitGame)
                        {
                            window.close();
                        }
                    }
                    else if (currentState == AppState::GameSelect)
                    {
                        bool openBlackjack = false;
                        bool openSlots = false;
                        bool backToMain = false;
                        gameSelect.handleMouseClick(mousePos, openBlackjack, openSlots, backToMain);

                        sharedBankroll = gameSelect.getBankroll();

                        if (openBlackjack)
                        {
                            blackjackUI.setStartingBankroll(sharedBankroll);
                            currentState = AppState::Blackjack;
                        }
                        else if (openSlots)
                        {
                            slotsUI.setStartingBankroll(sharedBankroll);
                            currentState = AppState::Slots;
                        }
                        else if (backToMain)
                        {
                            currentState = AppState::MainMenu;
                        }
                    }
                    else if (currentState == AppState::Blackjack)
                    {
                        bool backToMenu = false;
                        blackjackUI.handleScreenClick(mousePos, backToMenu);

                        if (backToMenu)
                        {
                            sharedBankroll = blackjackUI.getCurrentBankroll();
                            gameSelect.setBankroll(sharedBankroll);
                            slotsUI.setStartingBankroll(sharedBankroll);
                            currentState = AppState::GameSelect;
                        }
                    }
                    else if (currentState == AppState::Slots)
                    {
                        bool backToMenu = false;
                        slotsUI.handleScreenClick(mousePos, backToMenu);

                        if (backToMenu)
                        {
                            sharedBankroll = slotsUI.getCurrentBankroll();
                            gameSelect.setBankroll(sharedBankroll);
                            blackjackUI.setStartingBankroll(sharedBankroll);
                            currentState = AppState::GameSelect;
                        }
                    }
                }
            }
        }

        window.clear();

        if (currentState == AppState::MainMenu)
        {
            mainMenu.draw(window);
        }
        else if (currentState == AppState::GameSelect)
        {
            gameSelect.draw(window);
        }
        else if (currentState == AppState::Blackjack)
        {
            blackjackUI.draw(window);
        }
        else if (currentState == AppState::Slots)
        {
            slotsUI.draw(window);
        }

        window.display();
    }

    return 0;
}