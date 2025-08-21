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
    
    Entity(std::string _texture){
        if(!texture.loadFromFile(_texture)){
            std::cerr << "Unable to load character sprite" << std::endl;
        }
        sprite = std::make_unique<sf::Sprite>(texture);
    };
    
    virtual ~Entity(){};
    
    virtual void display (sf::RenderWindow& window) = 0;
    void applyForce(sf::Vector2f force);
    void collision_control(Platform& plat);
    
    sf::RectangleShape rect;
    sf::Vector2f location;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    bool isOnPlatform;
    
    
    sf::Texture texture;
    std::unique_ptr<sf::Sprite> sprite;

};


#include <stdio.h>

#endif /* Entity_hpp */
