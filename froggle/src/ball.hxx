//
// Created by Sara Kurniawan on 11/16/22.
//

#ifndef GAME_BALL_HXX
#define GAME_BALL_HXX

#endif //GAME_BALL_HXX

#pragma once

#include "game_config.hxx"
#include "peg.hxx"


#include <iostream>
using Position = ge211::Posn<int>;
using Velocity = ge211::Dims<float>;
using Block = ge211::Rect<int>;


struct Ball
{
    //Peg peg;

    /// CONSTRUCTOR
    Ball(Game_config const& config);

    /// MEMBER FUNCTIONS
    // Returns the position of the top-left corner of the ball's bounding box
    Position top_left() const;

    // Returns the state of the ball after `dt` seconds have passed
    Ball next(double dt) const;

    Position get_center() const;

    bool hits_top(Game_config const&) const;

    bool hits_bottom(Game_config const&) const;

    bool hits_side(Game_config const&) const;

    bool hits_peg(Peg const&) ;

    bool hits_peg_top(Peg const&) const;

    bool hits_peg_side(Peg const&) const;

    //bool peg_collision(std::vector<Peg>& pegs);

    void reflect_vertical();

    void reflect_horizontal();

    void set_velocity(Velocity v);

    void set_inactive();
    void set_active();

    bool get_is_live() const;

    Velocity get_velocity();



private:
    // The radius of the ball.
    Game_config config_;
    int radius_;

    // The position of the center of the ball.
    Position center_ ;

    // The velocity of the ball in pixels per tick.
    Velocity velocity_;


    bool live_ = false;

    bool hit_peg= false;

};