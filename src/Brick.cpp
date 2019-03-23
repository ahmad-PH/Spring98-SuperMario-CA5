#include "Brick.h"
#include "AssetsAddresses.h"
#include "utility.h"

using namespace std;

const double Brick::bump_speed = 2.5;

Brick::Brick(ExactRectangle position, Game* game) :
    Object(position, game) {
    vy = 0;
    original_y = position.y;
}

void Brick::on_collision_with_mario(Collision collision) {
    if (!collision.from_bottom)
        return;
    vy = -bump_speed;
    original_y = position.y;
}

void Brick::update() {
    position.y += vy;
    if (original_y - position.y >= 5) {
        vy = +bump_speed;
    } else if (position.y > original_y) {
        vy = 0;
        position.y = original_y;
    }
}

//===============================RegularBrick===============================

string RegularBrick::get_image_addr() const {
    return REGULAR_BRICK_ADDR;
}


//===============================QuestionBrick===============================
QuestionBrick::QuestionBrick(ExactRectangle position, Game* game) :
    Brick(position, game), animation_index_handler(2, 3) {
    is_empty = false;
}

void QuestionBrick::update() {
    Brick::update();
    animation_index_handler.next();
}

string QuestionBrick::get_image_addr() const {
    if (is_empty)
        return QUESTION_BRICK_ADDR "question-empty.png";
    else
        return  string(QUESTION_BRICK_ADDR) + "question-" +
                to_string(animation_index_handler.current() + 1) + ".png";
}

void QuestionBrick::on_collision_with_mario(Collision collision) {
    Brick::on_collision_with_mario(collision);

    if (!collision.from_bottom)
        return;
    is_empty = true;
}


