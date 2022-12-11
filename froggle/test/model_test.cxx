#include "model.hxx"
#include <catch.hxx>
#include "game_config.hxx"
#include "peg.hxx"

Game_config const config;

TEST_CASE("destroys peg")
{
    Model m(config);

    m.ball_.set_active();
    m.ball_.set_velocity({0,100});
    m.test_helper();
    CHECK(m.get_all_pegs().size()==1);
    CHECK(m.get_all_pegs().front().get_is_decaying() == false);

    m.on_frame(1);
    CHECK(m.ball_.hits_peg(m.get_all_pegs().front())==true);

    m.on_frame(1);

    CHECK(m.get_all_pegs().front().get_is_decaying() == true);
    CHECK(m.get_all_pegs().front().get_is_active() == true);

    for (int i=0 ; i<10; i++){
        m.on_frame(1);
    }
    CHECK(m.get_all_pegs().front().get_is_active() == false);

}

TEST_CASE("ball hits bottom + does not get returned to inventory"){
    Model m(config);

    m.test_helper();
    m.ball_.set_active();
    CHECK (m.ball_.get_is_live() == true);
    m.ball_.set_velocity({0, 759});
    int balls_before = m.get_balls_remaining();

    double const dt = 1;
    m.on_frame(dt);
    CHECK(m.ball_.get_is_live() == false);
    CHECK(m.ball_.get_center().y == 10);
    CHECK(m.get_balls_remaining() == balls_before -1);

}

TEST_CASE("ball falls into ball catcher + gets returned to inventory"){
    Model m(config);

    m.test_helper();
    m.ball_.set_active();
    m.ball_.set_velocity(ge211::Dims<float> {67, 345});
    int balls_before = m.get_balls_remaining();

    m.on_frame(1);
    m.on_frame(1);


    CHECK(m.ball_catch_.check_catcher_collision(m.ball_) == true);
    CHECK(m.get_balls_remaining() == balls_before);

    m.on_frame(1);
    CHECK(m.ball_.get_is_live() == false);

}


TEST_CASE("user wins when all the red pegs are cleared"){
    Model m(config);

    m.ball_.set_active();
    m.ball_.set_velocity({0,100});
    m.test_helper();
    m.on_frame(1);
    m.on_frame(1);

    for (int i=0 ; i<10; i++){
        m.on_frame(1);
    }
    CHECK(m.get_all_pegs().front().get_is_active() == false);
    m.check_conclusion();
    CHECK(m.get_won()==true);
}



TEST_CASE("user loses when they run out of balls and red pegs remain") {
    Model m(config);
    m.test_helper();

    CHECK(m.get_balls_remaining() == 10);
    for (int i = 0; i < 10; i++) {
        m.ball_.set_active();
        m.ball_.set_velocity(ge211::Dims<float>{200, 1000});
        m.on_frame(1);
    }
    CHECK(m.get_balls_remaining() == 0);
    CHECK(m.num_orange_remaining()==1);
    m.check_conclusion();
    CHECK(m.get_lost() == true);

}