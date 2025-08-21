//
//  menus.hpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/27/25.
//

#ifndef menus_hpp
#define menus_hpp

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


void reset(int& level, Character& player_one);
void main_menu();
void game_over();
void play_game(Character& player_one, std::vector<std::unique_ptr<Enemy>>& enemy_list,
               std::vector<std::unique_ptr<Platform>>& platform_list,
               std::vector<Bullets>& active_bullets, std::vector<Funding_round>& active_fr,
               sf::RenderWindow& window,
               bool& level_start, int& level,
               sf::Vector2f& gravity,
               sf::Texture& bkg,
               std::unordered_map<std::string, std::string>& background_images,
               sf::Clock& shareholder_clock, sf::Clock& health_delay_clock,
               sf::Texture& gBulletTexture, sf::Texture& funding_round_texture,
               sf::Sprite& background);

#endif /* menus_hpp */
