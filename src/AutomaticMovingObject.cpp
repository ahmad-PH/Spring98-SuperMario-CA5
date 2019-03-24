//
// Created by ahmad on 3/25/19.
//

#include "AutomaticMovingObject.h"
#include "Game.h"

void AutomaticMovingObject::update() {
    double initial_vx = vx;
    Collision collision = move_one_frame_with_obstacles(game->get_obstacles());
    if (collision.from_left || collision.from_right)
        vx = -initial_vx;
    update_direction();
}

