//
//  Enemies.cpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/20/25.
//

#include "Enemies.hpp"


void Enemy::hit_animation()
{

}


Stalker::Stalker(const float rand_origin, const float _easing): Enemy(3, "./All_Assets/Sprites/stalkerSprite.png"), easing(_easing) {
    
    //Set intial movement conditions for rect
    location = {rand_origin, 500};
    velocity = {0, 0};
    acceleration = {0, 0};
    
    float origin_x {sprite->getGlobalBounds().size.x/2};
    float origin_y {sprite->getGlobalBounds().size.y/2};
    sprite->setOrigin({origin_x, origin_y});
    sprite->setPosition(location);
    sprite->setScale({1.2, 1.2});
    
    if(!red_texture.loadFromFile("./All_Assets/Sprites/stalkerSpriteRed.png")){
        std::cerr << "Unable to load character sprite" << std::endl;
    }
    
}


void Stalker::display (sf::RenderWindow& window)
{
    velocity += acceleration;
    location += velocity;
    sprite->setPosition(location);
    
    
    //Check Bounds
    if(sprite->getPosition().x >= (window.getSize().x + 500)){
        velocity = {0,0};
    }
    if((sprite->getPosition().x) <= -500){
        velocity = {0,0};
    }
    
    
    //Red Hit Texture
    if(red_clock.isRunning() && red_clock.getElapsedTime()<sf::seconds(0.5f)){
        sprite->setTexture(red_texture);
    }
    else if (red_clock.getElapsedTime()>sf::seconds(0.5f)){
        sprite->setTexture(texture);
        red_clock.reset();
    }
    
    
    window.draw(*sprite);
}


void Stalker::move (const Character& player, sf::Vector2f& gravity){
    applyForce(gravity);

    float targetX = player.location.x;
    float dx = targetX - location.x;
    location.x += dx * easing;
    
    float targetY = player.location.y;
    float dy = targetY - location.y;
    location.y += dy * easing; //enemy moves towards player at rate of easing
}







//RUSHER CLASS METHODS
Rusher::Rusher(const float rand_origin, const float _easing): Enemy(4, "./All_Assets/Sprites/rusherSprite.png"), easing(_easing) {
    //Set intial movement conditions for rect
    
    
    location = {rand_origin, 100};
    velocity = {0, 0};
    acceleration = {0, 0};
    
    float origin_x {sprite->getGlobalBounds().size.x/2};
    float origin_y {sprite->getGlobalBounds().size.y/2};
    sprite->setOrigin({origin_x, origin_y});
    sprite->setPosition(location);
    sprite->setScale({1.2, 1.2});
    
    if(!red_texture.loadFromFile("./All_Assets/Sprites/rusherSpriteRed.png")){
        std::cerr << "Unable to load character sprite" << std::endl;
    }
}


void Rusher::display (sf::RenderWindow& window)
{
    if(std::abs(velocity.x) <= 7){
        velocity += acceleration;
    }
    else{
        if(velocity.x > 0){
            velocity.x = 8;
        }
        if(velocity.x < 0){
            velocity.x = -8;
        }
    }
    location += velocity;
    sprite->setPosition(location);
    
    //Check Bounds
    if(sprite->getPosition().x >= window.getSize().x + 300){
        velocity.x *= -1;
        location.x = window.getSize().x + 300;
    }
    
    if(sprite->getPosition().x <= -300){
        velocity.x *= -1;
        location.x = -300;
    }
    
    //Red Hit Texture
    if(red_clock.isRunning() && red_clock.getElapsedTime()<sf::seconds(0.5f)){
        sprite->setTexture(red_texture);
    }
    else if (red_clock.getElapsedTime()>sf::seconds(0.5f)){
        sprite->setTexture(texture);
        red_clock.reset();
    }
    
    
    window.draw(*sprite);
}


void Rusher::move (const Character& player, sf::Vector2f& gravity){
    applyForce(gravity);
    sf::Vector2f tempLoc = {player.location.x, player.location.y};
    tempLoc-=location; //get distance between rusher and player
    tempLoc = tempLoc.normalized() * easing; //resets tempLoc's magnitude to easing amount
    applyForce(tempLoc); //applies force to rusher's acceleration
    }











//Flyer CLASS METHODS
Flyer::Flyer(const float rand_origin, const float _easing): Enemy(2, "./All_Assets/Sprites/flyingSprite.png"), easing(_easing) {
    //Set intial movement conditions for rect
    location = {rand_origin, -200};
    std::cout<<rand_origin<<std::endl;

    velocity = {0, 0};
    acceleration = {0, 0};
    
    float origin_x {sprite->getGlobalBounds().size.x/2};
    float origin_y {sprite->getGlobalBounds().size.y/2};
    sprite->setOrigin({origin_x, origin_y});
    sprite->setPosition(location);
    sprite->setScale({0.4, 0.4});
    
    if(!red_texture.loadFromFile("./All_Assets/Sprites/flyingSpriteRed.png")){
        std::cerr << "Unable to load character sprite" << std::endl;
    }
}


