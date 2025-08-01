//
//  Character.hpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/14/25.
//

#ifndef Character_hpp
#define Character_hpp

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Platforms.hpp"
#include "Entity.hpp"

class Character : public Entity
{
public:
    
    Character();
    ~Character() = default;
    
    void display (sf::RenderWindow& window) override;
    void move (sf::Vector2f gravity);
//    void applyForce(sf::Vector2f force) override;
//    void collision_control(Platform& plat) override;
    

    bool isLeft;
    bool canGetHit;
    bool canShoot;
    int health;
    
private:
    float maxVel {0.5};
};


#endif /* Character_hpp */
