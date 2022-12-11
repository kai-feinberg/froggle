//
// Created by Sara Kurniawan on 11/16/22.
//

#include "peg.hxx"

Peg::Peg(ge211::geometry::Rect<int> block, bool orange)
    :Rectangle(block),
    is_orange_(orange)
    {}

bool
Peg::get_is_active() const
{
    return this->is_active_;
}

bool Peg::get_is_decaying()
{
    return this->is_decaying_;
}
bool Peg::get_is_orange(){
    return this->is_orange_;
}
int Peg::get_frames_decayed()
{
    return this->frames_decayed_;
}

void Peg::update_frames_decayed()
{
    this->frames_decayed_+=1;
}

void Peg::set_inactive(){
    this->is_active_= false;
}

void Peg::set_decaying()
{
    this->is_decaying_=true;
}
