//
//  collisions.cpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/27/25.
//

#include "collisions.hpp"


//collision detection for platforms and entities
template<typename T, typename P>
std::string collision_detection_platform(const T& entity_one, const P& entity_two)
{
    
    float pos_x = entity_two.sprite->getGlobalBounds().position.x + (entity_two.sprite->getGlobalBounds().size.x * 0.16);
    float pos_y = entity_two.sprite->getGlobalBounds().position.y;
    float size_x = entity_two.sprite->getGlobalBounds().size.x * 0.66;
    float size_y = entity_two.sprite->getGlobalBounds().size.y;
    
    
    const sf::Rect<float> trunc_rect({pos_x, pos_y }, {size_x, size_y});
    
    if(entity_one.sprite->getGlobalBounds().findIntersection(trunc_rect)){
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

//for detecting collision between an enemy and player
template<typename T, typename P>
std::string collision_detection(const T& entity_one, const P& entity_two)
{
    float pos_x = entity_two.sprite->getGlobalBounds().position.x + (entity_two.sprite->getGlobalBounds().size.x * 0.3);
    float pos_y = entity_two.sprite->getGlobalBounds().position.y + (entity_two.sprite->getGlobalBounds().size.y * 0.075);
    float size_x = entity_two.sprite->getGlobalBounds().size.x * 0.4;
    float size_y = entity_two.sprite->getGlobalBounds().size.y * 0.75;
    
    
    
    const sf::Rect<float> trunc_rect({pos_x, pos_y }, {size_x, size_y});
    
    if(entity_one.sprite->getGlobalBounds().findIntersection(trunc_rect)){
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





void collision_check(Character& player_one, std::vector<std::unique_ptr<Platform>>& platform_list, std::vector<std::unique_ptr<Enemy>>& enemy_list, sf::Clock& health_delay_clock){
    character_platform_collision(player_one, platform_list);
    enemy_platform_collision(enemy_list, platform_list);
    character_enemy_collision(player_one, enemy_list, health_delay_clock);
};



void character_platform_collision(Character& player_one, std::vector<std::unique_ptr<Platform>>& platform_list){
    for (int i = 0; i < platform_list.size(); ++i){
        if (collision_detection_platform<Character, Platform>(player_one, *platform_list[i]) == "Bottom" && player_one.velocity.y >= 0){
            player_one.collision_control(*platform_list[i]);
            player_one.isOnPlatform = true;
            break;
        }
        else{
            player_one.isOnPlatform = false;
        }
    }
}


//enemy platform detection
void enemy_platform_collision(std::vector<std::unique_ptr<Enemy>>& enemy_list, std::vector<std::unique_ptr<Platform>>& platform_list){
        for (auto& enemy : enemy_list){
            if (collision_detection_platform<Enemy&, Platform>(*enemy, *platform_list[0]) == "Bottom"){
                enemy->collision_control(*platform_list[0]);
            }
    }
}


void character_enemy_collision(Character& player_one, std::vector<std::unique_ptr<Enemy>>& enemy_list, sf::Clock& health_delay_clock){
    ;
    for (auto& enemy : enemy_list){
        if (collision_detection<Character, Enemy&> (player_one, *enemy) != "None" && player_one.canGetHit == true){
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
        for (auto enemyIt = enemy_list.begin(); enemyIt != enemy_list.end();) {
            if(collision_detection<Bullets, Enemy&> (*bulletIt, **enemyIt) != "None"){
                if((*enemyIt)->health != 0){
                    (*enemyIt)->health--;
                    if(!(*enemyIt)->red_clock.isRunning()){
                        (*enemyIt)->red_clock.start();
                    }
                    active_bullets.erase(bulletIt);
                    bulletDeleted = true;
                    break;
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
            if(collision_detection<Funding_round, Enemy&> (*frIt, **enemyIt) != "None"){
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
