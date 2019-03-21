#ifndef SRC_UTILITY_H
#define SRC_UTILITY_H

#include "rsdl.hpp"
#include "Geometry.h"

double closest_in_interval(double val, double interval_begin,
                           double interval_end);


rsdl::Rectangle convertToRectangle(ExactRectangle r);


#endif
