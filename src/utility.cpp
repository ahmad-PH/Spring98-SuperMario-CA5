#include "utility.h"

double closest_in_interval(double val, double interval_begin,
                           double interval_end) {
    if (val > interval_end)
        return interval_end;
    if (val < interval_begin)
        return interval_begin;
    return val;
}

rsdl::Rectangle convertToRectangle(ExactRectangle r) {
    return rsdl::Rectangle((int)r.x, (int)r.y, r.w, r.h);
}

bool compare_floats(double a, double b, double epsilon) {
    return fabs(a - b) < epsilon;
}