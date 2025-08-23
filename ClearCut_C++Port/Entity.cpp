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
    
    const float bottomOfEntity = sprite->getPosition().y + sprite->getGlobalBounds().size.y/2; //sprite->getTextureRect().size.y/2;
    const float topOfPlatform = plat.location.y;

    if (bottomOfEntity > topOfPlatform) {
        // Snap entity to top of platform
        location.y -= (bottomOfEntity - topOfPlatform);
        sprite->setPosition(location);
    }
}
