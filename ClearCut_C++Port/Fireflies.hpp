//
//  Fireflies.hpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 8/23/25.
//

#ifndef Fireflies_hpp
#define Fireflies_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>

class Fireflies {
    
public:
    Fireflies(float _start_size, float _start_x, float _start_y, const sf::Color& _color, const int& _window_size, float _increaser, float _speed)
    : size(_start_size), x_pos(_start_x), y_pos(_start_y), color(_color), window_size(_window_size), increaser(_increaser), speed(_speed)
    {
        fly.setSize({size, size});
        fly.setPosition({x_pos, y_pos});
        fly.setFillColor(color);
    }
    
    void move_and_display()
    {
        
        size+=increaser;
        
        if(size <= 2 || size >= 10){
            increaser *= -1;
        }
  
        
        if(x_pos <= window_size+100){
            x_pos += speed;
        }
        else if(x_pos > window_size+100){
            x_pos = -100;
        }
        
        fly.setSize({size, size});
        fly.setPosition({x_pos, y_pos});
        fly.setFillColor(color);
    }
    
    sf::RectangleShape fly;
    
private:
    float size;
    float x_pos;
    float y_pos;
    sf::Color color;
    const int window_size;
    float increaser;
    float speed;
    
};

#endif /* Fireflies_hpp */
