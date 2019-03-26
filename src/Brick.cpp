#include "Brick.h"
#include "AssetsAddresses.h"
#include "utility.h"
#include "Game.h"
#include "Coin.h"
#include "Mushroom.h"

using namespace std;

const double Brick::bump_speed = 2.5;

Brick::Brick(ExactRectangle position, Game* game) :
    Object(position, game) {
    vy = 0;
    original_y = position.y;
}

void Brick::handle_interaction_with_mario(Mario* mario) {
    if (!mario->check_collision_on_next_frame(this).from_bottom)
        return;
    vy = -bump_speed;
}

void Brick::update() {
    position.y += vy;
    if (original_y - position.y >= 5) {
        vy = bump_speed;
    } else if (position.y > original_y) {
        vy = 0;
        position.y = original_y;
    }
}

//===============================RegularBrick===============================

string RegularBrick::get_image_addr() const {
    return REGULAR_BRICK_ADDR;
}

void RegularBrick::handle_interaction_with_mario(Mario *mario) {
    Brick::handle_interaction_with_mario(mario);

    if (mario->check_collision_on_next_frame(this).from_bottom &&
        mario->get_strength() == Mario::BIG)
        game->remove_brick(this);
}


//===============================QuestionBrick===============================
QuestionBrick::QuestionBrick(ExactRectangle position, Game* game, BrickContent content) :
    Brick(position, game), animation_index_handler(2, 3) {
    is_empty = false;
    this->content = content;
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

void QuestionBrick::handle_interaction_with_mario(Mario* mario) {
    Brick::handle_interaction_with_mario(mario);

    if (!mario->check_collision_on_next_frame(this).from_bottom || is_empty)
        return;

    is_empty = true;
    ExactRectangle content_spawn_position = position;
    content_spawn_position.y -= CELL_SIZE_PX;

    if (content == COIN) {
        game->add_object(new Coin(content_spawn_position, game));
        game->increment_coin();
    } else if (content == MUSHROOM)
        game->add_object(new Mushroom(content_spawn_position, game));
}


