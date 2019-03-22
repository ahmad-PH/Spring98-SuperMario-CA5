#include "Geometry.h"
#include "utility.h"


#include <iostream>
using namespace std;

bool ExactRectangle::intersects(ExactRectangle r) {

//    if (compare_floats(r.x,64) && compare_floats(r.y,416)) {
//        cout << "found rect: " << r << endl;
//        cout<< "me: "<<*this<<endl;
//        cout<<"decision: "<<res<<endl;
//    }
    return (x < r.x + w &&
            x + w > r.x &&
            y < r.y + r.h &&
            y + h > r.y);
}

ExactRectangle::ExactRectangle(double _x, double _y, int _w, int _h) :
    x(_x), y(_y), w(_w), h(_h) {}

std::ostream &operator<<(std::ostream &stream, const ExactRectangle r) {
     return stream << "(x: " << r.x << ", y: " << r.y << ", w: " << r.w << ", h: " << r.h
     << ")";
}

