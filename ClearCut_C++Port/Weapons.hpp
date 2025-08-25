//
//  Weapons.hpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/18/25.
//

#ifndef Weapons_hpp
#define Weapons_hpp

#include <iostream>
#include <SFML/Graphics.hpp>

class Bullets {
    
public:
    Bullets(sf::Vector2f origin, bool _left, sf::Texture& gBulletTexture) : location(origin), left(_left) { //rect ({size, size}) {

        sprite = std::make_unique<sf::Sprite>(gBulletTexture);
        sprite->setTextureRect(sf::IntRect({0, 0}, {w, h}));
        auto origin_x = sprite->getGlobalBounds().size.x/2;
        auto origin_y = sprite->getGlobalBounds().size.y/2;
        sprite->setOrigin({origin_x, origin_y});
        
        starting_x = origin.x;
    }
    
    void display(sf::RenderWindow& window);
    void move();
    
    sf::Vector2f location;
    sf::Texture texture;
    std::unique_ptr<sf::Sprite> sprite;
    
    int row {0};
    int w {32};
    int h {32};
    float starting_x;
    
private:
    int delay {8};
    long hold {0};
    bool left;
};






class Funding_round {

public:
    Funding_round(sf::Vector2f origin, sf::Texture& funding_round_texture): location(origin){
        sprite = std::make_unique<sf::Sprite>(funding_round_texture);
        sprite->setTextureRect(sf::IntRect({0, 0}, {w, h}));
        auto origin_x = sprite->getGlobalBounds().size.x/2;
        auto origin_y = sprite->getGlobalBounds().size.y/2;
        sprite->setOrigin({origin_x, origin_y});
        sprite->setPosition(location);
//        sprite->scale({17, 17});
        
    }
    void display(sf::RenderWindow& window);

    sf::Vector2f location;
    sf::Texture texture;
    std::unique_ptr<sf::Sprite> sprite;
    
  
    
    int row {0};
    int w {32};
    int h {32};
    float starting_x;
    
private:
    int delay {5};
    long hold {0};
    float size {1};
   
};

#endif /* Weapons_hpp */
