//
//  Weapons.cpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/18/25.
//

#include "Weapons.hpp"


void Bullets::display(sf::RenderWindow& window)
{
    rect.setSize({size, size});
    rect.setPosition(location);
    window.draw(rect);
}



void Bullets::move()
{
    if(left){location.x-=10;}
    else{location.x+=10;}
    size -= 0.5f;
}







void Funding_round::display(sf::RenderWindow& window)
{
    rect.setOrigin({size, size});
    rect.setPosition(location);
    rect.setRadius(size);
    window.draw(rect);
}



void Funding_round::move()
{
    size+=5;
    stroke-=0.5;
}

float Funding_round::get_stroke(){
    return stroke;
}
