#include "Object.h"

Collision MovingObject::check_collision_on_next_frame(Object &o) {
    Rectangle next_pos = get_position();
    next_pos.x += get_vx();
    next_pos.y += get_vy();

    if (!next_pos.intersects(o.get_position()))
        return Collision(false, false, false, false);

    Rectangle only_move_along_x = next_pos;
    only_move_along_x.y -= get_vy();
    if (!only_move_along_x.intersects(o.get_position()))
        return Collision(get_vy() > 0, get_vy() > 0, false, false);

    Rectangle only_move_along_y = next_pos;
    only_move_along_y.x -= get_vx();
    if (!only_move_along_y.intersects(o.get_position()))
        return Collision(false, false, get_vx() > 0, get_vx() > 0);

    //stops colliding only if you stop movement along both axes
    return Collision(get_vy() > 0, get_vy() > 0, get_vx() > 0, get_vx() > 0);

}

Collision::Collision(bool from_top, bool from_bottom, bool from_left, bool from_right) {
    this->from_top = from_top;
    this->from_bottom = from_bottom;
    this->from_left = from_left;
    this->from_right = from_right;
}
