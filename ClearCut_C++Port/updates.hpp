//
//  updates.hpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/27/25.
//

#ifndef updates_hpp
#define updates_hpp

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

void update_bullets(std::vector<Bullets>& active_bullets, sf::RenderWindow& window);
void update_funding_round(std::vector<Funding_round>& active_fr, sf::RenderWindow& window);

void spawn_enemies(std::vector<std::unique_ptr<Enemy>>& enemy_list, int amountStalkers, int amountRushers, int amountFlyers, int amountGiants, int amountKings, float window_x);


#endif /* updates_hpp */
