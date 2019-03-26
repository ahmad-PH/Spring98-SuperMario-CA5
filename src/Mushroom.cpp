//
// Created by ahmad on 3/24/19.
//

#include "Mushroom.h"
#include "AssetsAddresses.h"
#include "Game.h"

std::string Mushroom::get_image_addr() const {
    return MUSHROOM_ADDR;
}

Mushroom::Mushroom(ExactRectangle position, Game *game) :
    AutomaticMovingObject(position, game) {
    vx = +10;
    start_of_movement_delay = 10;
}

void Mushroom::update() {
    start_of_movement_delay--;
    if (start_of_movement_delay > 0)
        return;
    AutomaticMovingObject::update();
}

void Mushroom::handle_interaction_with_mario(Mario *mario) {
    if (mario->collides(this))
        game->remove_object(this);
}
