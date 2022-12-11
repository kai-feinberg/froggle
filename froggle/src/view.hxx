#pragma once

#include "model.hxx"

class View
{
    using Circle_sprite = ge211::Circle_sprite;
    using Dimension = ge211::Dims<int>;
    using Rectangle_sprite = ge211::Rectangle_sprite;


public:
    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

    Dimension initial_window_dimensions() const;


private:
    Model const& model_;
    ge211::Circle_sprite const ball;
    ge211::Circle_sprite const orange_peg;
    ge211::Circle_sprite const blue_peg;
    ge211::Circle_sprite const light_orange_peg;
    ge211::Circle_sprite const light_blue_peg;
    Rectangle_sprite const loser;
    Rectangle_sprite const winner;
    ge211::sprites::Text_sprite const loser_text;
    ge211::sprites::Text_sprite const winner_text;
    ge211::Image_sprite const background;
    ge211::Image_sprite const ball_catcher;
    Rectangle_sprite const bc;

};
