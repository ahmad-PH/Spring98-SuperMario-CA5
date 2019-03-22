#include "Brick.h"
#include "AssetsAddresses.h"
#include "utility.h"

Brick::Brick(ExactRectangle position) {
    this->position = position;
}

void RegularBrick::draw(rsdl::Window &win) {
    win.draw_img(REGULAR_BRICK_ADDR, convertToRectangle(position));
}

void QuestionBrick::draw(rsdl::Window &win) {
    win.draw_img(QUESTION_BRICK_ADDR "question-1.png", convertToRectangle(position));
}

QuestionBrick::QuestionBrick(ExactRectangle position) : Brick(position) {

}
