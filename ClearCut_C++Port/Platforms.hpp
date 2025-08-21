//
//  Platforms.hpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/14/25.
//

#ifndef Platforms_hpp
#define Platforms_hpp

#include <iostream>
#include <SFML/Graphics.hpp>


class Platform {
    
public:
    Platform(float x, float y, float l, float h);
    ~Platform() = default;
    
    void display(sf::RenderWindow& window);
    
    
    sf::Vector2f location;
    float length;
    float height;
    float half_width;
    float half_height;
    
    
    sf::RectangleShape rect;
    
    
    sf::Texture texture;
    std::unique_ptr<sf::Sprite> sprite;
private:


    
    
};

#endif /* Platforms_hpp */
