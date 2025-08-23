//
//  Text_class.hpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 8/23/25.
//

#ifndef Text_class_hpp
#define Text_class_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class CustomText {
    
public:
    CustomText(int _ts, float _x, float _y, sf::Font& font, std::string& _t)
    :text_size{_ts}, position({_x, _y}), text{font, _t}
    {        
        text.setPosition(position);
        text.setCharacterSize(text_size);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::White);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(2.f);
    }
    
    sf::Text text;
    
private:
    int text_size;
    sf::Vector2f position;
    

};



#endif /* Text_class_hpp */
