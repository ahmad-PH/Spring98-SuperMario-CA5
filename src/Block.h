#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include "rsdl.hpp"
#include "Object.h"
#include "Geometry.h"

class Block : public Object {
public:
    Block(ExactRectangle position, std::string image_addr);
    virtual void draw(rsdl::Window &win) ;

private:
    std::string image_addr;
};

#endif
