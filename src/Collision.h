#ifndef SRC_COLLISION_H
#define SRC_COLLISION_H

struct Collision {
    bool from_top, from_bottom, from_left, from_right;
    Collision(bool from_top, bool from_bottom, bool from_left, bool from_right);
    Collision();
    Collision aggregate(Collision col) const;
    bool operator==(const Collision& c);
    bool operator!=(const Collision& c);

    static Collision NO_COLLISION;
};


#endif //SRC_COLLISION_H
