#pragma once

#include <ge211.hxx>
#include <peg.hxx>
#include <ball.hxx>

using Dimensions = ge211::Dims<int>;
using Positions = ge211::Posn<int>;
using Rectangle = struct ge211::geometry::Rect<int>;

class Ball_Catcher
{
public:
    // CONSTRUCTOR
    Ball_Catcher(Position bc_position_, Dimensions bc_velocity_);

    // GETTER FUNCTIONS
    Position get_bc_position() const;
    Dimensions get_bc_velocity() const;
    Ball_Catcher next(double dt);
    bool catcher_hits_side(Ball_Catcher b, Game_config config);
    bool check_catcher_collision(Ball ball);

private:
    Position bc_position_;
    Dimensions bc_velocity_;
};

class Model
{
public:
    // CONSTRUCTOR
    explicit Model(Game_config const& config = Game_config());
    std::vector<Peg> get_all_pegs() const;

    Game_config config_;
    Ball ball_;
    Ball_Catcher ball_catch_;

    int num_orange_remaining() const;
    void manage_decay();
    //launches the ball in a certain direction
    //pass the direction of the mouse into this function
    void launch_ball(Positions pos);
    //ball_catcher things
    void on_frame(double dt);
    void test_helper();
    void check_conclusion();

    // GETTER FUNCTIONS
    int get_balls_remaining() const;
    bool get_won();
    bool get_lost();

private:
    int balls_remaining_;
    bool won;
    bool lost;
    //Peg will inherit properties and functions of rectangle class
    std::vector<Peg> all_pegs;

};

