#include "Collision.h"

Collision::Collision(bool from_top, bool from_bottom, bool from_left, bool from_right) {
    this->from_top = from_top;
    this->from_bottom = from_bottom;
    this->from_left = from_left;
    this->from_right = from_right;
}

Collision::Collision() {
    this->from_top = this->from_bottom = this->from_right = this->from_left = false;
}

Collision Collision::NO_COLLISION(false, false, false, false);

bool Collision::operator==(const Collision &c) {
    return from_top == c.from_top &&
           from_bottom == c.from_bottom &&
           from_right == c.from_right &&
           from_left == c.from_left;
}

Collision Collision::aggregate(Collision col) const {
    Collision result = *this;
    result.from_top = result.from_top || col.from_top;
    result.from_bottom = result.from_bottom || col.from_bottom;
    result.from_left = result.from_left || col.from_left;
    result.from_right = result.from_right || col.from_right;
    return result;
}
