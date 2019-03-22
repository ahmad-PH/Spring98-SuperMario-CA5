#include "Object.h"

Collision MovingObject::check_collision_on_next_frame(const Object* o) {
    ExactRectangle next_pos = get_position();
    next_pos.x += get_vx();
    next_pos.y += get_vy();

    if (!next_pos.intersects(o->get_position()))
        return Collision(false, false, false, false);

    ExactRectangle only_move_along_x = next_pos;
    only_move_along_x.y -= get_vy();
    if (!only_move_along_x.intersects(o->get_position()))
        return Collision(get_vy() > 0, get_vy() > 0, false, false);

    ExactRectangle only_move_along_y = next_pos;
    only_move_along_y.x -= get_vx();
    if (!only_move_along_y.intersects(o->get_position()))
        return Collision(false, false, get_vx() > 0, get_vx() > 0);

    //stops colliding only if you stop movement along both axes
    return Collision(get_vy() > 0, get_vy() > 0, get_vx() > 0, get_vx() > 0);
}

void MovingObject::move_one_frame_with_obstacles(const std::vector<Object*>& obstacles) {
    for (int i = 0; i < obstacles.size(); i++) {
        Collision collision = check_collision_on_next_frame(obstacles[i]);
        if (collision == Collision::NO_COLLISION)
            continue;

        ExactRectangle new_pos = get_position();
        double new_vx = get_vx(), new_vy = get_vy();
        if (collision.from_top) {
            new_pos.y = obstacles[i]->get_position().y - new_pos.h - 1;
            new_vy = 0;
        }
        if (collision.from_bottom) {
            new_pos.y = obstacles[i]->get_position().y + obstacles[i]->get_position().h + 1;
            new_vy = 0;
        }
        if (collision.from_right) {
            new_pos.x = obstacles[i]->get_position().x - new_pos.w - 1;
            new_vx = 0;
        }
        if (collision.from_left) {
            new_pos.x = obstacles[i]->get_position().x + obstacles[i]->get_position().w + 1;
            new_vx = 0;
        }

        set_position(new_pos);
        set_vx(new_vx);
        set_vy(new_vy);
    }

    move_one_frame();
}

void MovingObject::move_one_frame() {
    position.x += vx;
    vx = vx + ax;
    position.y += vy;
    vy = vy + ay;
}


Collision::Collision(bool from_top, bool from_bottom, bool from_left, bool from_right) {
    this->from_top = from_top;
    this->from_bottom = from_bottom;
    this->from_left = from_left;
    this->from_right = from_right;
}


Collision Collision::NO_COLLISION(false, false, false, false);

bool Collision::operator==(const Collision &c) {
    return from_top == c.from_top &&
           from_bottom == c.from_bottom &&
           from_right == c.from_right &&
           from_left == c.from_left;
}

