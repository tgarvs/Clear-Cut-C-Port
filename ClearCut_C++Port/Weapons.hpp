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
    Bullets(sf::Vector2f origin, bool _left) : location(origin), left(_left), size(30), rect ({size, size}) {
        auto origin_x = rect.getSize().x/2;
        auto origin_y = rect.getSize().y/2;
        rect.setOrigin({origin_x, origin_y});
        rect.setFillColor(sf::Color::Green);
    }
    
    void display(sf::RenderWindow& window);
    void move();
    

    float size;
    sf::RectangleShape rect;
    sf::Vector2f location;
    
private:

    bool left;
    
};



class Funding_round {

public:
    Funding_round(sf::Vector2f origin): location(origin), size(0.0f), stroke(25.f), rect(size) {
        rect.setOutlineThickness(stroke);
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::Blue);
    }
    void display(sf::RenderWindow& window);
    void move();
    float get_stroke();
    
    
    float size;
    sf::CircleShape rect;
    sf::Vector2f location;
    
private:

    float stroke;
   
};

#endif /* Weapons_hpp */
