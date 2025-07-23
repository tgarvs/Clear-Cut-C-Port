//
//  main.cpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/13/25.
//


/*
 
 UPDATED TODO:
 - Health decrease for player - DONE
 - Game over menu and function
 - Start menu
 - Bullet + enemy collision detection (enemy health decrease & destrcution) - DONE
 - HUD + Shareholder bar
 - Add kings and giants
 - level spawns
 - Add all textures and backgrounds
 - Add all sounds
 - Level creation
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

template<typename T, typename P> std::string collision_detection(T entity, P plat);
float swept_aabb(const Character& b1, const Platform& b2, float& normalx, float& normaly);


int main()
{
    //SETUP
    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window = sf::RenderWindow(fullscreenMode, "First Game");
    window.setVerticalSyncEnabled(true); // call it once after creating the window
    window.setFramerateLimit(60);
    

    //Basic things on screen
    Character player_one;
    std::vector<Platform> platform_list{
        Platform(0, window.getSize().y, window.getSize().x, 5000),
        Platform(0, window.getSize().y/2, 400, 60),
        Platform(window.getSize().x-400, window.getSize().y/2, 400, 60)
    };
    
    std::vector<Bullets> active_bullets;
    std::vector<Funding_round> active_fr;
    
    std::random_device rd_y;
    std::mt19937 gen(rd_y());
    std::uniform_int_distribution<> distr(0, window.getSize().x);
    
    
    int amtStalkers = 5;
    int amtRushers = 5;
    int amtFlyers = 5;
    std::vector<std::unique_ptr<Enemy>> enemy_list{};
    
    for(int i = 0; i < amtStalkers; ++i){
        enemy_list.push_back(std::make_unique<Stalker>(distr(gen)  ));
    }
    
    for(int i = 0; i < amtRushers; ++i){
        enemy_list.push_back(std::make_unique<Rusher>());
    }
    
    for(int i = 0; i < amtFlyers; ++i){
        enemy_list.push_back(std::make_unique<Flyer>());
    }

    

    sf::Font font;
    if(!font.openFromFile("./Fonts/Anyfreak.ttf")){
        std::cerr << "Unable to load font" << std::endl;
        return -1;
    }
    
     
    // Create a text
    sf::Text text(font, "HIT");
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);

    
    
    sf::Vector2f gravity {0.0f, 0.05f};
    sf::Clock health_delay_clock;
    
    
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
        }
        
        
        //DRAW
        window.clear();
        
        //drawing player
        player_one.applyForce(gravity);
        player_one.move();
        player_one.display(window);
        
        
        //drawing enemies
        for(auto& enemy : enemy_list){
            enemy->applyForce(gravity);
            enemy->move(player_one);
            enemy->display(window);
        }
        
        
        //drawing platforms
        for (int i = 0; i < platform_list.size(); ++i){
            platform_list[i].display(window);
        }
        
        
        //character platform detection
        for (int i = 0; i < platform_list.size(); ++i){

            if (collision_detection<Character, Platform>(player_one, platform_list[i]) == "Bottom" && player_one.velocity.y >= 0){
                player_one.collision_control(platform_list[i]);
                if(collision_detection<Character, Platform>(player_one, platform_list[1]) == "Bottom"){
                    std::cout << "Collision with floor" << std::endl;
                }
                player_one.isOnPlatform = true;
                break;
            }
            else{
                player_one.isOnPlatform = false;
            }
        }


        
        //enemy platform detection
        for (int i = 0; i < platform_list.size(); ++i){
            for (auto& enemy : enemy_list){
                if (collision_detection<Enemy&, Platform>(*enemy, platform_list[i]) == "Bottom"){
                    enemy->collision_control(platform_list[i]);
                }
            }
        }

        
        
        //enemy + character detection + health delay
        for (auto& enemy : enemy_list){
            if (collision_detection<Enemy&, Character> (*enemy, player_one) != "None" && player_one.canGetHit == true){
                player_one.health--;
                player_one.canGetHit = false;
                window.draw(text);
            }
        }
        
        if(!player_one.canGetHit){
            health_delay_clock.start();
        }
        if(health_delay_clock.getElapsedTime() > sf::seconds(2.f)){
            player_one.canGetHit = true;
            health_delay_clock.reset();
        }
        
        std::string h = std::to_string(player_one.health);
        sf::Text health_text(font, h);
        health_text.setPosition({500, 10});
        health_text.setCharacterSize(30);
        health_text.setStyle(sf::Text::Bold);
        health_text.setFillColor(sf::Color::Red);
        window.draw(health_text);
        
        
        
        
        
        //Funding Rounds
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::K)){
            active_fr.push_back(Funding_round(player_one.location));
        }
        
        if(!active_fr.empty()){
            for(int i = 0; i < active_fr.size(); ++i){
                if(active_fr[i].get_stroke() <= 1.0){
                    active_fr.erase(active_fr.begin()+i);
                }
                else{
                    active_fr[i].move();
                    active_fr[i].display(window);
                }
                
                if(!enemy_list.empty()){
                    for (int k = 0; k < enemy_list.size(); ++k){
                        if(collision_detection<Enemy&, Funding_round> (*enemy_list[k], active_fr[i]) != "None"){
                            enemy_list[k]->health--;
                            enemy_list.erase(enemy_list.begin()+k);
                            active_fr.erase(active_fr.begin()+i);
                        }
                    }
                }
            }
        }
        
        
        
        
        //Bullets
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::L)){
            active_bullets.push_back(Bullets({player_one.location.x, player_one.location.y}, player_one.isLeft));
        }
        
        
        if(!active_bullets.empty()){
            for (int i = 0; i < active_bullets.size(); ++i){
                if(active_bullets[i].size <= 0.2){
                    active_bullets.erase(active_bullets.begin()+i);
                }
                else{
                    active_bullets[i].move();
                    active_bullets[i].display(window);
                }

                
                //Bullet/Enemy collision detection
                if(!enemy_list.empty()){
                    for (int k = 0; k < enemy_list.size(); ++k){
                        if(collision_detection<Enemy&, Bullets> (*enemy_list[k], active_bullets[i]) != "None"){
                            enemy_list[k]->health--;
                            enemy_list.erase(enemy_list.begin()+k);
                            active_bullets.erase(active_bullets.begin()+i);
                        }
                    }
                }
            }
        }
        
        
        

        window.display();
    }

    return 0;
}






//collision detection
template<typename T, typename P>
std::string collision_detection(const T entity_one, const P entity_two)
{
    if(entity_one.rect.getGlobalBounds().findIntersection(entity_two.rect.getGlobalBounds())){
        if(entity_one.location.y > entity_two.location.y){
            return "Top";
        }
        else if(entity_one.location.y < entity_two.location.y){
            return "Bottom";
        }
        else if(entity_one.location.x < entity_two.location.x){
            return "Left";
        }
        else if(entity_one.location.x > entity_two.location.x){
            return "Right";
        }
    }
    
    return "None";

}



