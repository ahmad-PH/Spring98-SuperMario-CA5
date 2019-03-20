#ifndef SRC_GEOMETRY_H
#define SRC_GEOMETRY_H

#include "rsdl.hpp"

class Rectangle : public rsdl::Rectangle {
public:
    using rsdl::Rectangle::Rectangle;
    bool intersects(Rectangle r);
};

#endif
