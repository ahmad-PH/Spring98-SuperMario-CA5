#include "Brick.h"
#include "AssetsAddresses.h"
#include "utility.h"

using namespace std;

Brick::Brick(ExactRectangle position) {
    this->position = position;
}

//===============================RegularBrick===============================
const double RegularBrick::bump_speed = 2.5;

RegularBrick::RegularBrick(ExactRectangle position) : Brick(position) {
    vy = 0;
    original_y = position.y;
}

string RegularBrick::get_image_addr() const {
    return REGULAR_BRICK_ADDR;
}

void RegularBrick::on_collision_with_mario(Collision collision) {
    if (!collision.from_bottom)
        return;

    vy = -bump_speed;
    original_y = position.y;
}

void RegularBrick::update() {
    position.y += vy;
    if (original_y - position.y >= 5) {
        vy = +bump_speed;
    } else if (position.y > original_y) {
        vy = 0;
        position.y = original_y;
    }
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

void QuestionBrick::on_collision_with_mario(Collision collision) {

}


