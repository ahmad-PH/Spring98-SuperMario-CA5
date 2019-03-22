#include "Brick.h"
#include "AssetsAddresses.h"
#include "utility.h"

using namespace std;

Brick::Brick(ExactRectangle position) {
    this->position = position;
}

//===============================RegularBrick===============================

void RegularBrick::draw(rsdl::Window &win) {
    win.draw_img(REGULAR_BRICK_ADDR, convertToRectangle(position));
}

//===============================QuestionBrick===============================
void QuestionBrick::draw(rsdl::Window &win) {
    string address = string(QUESTION_BRICK_ADDR) + "question-" +
                     to_string(animation_index_handler.current() + 1) + ".png";
    win.draw_img(address, convertToRectangle(position));
}

QuestionBrick::QuestionBrick(ExactRectangle position) :
    Brick(position), animation_index_handler(2, 3) {}

void QuestionBrick::update() {
    animation_index_handler.next();
}
