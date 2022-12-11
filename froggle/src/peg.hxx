//
// Created by Sara Kurniawan on 11/16/22.
//

#ifndef GAME_PEG_HXX
#define GAME_PEG_HXX
#pragma once
  #include "game_config.hxx"

  #include <ge211.hxx>

#endif //GAME_PEG_HXX
using Dimensions = ge211::Dims<int>;
using Positions = ge211::Posn<int>;
using Rectangle = struct ge211::geometry::Rect<int>;

struct Peg : public Rectangle {

    ///CONSTRUCTOR -- need to initialize rectangle too

public:
    Peg(Rectangle block, bool orange);
    bool get_is_active() const;
    bool get_is_decaying();
    bool get_is_orange();
    int get_frames_decayed();
    void update_frames_decayed();

    void set_inactive();
    void set_decaying();


    ///member variables
private:
    bool is_active_=true;
    bool is_decaying_=false;
    bool is_orange_;  //will be initialized in constructor
    int frames_decayed_=0;
};