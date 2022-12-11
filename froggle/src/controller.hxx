#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
    using Dimension = ge211::Dims<int>;
public:
    Controller();

protected:
    void draw(ge211::Sprite_set& set) override;
    void on_mouse_up( ge211::Mouse_button, ge211::Posn<int>) override;
    void on_mouse_move(ge211::Posn<int>) override;
    void on_frame(double dt) override;
    ge211::Posn<int> get_mouse_pos() const;
    Dimension initial_window_dimensions() const override;

private:
    Model model_;
    Game_config config_;
    View view_;
    ge211::Posn<int> mouse_pos_;
};
