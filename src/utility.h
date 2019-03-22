#ifndef SRC_UTILITY_H
#define SRC_UTILITY_H

#include <vector>
#include "rsdl.hpp"
#include "Geometry.h"

double closest_in_interval(double val, double interval_begin,
                           double interval_end);


rsdl::Rectangle convertToRectangle(ExactRectangle r);

template <typename Sub, typename Base> std::vector<Base*> cast_vector_elements(std::vector<Sub*> vec) {
    std::vector<Base*> result;
    for (int i = 0; i < vec.size(); i++)
        result.push_back((Base*)vec[i]);
    return result;
}

bool compare_floats(double a, double b, double epsilon = 0.1);

template <typename T> void delete_vector(std::vector<T*> vec) {
    for (int i = 0; i < vec.size(); i++)
        delete vec[i];
}

#endif
