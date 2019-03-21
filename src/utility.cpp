#include "utility.h"

double closest_in_interval(double val, double interval_begin,
                           double interval_end) {
    if (val > interval_end)
        return interval_end;
    if (val < interval_begin)
        return interval_begin;
    return val;
}