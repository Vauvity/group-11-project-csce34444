#include <SFML/Graphics.hpp>
#include "RouletteGame.h"
#include "RouletteState.h"
#include "RouletteWheel.h"
#include "RouletteTableView.h"
#include "HintSystem.h"
#include "SessionStats.h"

int main(){
    sf::RenderWindow window(sf::VideoMode(1000,700),"Roulette");

    RouletteGame game;
    RouletteState state;
    RouletteWheel wheel;
    RouletteTableView table;
    HintSystem hint;
    SessionStats stats;

    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Clock clock;

    while(window.isOpen()){
        float dt=clock.restart().asSeconds();
        sf::Event e;

        while(window.pollEvent(e)){
            if(e.type==sf::Event::Closed) window.close();

            if(e.type==sf::Event::MouseButtonPressed){
                auto pos=window.mapPixelToCoords(sf::Mouse::getPosition(window));

                table.handleClick(pos,state);

                if(state.phase==GamePhase::WAITING_NEXT &&
                   pos.x>600 && pos.y>500){
                    state.phase=GamePhase::BETTING;
                    state.bettingTimer=10;
                    state.betManager.clearBets();
                }
            }
        }

        // betting timer
        if(state.phase==GamePhase::BETTING){
            state.bettingTimer-=dt;
            if(state.bettingTimer<=0){
                state.phase=GamePhase::SPINNING;
                int r=game.spin();
                state.lastResult=r;
                wheel.startSpin(r);
            }
        }

        if(state.phase==GamePhase::SPINNING){
            wheel.update(dt);
            if(!wheel.isSpinning()){
                int payout=game.evaluate(state.betManager);
                state.balance+=payout;
                stats.record(payout);
                state.phase=GamePhase::WAITING_NEXT;
            }
        }

        window.clear();

        table.draw(window,state);
        wheel.draw(window);

        sf::Text t("Time: "+std::to_string((int)state.bettingTimer),font,18);
        t.setPosition(50,50);
        window.draw(t);

        window.display();
    }
}
