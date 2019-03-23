#include "Brick.h"
#include "AssetsAddresses.h"
#include "utility.h"

using namespace std;

Brick::Brick(ExactRectangle position) {
    this->position = position;
}

//===============================RegularBrick===============================

string RegularBrick::get_image_addr() const {
    return REGULAR_BRICK_ADDR;
}

//===============================QuestionBrick===============================
QuestionBrick::QuestionBrick(ExactRectangle position) :
    Brick(position), animation_index_handler(2, 3) {}

void QuestionBrick::update() {
    animation_index_handler.next();
}

string QuestionBrick::get_image_addr() const {
    return  string(QUESTION_BRICK_ADDR) + "question-" +
            to_string(animation_index_handler.current() + 1) + ".png";
}

