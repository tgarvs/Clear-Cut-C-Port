//
//  utils.hpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/27/25.
//


#ifndef utils_hpp
#define utils_hpp


#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Audio.hpp>

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>

//#include "Character.hpp"
//#include "Platforms.hpp"
//#include "Weapons.hpp"
//#include "Enemies.hpp"
//#include "collisions.hpp"






class CustomAudio {
public:
    CustomAudio(std::string _src)
    : src(_src)
    {
        if(!buffer.loadFromFile(src)){
            std::cerr << "Unable to load sound" << std::endl;
        }
        sound = std::make_unique<sf::Sound>(buffer);
    }
    
    void play(){
        sound->play();
    }
    
    void stop(){
        sound->stop();
    }
    
private:
    sf::SoundBuffer buffer;
    std::unique_ptr<sf::Sound> sound;
    std::string src;
};




class CustomMusic {
public:
    CustomMusic(const std::string _src)
    : src(_src), musicCanChange(true)
    {
        std::cout<<"music constructor called for : " << src <<std::endl;
        
        if(!music.openFromFile(src)){
            std::cerr << "Unable to load music" << std::endl;
        }
        music.setLooping(true);
    }
    
    void play(){
        if(musicCanChange){
            music.play();
            musicCanChange = false;
            isPlaying = true;
        }
    }
    
    void stop(){
        music.stop();
        musicCanChange = true;
        isPlaying = false;
    }
    
    void allow_music(){
        musicCanChange = true;
    }
    
    bool isPlaying;
    
private:
    bool musicCanChange;
    sf::Music music;
    const std::string src;
};


float random_num(const float range_start, const float range_end);
void set_music(const  std::string& path, std::unordered_map<std::string, std::unique_ptr<CustomMusic>>& themeMusic);



#endif /* utils_hpp */


