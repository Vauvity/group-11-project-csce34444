/*
    Author:     Ramon Lopez | rjl0157 | ramonlopez2@my.unt.edu
    Team:       Group 11 - Team Galactic - Space Casino
    Course:     CSCE 3444.400 Software Engineering
    Instructor: Bahareh M. Dorri
*/

#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include "MainMenu.h"
#include "GameSelect.h"
#include "BlackjackUI.h"

enum class AppState
{
    MainMenu,
    GameSelect,
    Blackjack
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

    AppState currentState = AppState::MainMenu;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
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
                        bool backToMain = false;
                        gameSelect.handleMouseClick(mousePos, openBlackjack, backToMain);

                        if (openBlackjack)
                        {
                            currentState = AppState::Blackjack;
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

        window.display();
    }

    return 0;
}