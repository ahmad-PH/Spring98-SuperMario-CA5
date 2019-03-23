#ifndef SRC_BRICK_H
#define SRC_BRICK_H

#include "Geometry.h"
#include "Object.h"
#include "AnimationIndexHandler.h"

class Brick : public Object {
public:
    Brick(ExactRectangle position);
    virtual void update() {}
};

class RegularBrick : public Brick {
public:
    using Brick::Brick;
    virtual std::string get_image_addr() const;
};

class QuestionBrick : public Brick {
public:
    QuestionBrick(ExactRectangle position);
    virtual std::string get_image_addr() const;
    virtual void update();
private:
    AnimationIndexHandler animation_index_handler;
};


#endif //SRC_BRICK_H
