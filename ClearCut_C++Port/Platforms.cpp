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
    rect.setPosition(location);
    rect.setFillColor(sf::Color::White);
}


void Platform::display(sf::RenderWindow& window)
{
    window.draw(rect);
}
