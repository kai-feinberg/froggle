//
// Created by Sara Kurniawan on 11/16/22.
//

#ifndef GAME_GAME_CONFIG_HXX
#define GAME_GAME_CONFIG_HXX

#endif //GAME_GAME_CONFIG_HXX

#pragma once

#include <ge211.hxx>
#include <peg.hxx>

using Position = ge211::Posn<int>;

struct Game_config
{
    // Constructs an instance with the default parameters.
    Game_config();

    // The dimensions of the whole window:
    ge211::Dims<int> scene_dims;

    std::vector<Position> all_pos;

    // Radius of the ball
    int ball_radius;

    int gravity;

    //number of frames it takes for a hit peg to be eliminated from play
    int decay_frames;

    int initial_velocity;

    int num_balls;

    void set_num_balls(int i);
};
