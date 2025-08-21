//
//  updates.cpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/27/25.
//

#include "updates.hpp"


void update_bullets(std::vector<Bullets>& active_bullets, sf::RenderWindow& window){
        for (auto bulletIt = active_bullets.begin(); bulletIt != active_bullets.end();){
            if(std::abs(bulletIt->starting_x - bulletIt->location.x) >= 1000){
                active_bullets.erase(bulletIt);
            }
            else{
                bulletIt->move();
                bulletIt->display(window);
                ++bulletIt;
                
        }
    }
}



void update_funding_round(std::vector<Funding_round>& active_fr, sf::RenderWindow& window){
    for(auto frIt = active_fr.begin(); frIt != active_fr.end();){
        if(frIt->row >= frIt->h*11){
            active_fr.erase(frIt);
        }
        else{
//            frIt->move();
            frIt->display(window);
            ++frIt;
        }
    }
}


void spawn_enemies(std::vector<std::unique_ptr<Enemy>>& enemy_list, int amountStalkers, int amountRushers, int amountFlyers, int amountGiants, int amountKings, float window_x){
    
    for(int i = 0; i < amountStalkers; ++i){
        enemy_list.push_back(std::make_unique<Stalker>(random_num(0, window_x), random_num(0.01, 0.0001)));
    };
    for(int i = 0; i < amountRushers; ++i){
        enemy_list.push_back(std::make_unique<Rusher>(random_num(0, window_x), random_num(0.01, 0.0001)));
    };
    for(int i = 0; i < amountFlyers; ++i){
        enemy_list.push_back(std::make_unique<Flyer>(random_num(0, window_x), random_num(0.0009, 0.0001)));
    };
    for(int i = 0; i < amountGiants; ++i){
        enemy_list.push_back(std::make_unique<Giant>(random_num(0, window_x), random_num(0.0009, 0.0001)));
    };
    for(int i = 0; i < amountKings; ++i){
        enemy_list.push_back(std::make_unique<King>(random_num(0, window_x), random_num(0.0009, 0.0001)));
    };
    
}



void change_level(int level, sf::Texture& bkg, std::unordered_map<std::string, std::string>& background_images, sf::Sprite& background, sf::RenderWindow& window){
    sf::Clock level_delay_clock;
    level_delay_clock.start();
    while(level_delay_clock.getElapsedTime() < sf::seconds(2.f)){
        //do something
        background.setTexture(bkg);
        window.draw(background);
        
        switch(level){
            case 1 :
                if(!bkg.loadFromFile(background_images.at("first_blood_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                break;
            case 2 :
                if(!bkg.loadFromFile(background_images.at("first_blood_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                break;
            case 3 :
                if(!bkg.loadFromFile(background_images.at("first_blood_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                break;
            case 4 :
                if(!bkg.loadFromFile(background_images.at("second_blood_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                break;
            case 5 :
                if(!bkg.loadFromFile(background_images.at("second_blood_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                break;
            case 6 :
                if(!bkg.loadFromFile(background_images.at("second_blood_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                break;
            case 7 :
                if(!bkg.loadFromFile(background_images.at("third_blood_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                break;
            case 8 :
                if(!bkg.loadFromFile(background_images.at("third_blood_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                break;
            case 9 :
                if(!bkg.loadFromFile(background_images.at("third_blood_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                break;
            case 10 :
                if(!bkg.loadFromFile(background_images.at("fourth_blood_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                break;
            default :
                break;
            }
     
        }

    level_delay_clock.reset();
}
