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
    Enemy(int h, std::string _texture) : health(h), Entity(_texture){
        red_clock.reset();
    }
    ~Enemy() {std::cout<< "Enemy Destructor has been called" << std::endl;}
    virtual void move (const Character& player, sf::Vector2f& gravity) = 0;
    void hit_animation();
    
    int health;
    sf::Texture red_texture;
    sf::Clock red_clock;
};



class Stalker : public Enemy
{
public:
    Stalker(const float rand_origin, const float _easing);
    void display (sf::RenderWindow& window) override;
    void move (const Character& player, sf::Vector2f& gravity) override;

private:
    float easing;
};


class Rusher : public Enemy
{
public:
    Rusher(const float rand_origin, const float _easing);
    void display (sf::RenderWindow& window) override;
    void move (const Character& player, sf::Vector2f& gravity) override;
    
private:
    float easing;
};




class Flyer : public Enemy
{
public:
    Flyer(const float rand_origin, const float _easing);
    void display (sf::RenderWindow& window) override;
    void move (const Character& player, sf::Vector2f& gravity) override;

private:
    float easing;
};



class Giant : public Enemy
{
public:
    Giant(const float rand_origin, const float _easing);
    void display (sf::RenderWindow& window) override;
    void move (const Character& player, sf::Vector2f& gravity) override;

private:
    float easing;
};




class King : public Enemy
{
public:
    King(const float rand_origin, const float _easing);
    void display (sf::RenderWindow& window) override;
    void move (const Character& player, sf::Vector2f& gravity) override;
    
private:
    float easing;
};

#endif /* Enemies_hpp */
