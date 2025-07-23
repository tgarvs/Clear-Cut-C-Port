//
//  Enemies.hpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/20/25.
//

#ifndef Enemies_hpp
#define Enemies_hpp

#include <iostream>
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include "Character.hpp"

class Enemy : public Entity
{
public:
    Enemy(int h, sf::Vector2f rs) : health(h), Entity(rs){}
    ~Enemy() {std::cout<< "Enemy Destructor has been called" << std::endl;}
    virtual void move (const Character& player) = 0;
    virtual void hit_animation() {};
    
    int health;
    
private:
    
};



class Stalker : public Enemy
{
public:
    Stalker(const float rand_origin);
    void display (sf::RenderWindow& window) override;
    void move (const Character& player) override;

    
private:
    float easing;
    
};


class Rusher : public Enemy
{
public:
    Rusher();
    void display (sf::RenderWindow& window) override;
    void move (const Character& player) override;

    
private:
    float easing;
    
};




class Flyer : public Enemy
{
public:
    Flyer();
    void display (sf::RenderWindow& window) override;
    void move (const Character& player) override;


    
private:
    float easing;

};



#endif /* Enemies_hpp */
