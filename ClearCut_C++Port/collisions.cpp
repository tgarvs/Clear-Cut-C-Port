//
//  collisions.cpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/27/25.
//

#include "collisions.hpp"


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



void collision_check(Character& player_one, std::vector<Platform>& platform_list,std::vector<std::unique_ptr<Enemy>>& enemy_list, sf::Clock& health_delay_clock){
    character_platform_collision(player_one, platform_list);
    enemy_platform_collision(enemy_list, platform_list);
    character_enemy_collision(player_one, enemy_list, health_delay_clock);
};


//character platform detection
void character_platform_collision(Character& player_one, std::vector<Platform>& platform_list){
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
}


//enemy platform detection
void enemy_platform_collision(std::vector<std::unique_ptr<Enemy>>& enemy_list, std::vector<Platform>& platform_list){
    for (int i = 0; i < platform_list.size(); ++i){
        for (auto& enemy : enemy_list){
            if (collision_detection<Enemy&, Platform>(*enemy, platform_list[i]) == "Bottom"){
                enemy->collision_control(platform_list[i]);
            }
        }
    }
}


void character_enemy_collision(Character& player_one, std::vector<std::unique_ptr<Enemy>>& enemy_list, sf::Clock& health_delay_clock){
    ;
    for (auto& enemy : enemy_list){
        if (collision_detection<Enemy&, Character> (*enemy, player_one) != "None" && player_one.canGetHit == true){
            player_one.health--;
            player_one.canGetHit = false;
            break;
        }
    }
    
    if(!player_one.canGetHit){
        health_delay_clock.start();
    }
    if(health_delay_clock.getElapsedTime() > sf::seconds(2.f)){
        player_one.canGetHit = true;
        health_delay_clock.reset();
    }
}


void bullet_enemy_collision(std::vector<Bullets>& active_bullets, std::vector<std::unique_ptr<Enemy>>& enemy_list, sf::Clock& shareholder_clock){
    for(auto bulletIt = active_bullets.begin(); bulletIt != active_bullets.end();){
        bool bulletDeleted {false};
        for (auto enemyIt = enemy_list.begin(); enemyIt != enemy_list.end(); /* no ++ here */) {
            if(collision_detection<Enemy&, Bullets> (**enemyIt, *bulletIt) != "None"){
                if((*enemyIt)->health != 0){
                    (*enemyIt)->health--;
                }
                else{
                    enemy_list.erase(enemyIt);
                    active_bullets.erase(bulletIt);
                    bulletDeleted = true;
                    shareholder_clock.reset();
                    break;
                }
            }
            else{
                ++enemyIt;
            }
        }
        if(!bulletDeleted){
            ++bulletIt;
        }
    }
}



void funding_round_enemy_collision(std::vector<Funding_round>& active_fr, std::vector<std::unique_ptr<Enemy>>& enemy_list, sf::Clock& shareholder_clock){
    for(auto frIt = active_fr.begin(); frIt != active_fr.end(); ++frIt){
        for (auto enemyIt = enemy_list.begin(); enemyIt != enemy_list.end(); /* no ++ here */) {
            if(collision_detection<Enemy&, Funding_round> (**enemyIt, *frIt) != "None"){
                if((*enemyIt)->health != 0){
                    (*enemyIt)->health--;
                }
                else{
                    enemy_list.erase(enemyIt);
                    shareholder_clock.reset();
                }
            }
            else{
                ++enemyIt;
            }
        }
    }
}
