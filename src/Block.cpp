#include "Block.h"

Block::Block(Rectangle _position, std::string image_addr) : position(_position){
    this->image_addr = image_addr;
}

void Block::draw(Window &win) {
    win.draw_img(image_addr, position);
}
