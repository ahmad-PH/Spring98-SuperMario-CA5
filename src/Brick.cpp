#include "Brick.h"
#include "AssetsAddresses.h"
#include "utility.h"

Brick::Brick(ExactRectangle position) {
    this->position = position;
}

//===============================RegularBrick===============================

void RegularBrick::draw(rsdl::Window &win) {
    win.draw_img(REGULAR_BRICK_ADDR, convertToRectangle(position));
}

//===============================QuestionBrick===============================
const int QuestionBrick::animation_counter_divider = 4;
const int QuestionBrick::n_animation_frames = 3;

void QuestionBrick::draw(rsdl::Window &win) {
    win.draw_img(QUESTION_BRICK_ADDR "question-1.png", convertToRectangle(position));
}

QuestionBrick::QuestionBrick(ExactRectangle position) : Brick(position) {
    animation_counter = 0;
}

void QuestionBrick::update() {
//    animation_counter = (animation_counter + 1) %;
}
