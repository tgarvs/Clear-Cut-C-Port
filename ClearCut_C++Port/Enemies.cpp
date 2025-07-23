//
//  Enemies.cpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/20/25.
//

#include "Enemies.hpp"





Stalker::Stalker(const float rand_origin): Enemy(5, {100, 200}), easing(0.0005f) {
    //Set initial conditions and configs for the rectangle shape
    rect.setFillColor(sf::Color::Yellow);
    auto origin_x = rect.getSize().x/2;
    auto origin_y = rect.getSize().y/2;
    rect.setOrigin({origin_x, origin_y});
    rect.setPosition(location);
    
    //Set intial movement conditions for rect
    location = {rand_origin, 100};
    velocity = {0, 0};
    acceleration = {0, 0};
}


void Stalker::display (sf::RenderWindow& window)
{
    velocity += acceleration;
    location += velocity;
    rect.setPosition(location);
    
    
    //Check Bounds
    if((rect.getPosition().x + rect.getSize().x/2) >= window.getSize().x){
        velocity = {0,0};
        location.x = window.getSize().x - rect.getSize().x/2;
    }
    if((rect.getPosition().x - rect.getSize().x/2) <= 0){
        velocity = {0,0};
        location.x = rect.getSize().x/2;
    }
    
//    acceleration = {0.f, 0.f};
    window.draw(rect);
    
}


void Stalker::move (const Character& player){
    float targetX = player.location.x + player.rect.getSize().x/2;
    float dx = targetX - location.x;
    location.x += dx * easing;
    
    float targetY = player.location.y + player.rect.getSize().y/2;
    float dy = targetY - location.y;
    location.y += dy * easing; //enemy moves towards player at rate of easing
}




//RUSHER CLASS METHODS
Rusher::Rusher(): Enemy(5, {100, 200}), easing(0.0001f) {
    //Set initial conditions and configs for the rectangle shape
    rect.setFillColor(sf::Color::Blue);
    auto origin_x = rect.getSize().x/2;
    auto origin_y = rect.getSize().y/2;
    rect.setOrigin({origin_x, origin_y});
    rect.setPosition(location);
    
    //Set intial movement conditions for rect
    location = {1000, 100};
    velocity = {0, 0};
    acceleration = {0, 0};
}


void Rusher::display (sf::RenderWindow& window)
{
    velocity += acceleration;
    location += velocity;
    rect.setPosition(location);
    
    
    //Check Bounds
    if((rect.getPosition().x + rect.getSize().x/2) >= window.getSize().x || (rect.getPosition().x - rect.getSize().x/2) <= 0){
        velocity.x *= -1;
    }
    
//    acceleration = {0.f, 0.f};
    window.draw(rect);
}


void Rusher::move (const Character& player){
    sf::Vector2f tempLoc = {player.location.x, player.location.y};
    tempLoc-=location; //get distance between rusher and player
    tempLoc = tempLoc.normalized() * easing; //resets tempLoc's magnitude to easing amount
    applyForce(tempLoc); //applies force to rusher's acceleration
}








//Flyer CLASS METHODS
Flyer::Flyer(): Enemy(5, {50, 50}), easing(0.0001f) {
    //Set initial conditions and configs for the rectangle shape
    rect.setFillColor(sf::Color::Magenta);
    auto origin_x = rect.getSize().x/2;
    auto origin_y = rect.getSize().y/2;
    rect.setOrigin({origin_x, origin_y});
    rect.setPosition(location);
    
    //Set intial movement conditions for rect
    location = {500, 100};
    velocity = {0, 0};
    acceleration = {0, 0};
}


void Flyer::display (sf::RenderWindow& window)
{
    velocity += acceleration;
    location += velocity;
    rect.setPosition(location);
    
    
    //Check Bounds
    if((rect.getPosition().x + rect.getSize().x/2) >= window.getSize().x || (rect.getPosition().x - rect.getSize().x/2) <= 0){
        velocity.x *= -1;
    }

    
//    acceleration = {0.f, 0.f};
    window.draw(rect);
}


void Flyer::move (const Character& player){
    sf::Vector2f tempLoc = player.location - location; //get distance between rusher and player
    tempLoc = tempLoc.normalized() * easing; //resets tempLoc's magnitude to easing amount
    applyForce(tempLoc); //applies force to rusher's acceleration
}
