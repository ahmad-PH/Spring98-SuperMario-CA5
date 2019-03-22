#include "Block.h"
#include "utility.h"

Block::Block(ExactRectangle position, std::string image_addr) {
    this->position = position;
    this->image_addr = image_addr;
}

void Block::draw(rsdl::Window &win) {
    win.draw_img(image_addr, convertToRectangle(position));
}

