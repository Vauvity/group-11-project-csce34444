#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 700 }), "Space Casino");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("font.otf"))
    {
        std::cout << "Font failed to load.\n";
        return 1;
    }

    sf::Text title(font, "SPACE CASINO", 54);
    title.setFillColor(sf::Color::White);
    title.setPosition({ 300.f, 100.f });

    sf::RectangleShape startButton({ 300.f, 80.f });
    startButton.setPosition({ 350.f, 280.f });
    startButton.setFillColor(sf::Color(50, 50, 150));

    sf::Text startText(font, "START GAME", 28);
    startText.setFillColor(sf::Color::White);
    startText.setPosition({ 410.f, 305.f });

    sf::RectangleShape settingsButton({ 300.f, 80.f });
    settingsButton.setPosition({ 350.f, 390.f });
    settingsButton.setFillColor(sf::Color(50, 50, 150));

    sf::Text settingsText(font, "SETTINGS", 28);
    settingsText.setFillColor(sf::Color::White);
    settingsText.setPosition({ 435.f, 415.f });

    sf::RectangleShape exitButton({ 300.f, 80.f });
    exitButton.setPosition({ 350.f, 500.f });
    exitButton.setFillColor(sf::Color(50, 50, 150));

    sf::Text exitText(font, "EXIT", 28);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition({ 470.f, 525.f });

    bool showStartMessage = false;
    bool showSettingsMessage = false;

    sf::Text messageText(font, "Placeholder only for Sprint 1 demo", 24);
    messageText.setFillColor(sf::Color::Yellow);
    messageText.setPosition({ 285.f, 620.f });

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mousePressed->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f mousePos(
                        static_cast<float>(mousePressed->position.x),
                        static_cast<float>(mousePressed->position.y)
                    );

                    if (startButton.getGlobalBounds().contains(mousePos))
                    {
                        showStartMessage = true;
                        showSettingsMessage = false;
                    }
                    else if (settingsButton.getGlobalBounds().contains(mousePos))
                    {
                        showSettingsMessage = true;
                        showStartMessage = false;
                    }
                    else if (exitButton.getGlobalBounds().contains(mousePos))
                    {
                        window.close();
                    }
                }
            }
        }

        sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos(
            static_cast<float>(mousePixelPos.x),
            static_cast<float>(mousePixelPos.y)
        );

        if (startButton.getGlobalBounds().contains(mousePos))
            startButton.setFillColor(sf::Color(80, 80, 200));
        else
            startButton.setFillColor(sf::Color(50, 50, 150));

        if (settingsButton.getGlobalBounds().contains(mousePos))
            settingsButton.setFillColor(sf::Color(80, 80, 200));
        else
            settingsButton.setFillColor(sf::Color(50, 50, 150));

        if (exitButton.getGlobalBounds().contains(mousePos))
            exitButton.setFillColor(sf::Color(80, 80, 200));
        else
            exitButton.setFillColor(sf::Color(50, 50, 150));

        window.clear(sf::Color(10, 10, 30));

        window.draw(title);

        window.draw(startButton);
        window.draw(startText);

        window.draw(settingsButton);
        window.draw(settingsText);

        window.draw(exitButton);
        window.draw(exitText);

        if (showStartMessage)
        {
            messageText.setString("Start Game clicked  placeholder for Sprint 1");
            window.draw(messageText);
        }
        else if (showSettingsMessage)
        {
            messageText.setString("Settings clicked  placeholder for Sprint 1");
            window.draw(messageText);
        }

        window.display();
    }

    return 0;
}