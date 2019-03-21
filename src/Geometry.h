#ifndef SRC_GEOMETRY_H
#define SRC_GEOMETRY_H

#include "rsdl.hpp"

//class Rectangle : public rsdl::Rectangle {
//public:
//    using rsdl::Rectangle::Rectangle;
//};

struct ExactRectangle {
    ExactRectangle(double x, double y, int w, int h);
    ExactRectangle() {}
    bool intersects(ExactRectangle r);

    double x,y;
    int w,h;
};

#endif
