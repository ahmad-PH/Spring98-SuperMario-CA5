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
    void draw(rsdl::Window &win) override;
};

class QuestionBrick : public Brick {
public:
    QuestionBrick(ExactRectangle position);
    void draw(rsdl::Window &win) override;
    virtual void update();
private:
    AnimationIndexHandler animation_index_handler;
};


#endif //SRC_BRICK_H
