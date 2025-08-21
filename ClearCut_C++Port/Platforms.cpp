//
//  Platforms.cpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/14/25.
//

#include "Platforms.hpp"

Platform::Platform(float x, float y, float l, float h) :
location{x, y}, length{l}, height{h}, half_width{l/2}, half_height{h/2}, rect({length, height})
{
    if(!texture.loadFromFile("./All_Assets/Sprites/white.png")){
        std::cerr << "Unable to load platform texture" << std::endl;
    }
    
    sprite = std::make_unique<sf::Sprite>(texture);
    sprite->setTextureRect(sf::IntRect({0,0}, {1,1}));
    sprite->setScale({length, height});
    sprite->setPosition(location);
}


void Platform::display(sf::RenderWindow& window)
{
//    window.draw(rect);
    window.draw(*sprite);
}
