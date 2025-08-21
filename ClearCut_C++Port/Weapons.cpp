//
//  Weapons.cpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/18/25.
//

#include "Weapons.hpp"


void Bullets::display(sf::RenderWindow& window)
{
    hold = (hold+1) % delay;
    if(hold == 0){
        if(row < h){
            row += h;
        }
        else{
            row = 0;
        }
        sprite->setTextureRect(sf::IntRect({0, row}, {w, h}));
    }
    
    sprite->setPosition(location);
    window.draw(*sprite);
    
    
//    sf::RectangleShape outline (sprite->getGlobalBounds().size);
//    outline.setPosition(sprite->getGlobalBounds().position);
//    outline.setOutlineColor(sf::Color::White);
//    outline.setOutlineThickness(5);
//    outline.setFillColor(sf::Color::Transparent);
//    window.draw(outline);
}



void Bullets::move()
{
    if(left){location.x-=50;}
    else{location.x+=50;}
}







void Funding_round::display(sf::RenderWindow& window)
{
    hold = (hold+1) % delay;
    if(hold == 0){
        if(row < h*11){
            row += h;
            size+=2; //scale should get up to 11?
        }
        else{
            row = 0;
        }
        sprite->setScale({size, size});
        sprite->setTextureRect(sf::IntRect({0, row}, {w, h}));
    }
    window.draw(*sprite);
    
//    sf::RectangleShape outline (sprite->getGlobalBounds().size);
//    outline.setPosition(sprite->getGlobalBounds().position);
//    outline.setOutlineColor(sf::Color::White);
//    outline.setOutlineThickness(5);
//    outline.setFillColor(sf::Color::Transparent);
//    window.draw(outline);
}



