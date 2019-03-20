#include "Geometry.h"

bool Rectangle::intersects(Rectangle r) {
    return (x <= r.x + w &&
            x + w >= r.x &&
            y <= r.y + r.h &&
            y + h >= r.y);
}
