//
//  menus.cpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/27/25.
//

#include "menus.hpp"

void reset(int& level, Character& player_one){
    if(level == 0){
        level = 1;
    }
    else if (level != 0){
        level = 0;
    }
    player_one.health = 3;
}




void main_menu(){

}

void game_over(){

}





void play_game(Character& player_one, std::vector<std::unique_ptr<Enemy>>& enemy_list, std::vector<Platform>& platform_list,  std::vector<Bullets>& active_bullets, std::vector<Funding_round>& active_fr, sf::RenderWindow& window, bool& level_start, int& level, sf::Vector2f& gravity, sf::Texture& bkg, std::unordered_map<std::string, std::string>& background_images, sf::Clock& shareholder_clock, sf::Clock& health_delay_clock){

    //drawing platforms
    for (int i = 0; i < platform_list.size(); ++i){
    platform_list[i].display(window);
    }

    //Update player
    player_one.move(gravity);
    player_one.display(window);



    //if start of level, spawn enemies
    if(level_start){
    switch(level){
        case 1 :
            if(!bkg.loadFromFile(background_images.at("first_bkg"))){
                std::cerr << "Unable to load menu screen" << std::endl;
            }
            spawn_enemies(enemy_list, 50, 0, 0, 0, 0);
            level_start = false;
            break;
        case 2 :
            if(!bkg.loadFromFile(background_images.at("first_bkg"))){
                std::cerr << "Unable to load menu screen" << std::endl;
            }
            spawn_enemies(enemy_list, 0, 10, 0, 0, 0);
            level_start = false;
            break;
        case 3 :
            if(!bkg.loadFromFile(background_images.at("first_bkg"))){
                std::cerr << "Unable to load menu screen" << std::endl;
            }
            spawn_enemies(enemy_list, 0, 10, 0, 0, 0);
            level_start = false;
            break;
        case 4 :
            if(!bkg.loadFromFile(background_images.at("second_bkg"))){
                std::cerr << "Unable to load menu screen" << std::endl;
            }
            spawn_enemies(enemy_list, 0, 10, 0, 0, 0);
            level_start = false;
            break;
        case 5 :
            if(!bkg.loadFromFile(background_images.at("second_bkg"))){
                std::cerr << "Unable to load menu screen" << std::endl;
            }
            spawn_enemies(enemy_list, 0, 10, 0, 0, 0);
            level_start = false;
            break;
        case 6 :
            if(!bkg.loadFromFile(background_images.at("second_bkg"))){
                std::cerr << "Unable to load menu screen" << std::endl;
            }
            spawn_enemies(enemy_list, 0, 10, 0, 0, 0);
            level_start = false;
            break;
        case 7 :
            if(!bkg.loadFromFile(background_images.at("third_bkg"))){
                std::cerr << "Unable to load menu screen" << std::endl;
            }
            spawn_enemies(enemy_list, 0, 10, 0, 0, 0);
            level_start = false;
            break;
        case 8 :
            if(!bkg.loadFromFile(background_images.at("third_bkg"))){
                std::cerr << "Unable to load menu screen" << std::endl;
            }
            spawn_enemies(enemy_list, 0, 10, 0, 0, 0);
            level_start = false;
            break;
        case 9 :
            if(!bkg.loadFromFile(background_images.at("third_bkg"))){
                std::cerr << "Unable to load menu screen" << std::endl;
            }
            spawn_enemies(enemy_list, 0, 10, 0, 0, 0);
            level_start = false;
            break;
        case 10 :
            if(!bkg.loadFromFile(background_images.at("fourth_bkg"))){
                std::cerr << "Unable to load menu screen" << std::endl;
            }
            spawn_enemies(enemy_list, 0, 10, 0, 0, 0);
            level_start = false;
            break;
        default :
            break;
    }
    }


    //Update enemies if there are any, if not, go to next level
    if(!enemy_list.empty() && !level_start){
    for(auto& enemy : enemy_list){
        enemy->move(player_one, gravity);
        enemy->display(window);
    }
    }
    else if (enemy_list.empty() && !level_start){
    change_level();
    level++;
    level_start = true;
    }


    //platform collision detection
    collision_check(player_one, platform_list, enemy_list, health_delay_clock);


    //draw bullets

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::L) && player_one.canShoot){
    active_bullets.push_back(Bullets({player_one.location.x, player_one.location.y}, player_one.isLeft));
    player_one.canShoot = false;
    }
    //updating bullets
    if(!active_bullets.empty()){
    update_bullets(active_bullets, window);
    }
    //Bullet/Enemy collision detection
    if(!active_bullets.empty() && !enemy_list.empty()){
    bullet_enemy_collision(active_bullets, enemy_list, shareholder_clock);
    }

    //Funding Rounds
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::K)){
    active_fr.push_back(Funding_round(player_one.location));
    }
    //Updating funding rounds
    if(!active_fr.empty()){
    update_funding_round(active_fr, window);
    }
    //Funding round + Enemy collision
    if(!active_fr.empty() && !enemy_list.empty()){
    funding_round_enemy_collision(active_fr, enemy_list, shareholder_clock);
    }

}




























