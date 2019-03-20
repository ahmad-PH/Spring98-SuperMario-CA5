#ifndef SRC_OBJECT_H
#define SRC_OBJECT_H

#include "Geometry.h"

class Object {
public:
    virtual Rectangle get_position() = 0;
};


struct Collision {
    bool from_top, from_bottom, from_left, from_right;
    Collision(bool from_top, bool from_bottom, bool from_left, bool from_right);
};


class MovingObject : public Object {
    virtual double get_vx() = 0;
    virtual double get_vy() = 0;
    Collision check_collision_on_next_frame(Object &o);
};


#endif
