//
//  main.cpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/13/25.
//


/*
 CHANGES
 1. Give each entity a collision check and response method --> will allow for specific entities to be on different platforms
 
 
 UPDATED TODO:
 - swap enemies for sprites and include hit animatin
 - make circle collision detection for bullets/funding rounds
 - Add Hud
 - Add all sounds
 - Fine tune Level creation
 - next level animations
 - funding round counter/flag
 
 
 */


#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "Character.hpp"
#include "Platforms.hpp"
#include "Weapons.hpp"
#include  "Enemies.hpp"
#include "collisions.hpp"
#include "utils.hpp"
#include "updates.hpp"
#include "menus.hpp"
#include "Fireflies.hpp"



int main()
{
    //SETUP
    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window = sf::RenderWindow(fullscreenMode, "First Game");
    window.setVerticalSyncEnabled(true); // call it once after creating the window
    window.setFramerateLimit(60);
    
    //Basic things on screen
    Character player_one;
    
    std::vector<std::unique_ptr<Platform>> platform_list;
    platform_list.push_back(std::make_unique<Platform>(-1000, window.getSize().y, window.getSize().x+2000, 5000));
    platform_list.push_back(std::make_unique<Platform>(0, window.getSize().y/2, 400, 60));
    platform_list.push_back(std::make_unique<Platform>(window.getSize().x-400, window.getSize().y/2, 400, 60));
    
    
    std::vector<Fireflies> fireflies;
    for(int i = 0; i < 100; ++i){
        fireflies.push_back(Fireflies(random_num(1.f, 6.f),
                                      random_num(0.f, float(window.getSize().x)),
                                      random_num(0.f, float(window.getSize().y)),
                                      sf::Color(std::uint8_t(156), std::uint8_t(49), std::uint8_t(255)),
                                      window.getSize().x,
                                      random_num(0.05, 0.3),
                                      random_num(0.2, 2)));
    }
    
    std::vector<Fireflies> fireflies_yellow;
    for(int i = 0; i < 60; ++i){
        fireflies_yellow.push_back(Fireflies(random_num(1.f, 6.f),
                                      random_num(0.f, float(window.getSize().x)),
                                      random_num(0.f, float(window.getSize().y)),
                                      sf::Color(std::uint8_t(255), std::uint8_t(244), std::uint8_t(78)),
                                      window.getSize().x,
                                      random_num(0.05, 0.3),
                                      random_num(0.2, 2)));
    }
    
//    CustomAudio jumper ("./All_Assets/Sound Effects/Score & Edited/jumpSound.mp3");
//    std::vector<std::unique_ptr<CustomAudio>> soundBites;
//    soundBites.push_back(std::make_unique<CustomAudio>("./All_Assets/Sound Effects/Score & Edited/jumpSound.mp3"));
    
    std::unordered_map<std::string, std::unique_ptr<CustomAudio>> soundBites;
    soundBites.emplace("jump", std::make_unique<CustomAudio>("./All_Assets/Sound Effects/Score & Edited/jumpSound.mp3"));
    soundBites.emplace("shoot", std::make_unique<CustomAudio>("./All_Assets/Sound Effects/Score & Edited/Pew5.mp3"));
    soundBites.emplace("funding round", std::make_unique<CustomAudio>("./All_Assets/Sound Effects/Score & Edited/special.mp3"));
    soundBites.emplace("grunt", std::make_unique<CustomAudio>("./All_Assets/Sound Effects/Score & Edited/gruntSound.mp3"));
    soundBites.emplace("level change", std::make_unique<CustomAudio>("./All_Assets/Sound Effects/Score & Edited/levelChange.mp3"));
    
    
    
    std::unordered_map<std::string, std::unique_ptr<CustomMusic>> themeMusic;
    themeMusic.emplace("menu", std::make_unique<CustomMusic>("./All_Assets/Sound Effects/Score & Edited/menuTheme.mp3"));
    themeMusic.emplace("one", std::make_unique<CustomMusic>("./All_Assets/Sound Effects/Score & Edited/themeOne.mp3"));
    themeMusic.emplace("two", std::make_unique<CustomMusic>("./All_Assets/Sound Effects/Score & Edited/themeTwo.mp3"));
    themeMusic.emplace("three", std::make_unique<CustomMusic>("./All_Assets/Sound Effects/Score & Edited/themeThree.mp3"));
    themeMusic.emplace("boss", std::make_unique<CustomMusic>("./All_Assets/Sound Effects/Score & Edited/bossTheme.mp3"));
    themeMusic.emplace("final", std::make_unique<CustomMusic>("./All_Assets/Sound Effects/Score & Edited/finalTheme.mp3"));
    themeMusic.emplace("gameover", std::make_unique<CustomMusic>("./All_Assets/Sound Effects/Score & Edited/gameoverTheme.mp3"));
    
    std::vector<Bullets> active_bullets;
    std::vector<Funding_round> active_fr;
    std::vector<std::unique_ptr<Enemy>> enemy_list{};
    
    sf::Clock shareholder_clock;
    sf::Clock health_delay_clock;
    sf::Clock blood_clock;
    blood_clock.reset();
    
    int kill_count {0};
    int fr_count {0};
    int level {0};
    bool level_start {true};
    bool reset_flag {true};
    sf::Vector2f gravity {0.0f, 0.05f};
    
    sf::Texture gBulletTexture;
    if(!gBulletTexture.loadFromFile("./All_Assets/Sprites/bullet.png")){
        std::cerr << "Unable to load character sprite" << std::endl;
    }
    
    sf::Texture funding_round_texture;
    if(!funding_round_texture.loadFromFile("./All_Assets/Sprites/fundingRound.png")){
        std::cerr << "Unable to load character sprite" << std::endl;
    }

    std::unordered_map<std::string, std::string> background_images{
        {"menu_screen", "./All_Assets/Backgrounds/menuscreen.png"},
        {"game_over_screen", "./All_Assets/Backgrounds/gameoverscreen.png"},
        {"first_bkg", "./All_Assets/Backgrounds/background1.png"},
        {"second_bkg", "./All_Assets/Backgrounds/background2.png"},
        {"third_bkg", "./All_Assets/Backgrounds/background3.png"},
        {"fourth_bkg", "./All_Assets/Backgrounds/background4.png"},
        {"first_blood_bkg", "./All_Assets/Backgrounds/background1blood.png"},
        {"second_blood_bkg", "./All_Assets/Backgrounds/background2blood.png"},
        {"third_blood_bkg", "./All_Assets/Backgrounds/background3blood.png"},
        {"fourth_blood_bkg", "./All_Assets/Backgrounds/background4blood.png"}
    };

    sf::Texture bkg;
    if(!bkg.loadFromFile(background_images.at("menu_screen"))){
        std::cerr << "Unable to load menu screen" << std::endl;
        return -1;
    }
    sf::Sprite background (bkg);
    
    sf::Font font;
    if(!font.openFromFile("Fonts/AndaleMono.ttf")){
        std::cerr << "Unable to load menu screen" << std::endl;
        return -1;
    }

    
    
    while(window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
                window.setView(sf::View(visibleArea));
            }
            if(const auto* key = event->getIf<sf::Event::KeyReleased>()){
                if(key->code == sf::Keyboard::Key::L){
                    player_one.canShoot = true;
                    player_one.animate(5);
                }
                if(key->code == sf::Keyboard::Key::P){
                    reset_flag = true;
                }
                if(key->code == sf::Keyboard::Key::J || key->code == sf::Keyboard::Key::A || key->code == sf::Keyboard::Key::D){
                    player_one.animate(5);
                }
            }
        }
        
        
        //DRAW
        window.clear();
    
        //Check to see if the game has been reset or started
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::P) && reset_flag == true){
            reset(level, player_one, level_start, enemy_list);
            reset_flag = false;
        }
        
        

        if(level == 0){
            if(!bkg.loadFromFile(background_images.at("menu_screen"))){
                std::cerr << "Unable to load menu screen" << std::endl;
            }
            background.setScale({1,1});
            background.setPosition({0,0});
            window.draw(background);
            
            for(auto& flies : fireflies){
                flies.move_and_display();
                window.draw(flies.fly);
            }
            
            set_music("menu", themeMusic);
        }
        
        else if(player_one.health == 0 || shareholder_clock.getElapsedTime() >= sf::seconds(30.f)){
            if(!bkg.loadFromFile(background_images.at("game_over_screen"))){
                std::cerr << "Unable to load game over screen" << std::endl;
            }
            background.setScale({1.1, 1.1});
            background.setPosition({-100, -150});
            window.draw(background);
            
            for(auto& flies_yellow : fireflies_yellow){
                flies_yellow.move_and_display();
                window.draw(flies_yellow.fly);
            }
            
            set_music("gameover", themeMusic);


        }
        
        
        else{
            window.draw(background);
            
            display_hud(window,
                        player_one,
                        font,
                        kill_count,
                        level,
                        shareholder_clock,
                        fr_count,
                        blood_clock
                        );
            
            play_game(player_one, enemy_list, platform_list,
                      active_bullets, active_fr, window,
                      level_start, level,
                      gravity, bkg, background_images,
                      shareholder_clock, health_delay_clock,
                      gBulletTexture, funding_round_texture,
                      background, blood_clock,
                      kill_count, fr_count,
                      soundBites);
            
            
            if(level >= 1 && level < 3){
                set_music("one", themeMusic);
            }
            else if(level >= 3 && level < 6){
                set_music("two", themeMusic);
            }
            else if(level >= 6 && level < 9){
                set_music("three", themeMusic);
            }
            else if(level == 9){
                set_music("boss", themeMusic);
            }
            else if(level == 10){
                set_music("final", themeMusic);
            }
            
        }
        

        
        window.display();
    }

    return 0;
}





 
