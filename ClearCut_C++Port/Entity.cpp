//
//  Entity.cpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/19/25.
//

#include "Entity.hpp"


void Entity::applyForce(sf::Vector2f force)
{
    acceleration += force;
}


//Collision control
void Entity::collision_control(Platform& plat)
{
    acceleration.y = 0;
    velocity.y = 0;
    
//    //if it falls thru platform partially, reset it so it stays on top of the platform
//    if(location.y + rect.getSize().y/2 > plat.location.y){
//        location.y -= (location.y + rect.getSize().y/2) - plat.location.y;
//    }
    
    float bottomOfEntity = location.y + rect.getSize().y / 2;
    float topOfPlatform = plat.location.y;

    if (bottomOfEntity > topOfPlatform) {
        // Snap entity to top of platform
        location.y -= (bottomOfEntity - topOfPlatform);
        rect.setPosition(location); // update rectangle position
    }
}
