//
// Created by Sara Kurniawan on 11/16/22.
//

#include "ball.hxx"
#include "game_config.hxx"

Ball::Ball(Game_config const& config)
        : config_(config),
          radius_(config.ball_radius),
          center_(Position {config.scene_dims.width/2, 10}),
          velocity_({0,0}),
          live_(false)
{ }

Ball
Ball::next(double dt) const
{
    Ball result (*this);
    float d_x = result.velocity_.width*dt;
    float d_y = result.velocity_.height*dt;
    result.center_ = result.center_.right_by(d_x).down_by(d_y);

    //decreases velocity in line with gravitational deceleration
    if (hit_peg){
        result.velocity_= {result.velocity_.width, result.velocity_.height+config_
                .gravity};
    }
    return result;
}


bool Ball::hits_peg(const Peg &peg) {
    float rhs_ball = this->center_.right_by(radius_).x;
    float lhs_ball = this->top_left().x;
    float top_ball = this->top_left().y;
    float bot_ball = this->center_.down_by(radius_).y;

    if(!peg.get_is_active()){
        return false;
    }

    //checks the left and right boundaries
    if (rhs_ball < peg.top_left().x || peg.top_right().x < lhs_ball) {
        return false;
    }
    //checks the top and bottom boundaries
    else if (bot_ball < peg.top_left().y || peg.bottom_left().y < top_ball) {
        return false;
    } else {
        hit_peg= true;
        return true;
    }
}

Velocity Ball::get_velocity() {
    return velocity_;
}

bool
Ball::hits_peg_side(const Peg& peg) const
{
    float rhs_ball = this->center_.right_by(radius_).x;
    float lhs_ball = this->top_left().x;
    if (rhs_ball<peg.top_left().x || peg.top_right().x <lhs_ball) {
        return false;
    }
    return true;
}

bool
Ball::hits_peg_top(const Peg& peg) const
{
    float top_ball = this->top_left().y;
    float bot_ball = this->center_.down_by(radius_).y;
    if (bot_ball <peg.top_left().y || peg.bottom_left().y < top_ball){
        return false;
    }
    return true;
}


Position
Ball::top_left() const
{
    Position tl = this->center_.left_by(radius_).up_by(radius_);
    return tl;
}

bool
Ball::hits_bottom(Game_config const& config) const
{
    float bottom = this->top_left().down_by(radius_*2).y;
    if (bottom> config.scene_dims.height){
        return true;
    }
    return false;
}

bool
Ball::hits_top(Game_config const&) const
{
    float top = this->top_left().y;
    if (top< 0){
        return true;
    }
    return false;
}

bool
Ball::hits_side(Game_config const& config) const
{
    float lhs = this->top_left().x;
    float rhs = this->top_left().right_by(radius_*2).x;

    if(lhs<0 || rhs>config.scene_dims.width){
        return true;
    }
    return false;
}

void Ball::reflect_vertical() {
    velocity_.height*=-.75;
}

void Ball::reflect_horizontal()
{
    ge211::Random_source<int> rand(-40,40);
    ge211::Random_source<int> rand2(-3,3);
    velocity_.width*=-1;
    velocity_.width -= rand.next();
    center_.x += rand2.next();
}

void Ball::set_inactive()
{
    this->live_= false;
}
void Ball::set_active()
{
    this->live_= true;
}

void Ball::set_velocity(Velocity v)
{
    this->velocity_ = v;
}

bool Ball::get_is_live() const
{
    return this->live_;
}

Position Ball::get_center() const
{
    return center_;
}
