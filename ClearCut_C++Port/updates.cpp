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
    
    for(int i = 0; i < amountStalkers/2; ++i){
        enemy_list.push_back(std::make_unique<Stalker>(-400, random_num(0.01, 0.0001)));
        enemy_list.push_back(std::make_unique<Stalker>(window_x+450, random_num(0.01, 0.0001)));
    };
    for(int i = 0; i < amountRushers/2; ++i){
//        enemy_list.push_back(std::make_unique<Rusher>(-280, random_num(0.001, 0.0001)));
//        enemy_list.push_back(std::make_unique<Rusher>(window_x+280, random_num(0.001, 0.0001)));
        enemy_list.push_back(std::make_unique<Rusher>(0, random_num(0.001, 0.0001)));
        enemy_list.push_back(std::make_unique<Rusher>(window_x, random_num(0.001, 0.0001)));

    };
    for(int i = 0; i < amountFlyers; ++i){
        enemy_list.push_back(std::make_unique<Flyer>(random_num(300, window_x-300), random_num(0.001, 0.0001)));

    };
    for(int i = 0; i < amountGiants/2; ++i){
        enemy_list.push_back(std::make_unique<Giant>(random_num(-400, window_x), random_num(0.0009, 0.0001)));
        enemy_list.push_back(std::make_unique<Giant>(random_num(window_x+450, window_x), random_num(0.0009, 0.0001)));

    };
    for(int i = 0; i < amountKings; ++i){
        enemy_list.push_back(std::make_unique<King>(random_num(0, window_x), random_num(0.0009, 0.0001)));
    };
    
}

