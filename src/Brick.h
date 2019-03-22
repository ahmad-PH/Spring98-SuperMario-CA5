#ifndef SRC_BRICK_H
#define SRC_BRICK_H

#include "Geometry.h"
#include "Object.h"

class Brick : public Object {
public:
    Brick(ExactRectangle position);
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
};


#endif //SRC_BRICK_H
