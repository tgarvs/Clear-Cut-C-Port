//
//  Character.hpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/14/25.
//

#ifndef Character_hpp
#define Character_hpp

#include <iostream>
#include <chrono>
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
    void animate(int direction);
//    void applyForce(sf::Vector2f force) override;
//    void collision_control(Platform& plat) override;
    

    bool isLeft;
    bool canGetHit;
    bool canShoot;
    int health;
    
    
    
private:
    float maxVel {0.5};
    int column {0};
    int w {192};
    int h {192};
    int delay {8};
    long hold {0};
  
    sf::Clock delay_clock;

    

    
    
    
};


#endif /* Character_hpp */
