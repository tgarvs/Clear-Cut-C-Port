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
#include <SFML/Audio.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "Character.hpp"
#include "Platforms.hpp"
#include "Weapons.hpp"
#include "Enemies.hpp"
#include "utils.hpp"


template<typename T, typename P> std::string collision_detection(const T& entity, const P& plat);

template<typename T, typename P> std::string collision_detection_sprite_NONsprite(const T& entity_one, const P& entity_two);

void character_platform_collision(Character& player_one, std::vector<std::unique_ptr<Platform>>& platform_list);

void enemy_platform_collision(std::vector<std::unique_ptr<Enemy>>& enemy_list, std::vector<std::unique_ptr<Platform>>& platform_list);

void character_enemy_collision(Character& player_one, std::vector<std::unique_ptr<Enemy>>& enemy_list, sf::Clock& health_delay_clock, int& fr_count, std::unordered_map<std::string, std::unique_ptr<CustomAudio>>& soundBites);

void collision_check(Character& player_one, std::vector<std::unique_ptr<Platform>>& platform_list,std::vector<std::unique_ptr<Enemy>>& enemy_list, sf::Clock& health_delay_clock, int& fr_count, std::unordered_map<std::string, std::unique_ptr<CustomAudio>>& soundBites);

void funding_round_enemy_collision(std::vector<Funding_round>& active_fr, std::vector<std::unique_ptr<Enemy>>& enemy_list, sf::Clock& shareholder_clock);

void bullet_enemy_collision(std::vector<Bullets>& active_bullets, std::vector<std::unique_ptr<Enemy>>& enemy_list, sf::Clock& shareholder_clock, int& kill_count, int& fr_count);



#endif /* collisions_hpp */
