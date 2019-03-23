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
    ExactRectangle relative_to_x(int x);

    double x,y;
    int w,h;
};
std::ostream& operator<<(std::ostream &stream, const ExactRectangle);

#endif
