#ifndef SRC_BRICK_H
#define SRC_BRICK_H

#include "Geometry.h"
#include "Object.h"
#include "AnimationIndexHandler.h"

class Brick : public Object {
public:
    Brick(ExactRectangle position);
    virtual void update() = 0;
    virtual void on_collision_with_mario(Collision collision) = 0;
};

class RegularBrick : public Brick {
public:
    RegularBrick(ExactRectangle position);
    virtual std::string get_image_addr() const;
    virtual void update();
    virtual void on_collision_with_mario(Collision collision);
private:
    double vy;
    double original_y;
    const static double bump_speed;
};

class QuestionBrick : public Brick {
public:
    QuestionBrick(ExactRectangle position);
    virtual std::string get_image_addr() const;
    virtual void update();
    virtual void on_collision_with_mario(Collision collision);
private:
    AnimationIndexHandler animation_index_handler;
};


#endif //SRC_BRICK_H
