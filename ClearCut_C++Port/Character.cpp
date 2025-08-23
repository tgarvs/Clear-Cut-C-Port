//
//  Character.cpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/14/25.
//

#include "Character.hpp"



Character::Character()
: Entity("./All_Assets/Sprites/mainCharacter.png"), health (3), canGetHit(true), isLeft(true), canShoot(true)
{
    location = {100, 100};
    velocity = {0, 0};
    acceleration = {0, 0};
    
    
    sprite->setTextureRect(sf::IntRect({column, 0}, {w, h}));
    int origin_x {sprite->getTextureRect().size.x/2};
    int origin_y {sprite->getTextureRect().size.y/2};
    sprite->setOrigin({float(origin_x), float(origin_y)});
    sprite->setPosition({100, 100});
    
    
}


void Character::display (sf::RenderWindow& window)
{
    //Fundamental movement mechanics
    velocity += acceleration;
    location += velocity;
    sprite->setPosition(location);
    
    if(velocity.y > 25){
        velocity.y = 25;
    }
    
    
    //Check Bounds
    if((sprite->getPosition().x) >= window.getSize().x || (sprite->getPosition().x) <= 0){
        velocity.x *= -1;
    }

    window.draw(*sprite);
    
}


void Character::move (sf::Vector2f gravity)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)){
        isLeft = false;
//        animate(1);
        if (acceleration.x >= maxVel){
            acceleration.x = maxVel;
        }
        else{
            acceleration += {0.1, 0};
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)){
        isLeft = true;
//        animate(0);
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
    
    
    if(velocity.y < 0){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::L)){
            animate(4);
        }
       else{
           animate(2);
       }
    }
    else if(velocity.y > 0){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::L)){
            animate(4);
        }
       else{
           animate(3);
       }
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)){
        animate(0);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)){
        animate(1);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::L)){
        animate(4);
    }
    else{
        animate(5);
    }

    
    applyForce(gravity);
}




void Character::animate(int direction){
    switch(direction){
        case 0 : //moving left
            hold = (hold+1) % delay;
            if(hold == 0){
                if(column < w){
                    column += w;
                }
                else{
                    column = 0;
                }
                sprite->setTextureRect(sf::IntRect({column, h*2}, {w, h}));
            }
            break;
            
        case 1 : //moving right
            hold = (hold+1) % delay;
            if(hold == 0){
                if(column < w){
                    column += w;
                }
                else{
                    column = 0;
                }
                sprite->setTextureRect(sf::IntRect({column, h*3}, {w, h}));
            }
            break;
            
        case 2: //jumping
            if(isLeft){
                sprite->setTextureRect(sf::IntRect({0, h*6}, {w, h}));
            }
            else{
                sprite->setTextureRect(sf::IntRect({0, h*7}, {w, h}));
            }
            break;
            
        case 3: //falling
            if(isLeft){
                sprite->setTextureRect(sf::IntRect({w, h*6}, {w, h}));
            }
            else{
                sprite->setTextureRect(sf::IntRect({w, h*7}, {w, h}));
            }
            break;
            
        case 4: //shooting
            if(isLeft){
                sprite->setTextureRect(sf::IntRect({0, h*4}, {w, h}));
            }
            else{
                sprite->setTextureRect(sf::IntRect({0, h*5}, {w, h}));
            }
            break;
        
        case 5:
            if(isLeft){
                sprite->setTextureRect(sf::IntRect({0, 0}, {w, h}));
            }
            else{
                sprite->setTextureRect(sf::IntRect({0, h}, {w, h}));
            }
            break;
    }
}
