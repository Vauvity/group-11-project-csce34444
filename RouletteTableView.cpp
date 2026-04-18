#include "RouletteTableView.h"

RouletteTableView::RouletteTableView() {
    font.loadFromFile("arial.ttf");
}

void RouletteTableView::draw(sf::RenderWindow& window, const RouletteState& state) {
    float x=50,y=200,w=50,h=50;

    int num=1;
    for(int c=0;c<12;c++){
        for(int r=0;r<3;r++){
            sf::RectangleShape cell({w,h});
            cell.setPosition(x+c*w,y+r*h);
            cell.setFillColor(sf::Color::Green);
            window.draw(cell);

            sf::Text t(std::to_string(num++),font,14);
            t.setPosition(cell.getPosition().x+10,cell.getPosition().y+10);
            window.draw(t);
        }
    }

    // chips
    for(auto& bet: state.betManager.getBets()){
        if(bet.type==BetType::NUMBER){
            int n=bet.value-1;
            int c=n/3, r=n%3;

            sf::CircleShape chip(6);
            chip.setFillColor(sf::Color::Yellow);
            chip.setPosition(x+c*w+15,y+r*h+15);
            window.draw(chip);
        }
    }
}

void RouletteTableView::handleClick(sf::Vector2f pos, RouletteState& state) {
    if(state.phase==GamePhase::WAITING_NEXT) return;

    float x=50,y=200,w=50,h=50;

    for(int c=0;c<12;c++){
        for(int r=0;r<3;r++){
            float cx=x+c*w, cy=y+r*h;

            if(pos.x>cx && pos.x<cx+w && pos.y>cy && pos.y<cy+h){
                int num=c*3+r+1;
                state.betManager.addBet(BetType::NUMBER,num,state.currentChip);
                state.balance-=state.currentChip;
                return;
            }
        }
    }

    // bottom = RED zone
    if(pos.y>380){
        state.betManager.addBet(BetType::RED,0,state.currentChip);
        state.balance-=state.currentChip;
    }
}
