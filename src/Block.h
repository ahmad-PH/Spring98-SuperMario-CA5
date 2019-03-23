#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include "rsdl.hpp"
#include "Object.h"
#include "Geometry.h"

class Block : public Object {
public:
    Block(ExactRectangle position, std::string image_addr, Game* game);
    std::string get_image_addr() const override;

    void update() override;

private:
    std::string image_addr;
};

#endif
