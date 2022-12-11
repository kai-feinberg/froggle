#include "model.hxx"
#include "peg.hxx"
#include "ball.hxx"


Model::Model(Game_config const& config)
    : config_(config),
      ball_(config),
      ball_catch_({0,config.scene_dims.height-100}, {300, 0}),
    balls_remaining_(config.num_balls)
{
        ge211::Random_source<int> rand(1,1000);
        for (Position p : config.all_pos){
            // change boolean to true or false based on if we want it to be
            // orange
            // 1/100 pegs will be orange
            bool is_orange = (rand.next()%100==1);
            all_pegs.emplace_back(Rectangle(p.x, p.y, 7,7),is_orange);
        }

        // last peg is always orange to ensure there is no default win ;)
        if (!all_pegs.front().get_is_orange()){
            all_pegs.pop_back();
            all_pegs.emplace_back(
                    Rectangle(config.all_pos.front().x, config.all_pos.front().y, 7,7),true);
        }
    }

std::vector<Peg>
Model::get_all_pegs() const
{
    return all_pegs;
}

int
Model::get_balls_remaining() const {
    return balls_remaining_;
}

int
Model::num_orange_remaining() const {
    int count =0;
    for (Peg peg: all_pegs){
        if (peg.get_is_orange() && peg.get_is_active()){
            count++;
        }
    }
    return count;
}

void
Model::manage_decay()
{
    for (Peg& peg: all_pegs){

        if (peg.get_is_decaying()){
            if(!ball_.get_is_live()){
                peg.set_inactive();
            }
            else if (peg.get_frames_decayed()>=config_.decay_frames){
                peg.set_inactive();
            }
            else{
                peg.update_frames_decayed();
            }
        }
    }
}

void
Model::launch_ball(Positions pos)
{
    if (balls_remaining_>0){
        ball_.set_active();
        float x = (float)(pos.into<float>().x-(config_.scene_dims.width/2.0));
        float y = (float)(pos.into<float>().y-10.0);
        float mag = (2.0);

        x=x*config_.initial_velocity/mag;
        y=y*config_.initial_velocity/mag;
        ge211::geometry::Dims<float> v =  ge211::geometry::Dims<float>{x,y};

        ball_.set_velocity(v);
    }
}

void Model::check_conclusion() {
    if (num_orange_remaining()==0){
        won=true;
    }
    else if (balls_remaining_==0){
        lost = true;
    }
}

bool Model::get_won(){
    return won;
}
bool Model::get_lost(){
    return lost;
}


//on_frame needs to handle the reflection of the ball depending on what
// side the ball hits a peg (if any) - also responsible for setting the hit
// peg to inactive by using destroy_peg
//on_frame should also deal with managing decaying pegs with manage_decay()
void
Model::on_frame(double dt)
{
    Ball n_ball = ball_.next(dt);
    if (!ball_.get_is_live()) {
        manage_decay();
        return;
    }
    /// CHECK IF BALL HITS BALL CATCHER
    ///IF SO THEN BALLS REMAINING STAYS THE SAME

    if (ball_catch_.check_catcher_collision(n_ball)){
        ball_.set_inactive();
        manage_decay();
        ball_ = Ball(config_);
        return;
    }

    if (n_ball.hits_bottom(config_)) {
        ball_.set_inactive();
        balls_remaining_-=1;
        manage_decay();
        ball_ = Ball(config_);
        return;
    }
    if (n_ball.hits_top(config_)) {
        ball_.reflect_vertical();
    }
    if (n_ball.hits_side(config_)) {
        ball_.reflect_horizontal();
    }

    for (Peg& peg : all_pegs){

        if(ball_.hits_peg(peg)){
            if(ball_.hits_peg_side(peg)){
                ball_.reflect_horizontal();
            }
            if (ball_.hits_peg_top(peg)){
                ball_.reflect_vertical();
            }
            peg.set_decaying();
        }
    }

    manage_decay();
    if (ball_.get_is_live()){
        ball_ = ball_.next(dt);
    }
    check_conclusion();


    ball_catch_ = ball_catch_.next(dt);

    ball_catch_.catcher_hits_side(ball_catch_, config_);
}

Ball_Catcher::Ball_Catcher(Position bc_position_, Dimensions bc_velocity_):
        bc_position_(bc_position_),
        bc_velocity_(bc_velocity_)

{}
Position Ball_Catcher::get_bc_position() const {
    return bc_position_;
}

Dimensions Ball_Catcher::get_bc_velocity() const {
    return bc_velocity_;
}

Ball_Catcher Ball_Catcher::next(double dt) {
    Ball_Catcher result(*this);
    float d_x = result.bc_velocity_.width*dt;
    result.bc_position_= result.bc_position_.right_by(d_x);

    return result;
}

bool Ball_Catcher::catcher_hits_side(Ball_Catcher b, Game_config config){
    if (bc_position_.right_by(220).x > config.scene_dims.width || bc_position_.left_by(0).x < 0){
        bc_velocity_ *= -1;
        return true;
    }
    else{
        return false;
    }
}

bool Ball_Catcher::check_catcher_collision(Ball ball) {
    float rhs_ball = ball.get_center().right_by(5).x;
    float lhs_ball = ball.top_left().x;
    float top_ball = ball.top_left().y;
    float bot_ball = ball.get_center().down_by(5).y;

    Position catch_left = bc_position_;

    if (rhs_ball < catch_left.right_by(40).x || catch_left.right_by(200).x < lhs_ball) {
        return false;
    }
    if (bot_ball < catch_left.y || catch_left.down_by(50).y < top_ball){
        return false;
    }
    return true;

}

void Model::test_helper(){
    all_pegs.clear();
    all_pegs.emplace_back(Rectangle(500, 100, 25,25),true);
}


