//
//  Entity.hpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/19/25.
//

#ifndef Entity_hpp
#define Entity_hpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Platforms.hpp"


class Entity {
    
public:
    
    Entity(sf::Vector2f rect_shape) : rect(rect_shape){};
    virtual ~Entity(){};
    
    virtual void display (sf::RenderWindow& window) = 0;
    void applyForce(sf::Vector2f force);
    void collision_control(Platform& plat);
    
    sf::RectangleShape rect;
    sf::Vector2f location;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    bool isOnPlatform;
};


#include <stdio.h>

#endif /* Entity_hpp */
