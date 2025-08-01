//
//  Character.cpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/14/25.
//

#include "Character.hpp"



Character::Character()
: Entity({100, 100}), health (3), canGetHit(true)
{
    //Set initial conditions and configs for the rectangle shape
    rect.setFillColor(sf::Color::Red);
    auto origin_x = rect.getSize().x/2;
    auto origin_y = rect.getSize().y/2;
    rect.setOrigin({origin_x, origin_y});
    rect.setPosition(location);
    
    //Set intial movement conditions for rect
    location = {100, 100};
    velocity = {0, 0};
    acceleration = {0, 0};
}

void Character::display (sf::RenderWindow& window)
{
    //Fundamental movement mechanics
    velocity += acceleration;
    location += velocity;
    rect.setPosition(location);
    
    if(velocity.y > 25){
        velocity.y = 25;
    }
    
    //Check Bounds
    if((rect.getPosition().x + rect.getSize().x/2) >= window.getSize().x || (rect.getPosition().x - rect.getSize().x/2) <= 0){
        velocity.x *= -1;
    }

    
//    acceleration = {0.f, 0.f};
    window.draw(rect);
    
}


void Character::move (sf::Vector2f gravity)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)){
        isLeft = false;
        if (acceleration.x >= maxVel){
            acceleration.x = maxVel;
        }
        else{
            acceleration += {0.1, 0};
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)){
        isLeft = true;
        if (std::abs(acceleration.x) <= maxVel){
            acceleration.x = -maxVel;
        }
        else{
            acceleration += {-0.1, 0};
        }
    }
    else{
        acceleration.x = 0;
        velocity.x = 0;
    }
    
    //Jumping gets it's own if so it can run concurrently with other movement
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::J)){
        if(isOnPlatform){
            velocity.y = -28;
        }
    }
    
    applyForce(gravity);
}



