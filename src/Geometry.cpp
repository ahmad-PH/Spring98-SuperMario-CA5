#include "Geometry.h"

bool ExactRectangle::intersects(ExactRectangle r) {
    return (x <= r.x + w &&
            x + w >= r.x &&
            y <= r.y + r.h &&
            y + h >= r.y);
}

ExactRectangle::ExactRectangle(double _x, double _y, int _w, int _h) :
    x(_x), y(_y), w(_w), h(_h) {}
