//
//  collisions.hpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/27/25.
//

#ifndef collisions_hpp
#define collisions_hpp

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

template<typename T, typename P> std::string collision_detection(T entity, P plat);
void character_platform_collision(Character& player_one, std::vector<Platform>& platform_list);
void enemy_platform_collision(std::vector<std::unique_ptr<Enemy>>& enemy_list, std::vector<Platform>& platform_list);
void character_enemy_collision(Character& player_one, std::vector<std::unique_ptr<Enemy>>& enemy_list, sf::Clock& health_delay_clock);
void collision_check(Character& player_one, std::vector<Platform>& platform_list,std::vector<std::unique_ptr<Enemy>>& enemy_list, sf::Clock& health_delay_clock);
void funding_round_enemy_collision(std::vector<Funding_round>& active_fr, std::vector<std::unique_ptr<Enemy>>& enemy_list, sf::Clock& shareholder_clock);
void bullet_enemy_collision(std::vector<Bullets>& active_bullets, std::vector<std::unique_ptr<Enemy>>& enemy_list, sf::Clock& shareholder_clock);



#endif /* collisions_hpp */
