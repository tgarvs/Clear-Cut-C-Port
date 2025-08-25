//
//  utils.cpp
//  ClearCut_C++Port
//
//  Created by Thomas Garvey on 7/27/25.
//

#include "utils.hpp"



float random_num(const float range_start, const float range_end)
{
    std::random_device rd_y;
    std::mt19937 gen(rd_y());
    std::uniform_real_distribution<float> distr(range_start, range_end);
    return distr(gen);
}

void set_music(const std::string& path, std::unordered_map<std::string, std::unique_ptr<CustomMusic>>& themeMusic)
{
    for(auto& music : themeMusic){
        if(music.first != path){
            if(music.second->isPlaying){
                music.second->stop();
            }
        }
    }
    themeMusic.at(path)->play();
}
