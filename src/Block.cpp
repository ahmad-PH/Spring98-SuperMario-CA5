#include "Block.h"
#include "utility.h"

Block::Block(ExactRectangle position, std::string image_addr) {
    this->position = position;
    this->image_addr = image_addr;
}

std::string Block::get_image_addr() const {
    return image_addr;
}

