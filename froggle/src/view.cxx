#include "view.hxx"
#include "peg.hxx"

ge211::Color orange = ge211::Color(255, 165, 0);

View::View(Model const& model)
        : model_(model),
          ball(model.config_.ball_radius, ge211::Color(1, 129, 65)),
          orange_peg(7, ge211::Color(144,6,1,255)),
          blue_peg(7, ge211::Color(51,80,197,255)),
          light_orange_peg(7, ge211::Color(255,213,128,255)),
          light_blue_peg(7,ge211::Color(135,206,235,255) ),
          loser(model_.config_.scene_dims, ge211::Color::medium_red()),
          winner(model_.config_.scene_dims, ge211::Color::medium_green()),
          loser_text("YOU LOSE!", ge211::Font{"sans.ttf",72}),
          winner_text("YOU WIN!", ge211::Font{"sans.ttf",72}),
          background("backdrop.png"),
          ball_catcher("ball_catch.png"),
          bc({160,40}, ge211::Color::medium_magenta())
{ }

void
View::draw(ge211::Sprite_set& set)
{

    if(model_.get_balls_remaining()>0){
        ge211::Transform my_transform =
                ge211::Transform{}
                        .scale(0.7);
        set.add_sprite(background, {0, -10},0, my_transform);
    }

    if(model_.get_balls_remaining()>0){
        ge211::Transform my_transform =
                ge211::Transform{}
                        .scale(0.2);
        set.add_sprite(ball_catcher, model_.ball_catch_.get_bc_position(), 1, my_transform);
    }

    if(model_.get_balls_remaining()>0){
        set.add_sprite(ball,model_.ball_.get_center(),1);
    }

    for (Peg peg: model_.get_all_pegs()){
        if (peg.get_is_active() && !peg.get_is_decaying()){
            if (peg.get_is_orange()){
                set.add_sprite(orange_peg, peg.top_left(), 1 );
            }
            else{
                set.add_sprite(blue_peg, peg.top_left(),1);
            }
        }

        if (peg.get_is_active() && peg.get_is_decaying()){
            if (peg.get_is_orange()){
                set.add_sprite(light_orange_peg, peg.top_left(), 1 );
            }
            else{
                set.add_sprite(light_blue_peg, peg.top_left(),1);
            }
        }
    }
    for (int i=0; i<model_.get_balls_remaining()-1; i++){
            set.add_sprite(ball,
                           {model_.config_.scene_dims.width-20, 10+i*15},1);
    }

    if (model_.num_orange_remaining() ==0 ){
        set.add_sprite(winner, {0,0},3);

        Dimension m = model_.config_.scene_dims;
        set.add_sprite(winner_text, ge211::Posn<int>{m.width/2-190, m.height/2-150},4);
    }

    else if (model_.get_balls_remaining()==0){
        // MAKE LOSING SCREEN
        set.add_sprite(loser, {0,0},3);

        Dimension m = model_.config_.scene_dims;
        set.add_sprite(loser_text, ge211::Posn<int>{m.width/2-190, m.height/2-150},4);
    }

}

Dimensions
View::initial_window_dimensions() const{
    return model_.config_.scene_dims;
}



