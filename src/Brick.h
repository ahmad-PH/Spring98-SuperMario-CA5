#ifndef SRC_BRICK_H
#define SRC_BRICK_H

#include "Geometry.h"
#include "Object.h"

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
    int animation_counter, animation_index;
    const static int animation_counter_divider, n_animation_frames;
};


#endif //SRC_BRICK_H
