#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include "rsdl.hpp"

class Block {
public:
    Block(Rectangle position, std::string image_addr);
    void draw(Window& win);

private:
    Rectangle position;
    std::string image_addr;
};

#endif
