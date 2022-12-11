#include "controller.hxx"


Controller::Controller()
        : view_(model_),
          mouse_pos_(Position {0,0})
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

void
Controller::on_frame(double dt) {
    model_.on_frame(dt);
}


//controller needs to override on_mouse_down()
// on_mouse_down() should set the balls velocity to be the unit vector of the
// position scaled by some constant defined in config

void
Controller::on_mouse_up(ge211::Mouse_button press, ge211::Posn<int> pos)
{
    if (!model_.ball_.get_is_live()){
        model_.launch_ball(mouse_pos_);
    }
}

void
Controller::on_mouse_move(ge211::Posn<int> p)
{
    mouse_pos_= p;
}

ge211::Posn<int> Controller::get_mouse_pos() const{
    return mouse_pos_;
}

