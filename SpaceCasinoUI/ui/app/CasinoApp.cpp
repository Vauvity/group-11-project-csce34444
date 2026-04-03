#include "CasinoApp.h"
#include "../components/Button.h"
#include <optional>
#include <sstream>
#include <iomanip>
#include <iostream>

CasinoApp::CasinoApp()
    : window(sf::VideoMode({ 1000, 700 }), "Space Casino"),
    session(1000.0),
    currentState(AppState::Welcome),
    pendingBankroll(0.0),
    startButton(nullptr),
    exitButton(nullptr),
    add5(nullptr),
    add25(nullptr),
    add100(nullptr),
    add500(nullptr),
    clearButton(nullptr),
    confirmButton(nullptr),
    blackjackButton(nullptr),
    backButton(nullptr),
    blackjackUI(nullptr)
{
    window.setFramerateLimit(60);

    if (!font.openFromFile("assets/fonts/ARIAL.TTF"))
    {
        std::cout << "Failed to load font.\n";
    }

    setupButtons();
    blackjackUI = new BlackjackUI(font);
}

CasinoApp::~CasinoApp()
{
    delete startButton;
    delete exitButton;

    delete add5;
    delete add25;
    delete add100;
    delete add500;
    delete clearButton;
    delete confirmButton;

    delete blackjackButton;
    delete backButton;

    delete blackjackUI;
}

void CasinoApp::setupButtons()
{
    startButton = new Button({ 220.f, 60.f }, { 390.f, 300.f }, "Start Game", font);
    exitButton = new Button({ 220.f, 60.f }, { 390.f, 380.f }, "Exit", font);

    add5 = new Button({ 120.f, 50.f }, { 200.f, 300.f }, "+$5", font);
    add25 = new Button({ 120.f, 50.f }, { 350.f, 300.f }, "+$25", font);
    add100 = new Button({ 120.f, 50.f }, { 500.f, 300.f }, "+$100", font);
    add500 = new Button({ 120.f, 50.f }, { 650.f, 300.f }, "+$500", font);

    clearButton = new Button({ 150.f, 50.f }, { 300.f, 400.f }, "Clear", font);
    confirmButton = new Button({ 150.f, 50.f }, { 550.f, 400.f }, "Confirm", font);

    blackjackButton = new Button({ 220.f, 60.f }, { 390.f, 300.f }, "Blackjack", font);
    backButton = new Button({ 150.f, 50.f }, { 20.f, 620.f }, "Back", font);
}

void CasinoApp::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void CasinoApp::processEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (const auto* resized = event->getIf<sf::Event::Resized>())
        {
            window.setView(sf::View(sf::FloatRect(
                { 0.f, 0.f },
                {
                    static_cast<float>(resized->size.x),
                    static_cast<float>(resized->size.y)
                }
            )));
        }

        switch (currentState)
        {
        case AppState::Welcome:
            if (startButton->isClicked(window, *event))
            {
                changeState(AppState::BankrollSetup);
            }

            if (exitButton->isClicked(window, *event))
            {
                window.close();
            }
            break;

        case AppState::BankrollSetup:
            if (add5->isClicked(window, *event)) pendingBankroll += 5.0;
            if (add25->isClicked(window, *event)) pendingBankroll += 25.0;
            if (add100->isClicked(window, *event)) pendingBankroll += 100.0;
            if (add500->isClicked(window, *event)) pendingBankroll += 500.0;

            if (clearButton->isClicked(window, *event))
            {
                pendingBankroll = 0.0;
            }

            if (confirmButton->isClicked(window, *event) && pendingBankroll > 0.0)
            {
                session.startSession(pendingBankroll);
                changeState(AppState::MainHub);
            }

            if (backButton->isClicked(window, *event))
            {
                changeState(AppState::Welcome);
            }
            break;

        case AppState::MainHub:
            if (blackjackButton->isClicked(window, *event))
            {
                blackjackUI->setStartingBankroll(session.getCurrentBankroll());
                changeState(AppState::Blackjack);
            }

            if (backButton->isClicked(window, *event))
            {
                changeState(AppState::Welcome);
            }
            break;

        case AppState::Blackjack:
        {
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mousePressed->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(mousePressed->position);

                    bool backToMenu = false;
                    blackjackUI->handleScreenClick(mousePos, backToMenu);

                    if (backToMenu)
                    {
                        session.startSession(blackjackUI->getCurrentBankroll());
                        changeState(AppState::MainHub);
                    }
                }
            }
            break;
        }

        default:
            break;
        }
    }
}

void CasinoApp::update()
{
    switch (currentState)
    {
    case AppState::Welcome:
        startButton->update(window);
        exitButton->update(window);
        break;

    case AppState::BankrollSetup:
        add5->update(window);
        add25->update(window);
        add100->update(window);
        add500->update(window);
        clearButton->update(window);
        confirmButton->update(window);
        backButton->update(window);
        break;

    case AppState::MainHub:
        blackjackButton->update(window);
        backButton->update(window);
        break;

    case AppState::Blackjack:
        // Your BlackjackUI does not have an update() method.
        break;

    default:
        break;
    }
}

void CasinoApp::render()
{
    window.clear(sf::Color(10, 10, 30));

    switch (currentState)
    {
    case AppState::Welcome:
        renderWelcome();
        break;

    case AppState::BankrollSetup:
        renderBankrollSetup();
        break;

    case AppState::MainHub:
        renderMainHub();
        break;

    case AppState::Blackjack:
        blackjackUI->draw(window);
        break;

    default:
        break;
    }

    window.display();
}

void CasinoApp::renderCenteredText(const std::string& str, float y, unsigned int size)
{
    sf::Text text(font, str);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::White);

    sf::FloatRect bounds = text.getLocalBounds();

    text.setOrigin({
        bounds.position.x + bounds.size.x / 2.0f,
        bounds.position.y + bounds.size.y / 2.0f
        });

    text.setPosition({
        window.getSize().x / 2.0f,
        y
        });

    window.draw(text);
}

void CasinoApp::renderWelcome()
{
    renderCenteredText("Space Casino", 150.f, 40);
    startButton->render(window);
    exitButton->render(window);
}

void CasinoApp::renderBankrollSetup()
{
    renderCenteredText("Set Your Bankroll", 120.f, 36);

    std::ostringstream ss;
    ss << "$" << std::fixed << std::setprecision(2) << pendingBankroll;

    renderCenteredText("Selected: " + ss.str(), 200.f, 28);

    add5->render(window);
    add25->render(window);
    add100->render(window);
    add500->render(window);

    clearButton->render(window);
    confirmButton->render(window);
    backButton->render(window);
}

void CasinoApp::renderMainHub()
{
    renderCenteredText("Main Hub", 100.f, 36);

    std::ostringstream ss;
    ss << "$" << std::fixed << std::setprecision(2)
        << session.getCurrentBankroll();

    renderCenteredText("Bankroll: " + ss.str(), 160.f, 26);

    blackjackButton->render(window);
    backButton->render(window);
}

void CasinoApp::changeState(AppState newState)
{
    currentState = newState;
}