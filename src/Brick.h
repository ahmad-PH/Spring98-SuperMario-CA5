#ifndef SRC_BRICK_H
#define SRC_BRICK_H

#include "Geometry.h"
#include "Object.h"

class Brick : public Object {
public:
    Brick(ExactRectangle position);
    void draw(rsdl::Window &win) override;
};


#endif //SRC_BRICK_H