void Flyer::display (sf::RenderWindow& window)
{
    velocity += acceleration;
    location += velocity;
    sprite->setPosition(location);
    
    
    //Check Bounds
    if(sprite->getPosition().x  >= window.getSize().x){
        velocity.x *= -1;
    }
    else if(sprite->getPosition().x  <= 0){
        velocity.x *= -1;
    }
    
    if(sprite->getPosition().y <= -250){
        velocity.y *= -1;
    }
    
    //Red Hit Texture
    if(red_clock.isRunning() && red_clock.getElapsedTime()<sf::seconds(0.5f)){
        sprite->setTexture(red_texture);
    }
    else if (red_clock.getElapsedTime()>sf::seconds(0.5f)){
        sprite->setTexture(texture);
        red_clock.reset();
    }
    
    window.draw(*sprite);
}


void Flyer::move (const Character& player, sf::Vector2f& gravity){
    sf::Vector2f tempLoc = player.location - location; //get distance between rusher and player
    tempLoc = tempLoc.normalized() * easing; //resets tempLoc's magnitude to easing amount
    applyForce(tempLoc); //applies force to rusher's acceleration
}





//Giants
Giant::Giant(const float rand_origin, const float _easing): Enemy(20, "./All_Assets/Sprites/giantSprite.png"), easing(_easing) {
    //Set intial movement conditions for rect
    location = {rand_origin, 100};
    velocity = {0, 0};
    acceleration = {0, 0};
    
    float origin_x {sprite->getGlobalBounds().size.x/2};
    float origin_y {sprite->getGlobalBounds().size.y/2};
    sprite->setOrigin({origin_x, origin_y});
    sprite->setPosition(location);
    sprite->setScale({1.7, 1.7});
    
    if(!red_texture.loadFromFile("./All_Assets/Sprites/giantSpriteRed.png")){
        std::cerr << "Unable to load character sprite" << std::endl;
    }
}


void Giant::display (sf::RenderWindow& window)
{
    velocity += acceleration;
    location += velocity;
    sprite->setPosition(location);
    
    
    //Check Bounds
    if((sprite->getPosition().x + sprite->getGlobalBounds().size.x/2) >= window.getSize().x){
        velocity = {0,0};
        location.x = window.getSize().x - sprite->getGlobalBounds().size.x/2;
    }
    if((sprite->getPosition().x - sprite->getGlobalBounds().size.x/2) <= 0){
        velocity = {0,0};
        location.x = sprite->getGlobalBounds().size.x/2;
    }
    
    //Red Hit Texture
    if(red_clock.isRunning() && red_clock.getElapsedTime()<sf::seconds(0.5f)){
        sprite->setTexture(red_texture);
    }
    else if (red_clock.getElapsedTime()>sf::seconds(0.5f)){
        sprite->setTexture(texture);
        red_clock.reset();
    }
    
    window.draw(*sprite);
}


void Giant::move (const Character& player, sf::Vector2f& gravity){
    applyForce(gravity);

    float targetX = player.location.x + player.rect.getSize().x/2;
    float dx = targetX - location.x;
    location.x += dx * easing;
    
    float targetY = player.location.y + player.rect.getSize().y/2;
    float dy = targetY - location.y;
    location.y += dy * easing; //enemy moves towards player at rate of easing
}







//Kings CLASS METHODS
King::King(const float rand_origin, const float _easing): Enemy(50, "./All_Assets/Sprites/bossSprite.png"), easing(_easing) {
    //Set intial movement conditions for rect
    location = {rand_origin, 100};
    velocity = {0, 0};
    acceleration = {0, 0};
    
    float origin_x {sprite->getGlobalBounds().size.x/2};
    float origin_y {sprite->getGlobalBounds().size.y/2};
    sprite->setOrigin({origin_x, origin_y});
    sprite->setPosition(location);
    sprite->setScale({2.0, 2.0});
    
    if(!red_texture.loadFromFile("./All_Assets/Sprites/bossSpriteRed.png")){
        std::cerr << "Unable to load character sprite" << std::endl;
    }
}


void King::display (sf::RenderWindow& window)
{
    velocity += acceleration;
    location += velocity;
    sprite->setPosition(location);
    
    
    //Check Bounds
    if(sprite->getPosition().x >= window.getSize().x + 300){
        velocity.x *= -1;
        location.x = window.getSize().x + 300;
    }
    
    if(sprite->getPosition().x <= -300){
        velocity.x *= -1;
        location.x = -300;
    }
    
    //Red Hit Texture
    if(red_clock.isRunning() && red_clock.getElapsedTime()<sf::seconds(0.5f)){
        sprite->setTexture(red_texture);
    }
    else if (red_clock.getElapsedTime()>sf::seconds(0.5f)){
        sprite->setTexture(texture);
        red_clock.reset();
    }
    
    window.draw(*sprite);
}


void King::move (const Character& player, sf::Vector2f& gravity){
    applyForce(gravity);
    sf::Vector2f tempLoc = {player.location.x, player.location.y};
    tempLoc-=location; //get distance between rusher and player
    tempLoc = tempLoc.normalized() * easing; //resets tempLoc's magnitude to easing amount
    applyForce(tempLoc); //applies force to rusher's acceleration
    }





