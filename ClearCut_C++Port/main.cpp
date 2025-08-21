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
#include <limits>
#include "Character.hpp"
#include "Platforms.hpp"
#include "Weapons.hpp"
#include  "Enemies.hpp"
#include <random>
#include "collisions.hpp"
#include "utils.hpp"
#include "updates.hpp"
#include "menus.hpp"



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

    std::vector<Bullets> active_bullets;
    std::vector<Funding_round> active_fr;
    std::vector<std::unique_ptr<Enemy>> enemy_list{};
    
    sf::Clock shareholder_clock;
    sf::Clock health_delay_clock;
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
            reset(level, player_one);
            reset_flag = false;
        }
        
       
        
        
        if(level == 0){
            if(!bkg.loadFromFile(background_images.at("menu_screen"))){
                std::cerr << "Unable to load menu screen" << std::endl;
            }
            window.draw(background);
            main_menu();
        }
        
//TURN BACK ON TO PLAY GAME
//        else if(player_one.health == 0 || shareholder_clock.getElapsedTime() >= sf::seconds(30.f)){
//            if(!bkg.loadFromFile(background_images.at("game_over_screen"))){
//                std::cerr << "Unable to load game over screen" << std::endl;
//            }
//            window.draw(background);
//            game_over();
//        }
        
        else{
            window.draw(background);
            play_game(player_one, enemy_list, platform_list, active_bullets, active_fr, window, level_start, level, gravity, bkg, background_images, shareholder_clock, health_delay_clock, gBulletTexture, funding_round_texture, background);
            
 
            std::string h = std::to_string(player_one.health);
            sf::Text health_text(font, h);
            health_text.setPosition({500, 10});
            health_text.setCharacterSize(300);
            health_text.setStyle(sf::Text::Bold);
            health_text.setFillColor(sf::Color::Red);
            window.draw(health_text);
        }
        
        window.display();
    }

    return 0;
}





 
