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





void play_game(Character& player_one, std::vector<std::unique_ptr<Enemy>>& enemy_list, std::vector<std::unique_ptr<Platform>>& platform_list,  std::vector<Bullets>& active_bullets, std::vector<Funding_round>& active_fr, sf::RenderWindow& window, bool& level_start, int& level, sf::Vector2f& gravity, sf::Texture& bkg, std::unordered_map<std::string, std::string>& background_images, sf::Clock& shareholder_clock, sf::Clock& health_delay_clock, sf::Texture& gBulletTexture, sf::Texture& funding_round_texture, sf::Sprite& background, sf::Clock& blood_clock, int& kill_count, int& fr_count){

    //drawing platforms
    for (int i = 0; i < platform_list.size(); ++i){
        platform_list[i]->display(window);
    }

    //Update player
    player_one.move(gravity);
    player_one.display(window);



    //if start of level, spawn enemies and set the background based off of the level
    if(level_start){
        shareholder_clock.start();
        switch(level){
            case 1 :
                if(!bkg.loadFromFile(background_images.at("first_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                spawn_enemies(enemy_list, 0, 0, 0, 2, 0, float(window.getSize().x));
                level_start = false;
                break;
            case 2 :
                if(!bkg.loadFromFile(background_images.at("first_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                spawn_enemies(enemy_list, 0, 2, 0, 0, 0, float(window.getSize().x));
                level_start = false;
                break;
            case 3 :
                if(!bkg.loadFromFile(background_images.at("first_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                spawn_enemies(enemy_list, 0, 0, 10, 0, 0, float(window.getSize().x));
                level_start = false;
                break;
            case 4 :
                if(!bkg.loadFromFile(background_images.at("second_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                spawn_enemies(enemy_list, 0, 0, 0, 2, 0, float(window.getSize().x));
                level_start = false;
                break;
            case 5 :
                if(!bkg.loadFromFile(background_images.at("second_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                spawn_enemies(enemy_list, 0, 0, 0, 0, 2, float(window.getSize().x));
                level_start = false;
                break;
            case 6 :
                if(!bkg.loadFromFile(background_images.at("second_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                spawn_enemies(enemy_list, 1, 0, 0, 0, 0, float(window.getSize().x));
                level_start = false;
                break;
            case 7 :
                if(!bkg.loadFromFile(background_images.at("third_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                spawn_enemies(enemy_list, 1, 0, 0, 0, 0, float(window.getSize().x));
                level_start = false;
                break;
            case 8 :
                if(!bkg.loadFromFile(background_images.at("third_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                spawn_enemies(enemy_list, 1, 0, 0, 0, 0, float(window.getSize().x));
                level_start = false;
                break;
            case 9 :
                if(!bkg.loadFromFile(background_images.at("third_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                spawn_enemies(enemy_list, 1, 0, 0, 0, 0, float(window.getSize().x));
                level_start = false;
                break;
            case 10 :
                if(!bkg.loadFromFile(background_images.at("fourth_bkg"))){
                    std::cerr << "Unable to load menu screen" << std::endl;
                }
                spawn_enemies(enemy_list, 1, 0, 0, 0, 0, float(window.getSize().x));
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
    
    //Next Level Protocol
    else if (enemy_list.empty() && !level_start){
        if(!blood_clock.isRunning()){
            blood_clock.start();
        }
        shareholder_clock.stop();
    }
    
    
    if(blood_clock.isRunning() && blood_clock.getElapsedTime() < sf::seconds(2.f)){
        switch(level){
            case 1 :
                if(!bkg.loadFromFile(background_images.at("first_blood_bkg"))){
                    std::cerr << "Unable to load first_blood_bkg" << std::endl;
                }
                break;
            case 2 :
                if(!bkg.loadFromFile(background_images.at("first_blood_bkg"))){
                    std::cerr << "Unable to load first_blood_bkg" << std::endl;
                }
                break;
            case 3 :
                if(!bkg.loadFromFile(background_images.at("first_blood_bkg"))){
                    std::cerr << "Unable to load first_blood_bkg" << std::endl;
                }
                break;
            case 4 :
                if(!bkg.loadFromFile(background_images.at("second_blood_bkg"))){
                    std::cerr << "Unable to load second_blood_bkg" << std::endl;
                }
                break;
            case 5 :
                if(!bkg.loadFromFile(background_images.at("second_blood_bkg"))){
                    std::cerr << "Unable to load second_blood_bkg" << std::endl;
                }
                break;
            case 6 :
                if(!bkg.loadFromFile(background_images.at("second_blood_bkg"))){
                    std::cerr << "Unable to load second_blood_bkg" << std::endl;
                }
                break;
            case 7 :
                if(!bkg.loadFromFile(background_images.at("third_blood_bkg"))){
                    std::cerr << "Unable to load third_blood_bkg" << std::endl;
                }
                break;
            case 8 :
                if(!bkg.loadFromFile(background_images.at("third_blood_bkg"))){
                    std::cerr << "Unable to load third_blood_bkg" << std::endl;
                }
                break;
            case 9 :
                if(!bkg.loadFromFile(background_images.at("third_blood_bkg"))){
                    std::cerr << "Unable to load third_blood_bkg" << std::endl;
                }
                break;
            case 10 :
                if(!bkg.loadFromFile(background_images.at("fourth_blood_bkg"))){
                    std::cerr << "Unable to load fourth_blood_bkg" << std::endl;
                }
                break;
            default :
                break;
            }
    }
    
    else if(blood_clock.isRunning() && blood_clock.getElapsedTime() > sf::seconds(2.f)){
        level++;
        std::cout << "level++ called" << std::endl;
        level_start = true;
        blood_clock.reset();
    }


    
    //platform collision detection
    collision_check(player_one, platform_list, enemy_list, health_delay_clock, fr_count);

    
    //draw bullets
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::L) && player_one.canShoot){
        active_bullets.push_back(Bullets({player_one.location.x, player_one.location.y}, player_one.isLeft, gBulletTexture));
        player_one.canShoot = false;
    }
    //updating bullets
    if(!active_bullets.empty()){
    update_bullets(active_bullets, window);
    }
    //Bullet/Enemy collision detection
    if(!active_bullets.empty() && !enemy_list.empty()){
    bullet_enemy_collision(active_bullets, enemy_list, shareholder_clock, kill_count, fr_count);
    }

    
    //Funding Rounds
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::K) && fr_count >= 10){
    active_fr.push_back(Funding_round(player_one.location, funding_round_texture));
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






void display_hud(sf::RenderWindow& window, Character& player_one, sf::Font font, const int& kill_count, const int& level, sf::Clock& share_holder, const int& fr_count, sf::Clock& blood_clock)
{
    auto textSize {25};

    std::string kills {std::to_string(kill_count)};
    CustomText kill_text (textSize, 325.f, 51.f, font, kills);
    window.draw(kill_text.text);
    
    std::string levels {std::to_string(level)};
    CustomText level_text (textSize, 325.f, 103.f, font, levels);
    window.draw(level_text.text);
        
    
    sf::RectangleShape sh_bar;
    float window_length {float(window.getSize().x)};
    float rect_pos_x {window_length/2.f - 300.f};
    sf::Vector2f rect_pos {rect_pos_x, 50.f};
    
    float sh_bar_width (30 - share_holder.getElapsedTime().asSeconds());
    sh_bar_width *= 20.f;
    sf::Vector2f rect_size {sh_bar_width, 30.f};
    
    sh_bar.setSize(rect_size);
    sh_bar.setPosition(rect_pos);
    sh_bar.setFillColor(sf::Color(std::uint8_t(185), std::uint8_t(2), std::uint8_t(247)));
    sh_bar.setOutlineColor(sf::Color::Black);
    sh_bar.setOutlineThickness(2.f);
    window.draw(sh_bar);
    
    
    std::vector<sf::CircleShape> health_spheres (3);
    auto grey {sf::Color(80, 80, 80)};
    
    if(player_one.health == 3)
    {
        health_spheres.at(0).setFillColor(sf::Color::Red);
        health_spheres.at(1).setFillColor(sf::Color::Red);
        health_spheres.at(2).setFillColor(sf::Color::Red);
    }
    else if(player_one.health == 2)
    {
        health_spheres.at(0).setFillColor(sf::Color::Red);
        health_spheres.at(1).setFillColor(sf::Color::Red);
        health_spheres.at(2).setFillColor(grey);
    }
    else if(player_one.health == 1)
    {
        health_spheres.at(0).setFillColor(sf::Color::Red);
        health_spheres.at(1).setFillColor(grey);
        health_spheres.at(2).setFillColor(grey);
    }
    else
    {
        health_spheres.at(0).setFillColor(grey);
        health_spheres.at(1).setFillColor(grey);
        health_spheres.at(2).setFillColor(grey);
    }

    auto starting_x {300};
    for(auto& sphere : health_spheres){
        sphere.setPosition({float(window.getSize().x) - starting_x, 50});
        starting_x -= 55;
        
        sphere.setRadius(25);
        sphere.setOutlineColor(sf::Color::Black);
        sphere.setOutlineThickness(2.f);
        window.draw(sphere);
    }
    
    
    sf::Texture trees_felled_texture;
    if(!trees_felled_texture.loadFromFile("./All_Assets/Other Assets/treesFelledWhite.png")){
        std::cerr << "Unable to load texture" << std::endl;
    }
    sf::Sprite trees_felled_sprite {trees_felled_texture};
    trees_felled_sprite.setPosition({50.f, 50.f});
    window.draw(trees_felled_sprite);
    
    sf::Texture level_texture;
    if(!level_texture.loadFromFile("./All_Assets/Other Assets/levelWhite.png")){
        std::cerr << "Unable to load texture" << std::endl;
    }
    sf::Sprite level_sprite {level_texture};
    level_sprite.setPosition({50.f, 100.f});
    window.draw(level_sprite);
    
    
    if(!player_one.canGetHit){
        sf::Texture hp_texture;
        if(!hp_texture.loadFromFile("./All_Assets/Other Assets/-1HP.png")){
            std::cerr << "Unable to load texture" << std::endl;
        }
        sf::Sprite hp_sprite {hp_texture};
        hp_sprite.setPosition({float(window.getSize().x) - 100.f, 53.f});
        window.draw(hp_sprite);
    }
    
    
    if(fr_count >= 10){
        sf::Texture fr_texture;
        if(!fr_texture.loadFromFile("./All_Assets/Other Assets/fundingroundraised.png")){
            std::cerr << "Unable to load texture" << std::endl;
        }
        sf::Sprite fr_sprite {fr_texture};
        fr_sprite.setPosition({50.f, 153.f});
        window.draw(fr_sprite);
    }
    
    if(share_holder.getElapsedTime().asSeconds() > 5 && share_holder.getElapsedTime().asSeconds() < 15){
        sf::Texture fr1_texture;
        if(!fr1_texture.loadFromFile("./All_Assets/Other Assets/shareholdersareworried.png")){
            std::cerr << "Unable to load texture" << std::endl;
        }
        sf::Sprite fr1_sprite {fr1_texture};
        fr1_sprite.setPosition({float(window.getSize().x)/2.f - 300.f, 80.f});
        window.draw(fr1_sprite);
    }
    
    else if(share_holder.getElapsedTime().asSeconds() > 15 && share_holder.getElapsedTime().asSeconds() < 25){
        sf::Texture fr1_texture;
        if(!fr1_texture.loadFromFile("./All_Assets/Other Assets/shareholderswanttotalk.png")){
            std::cerr << "Unable to load texture" << std::endl;
        }
        sf::Sprite fr1_sprite {fr1_texture};
        fr1_sprite.setPosition({float(window.getSize().x)/2.f - 300.f, 80.f});
        window.draw(fr1_sprite);
    }
    
    else if(share_holder.getElapsedTime().asSeconds() > 25 && share_holder.getElapsedTime().asSeconds() < 30){
        sf::Texture fr1_texture;
        if(!fr1_texture.loadFromFile("./All_Assets/Other Assets/youveruinedus.png")){
            std::cerr << "Unable to load texture" << std::endl;
        }
        sf::Sprite fr1_sprite {fr1_texture};
        fr1_sprite.setPosition({float(window.getSize().x)/2.f - 300.f, 80.f});
        window.draw(fr1_sprite);
    }
    

    if(blood_clock.isRunning())
    {
        sf::Texture blood_texture;
        if(!blood_texture.loadFromFile("./All_Assets/Other Assets/nextLevelBlackOutline.png")){
            std::cerr << "Unable to load texture" << std::endl;
        }
        sf::Sprite blood_sprite {blood_texture};
//        blood_sprite.scale({3, 3});
        blood_sprite.setPosition({float(window.getSize().x)/2.f - 400.f, float(window.getSize().y)/2.f - 200});
        window.draw(blood_sprite);
    }

}






















