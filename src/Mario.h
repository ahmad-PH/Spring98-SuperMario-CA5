#ifndef SRC_MARIO_H
#define SRC_MARIO_H

#include "rsdl.hpp"
#include "Object.h"
#include "Geometry.h"
#include <string>

class Mario : public MovingObject {

public:
    Mario(Rectangle position);
    void draw(rsdl::Window& win);
    void handle_key_press(char key);
    void handle_key_release(char key);
    void update();
    virtual Rectangle get_position() override;

private:
    double get_vx() override;

    double get_vy() override;

private:
    Rectangle position;
    enum State {STANDING, WALKING, JUMPING} state;
    enum Direction {LEFT, RIGHT} direction;
    enum Strength {NORMAL, BIG} strength;

    double vx, vy;
    double ax, ay;
    double exact_x, exact_y;

    static double max_vx, max_vy;
};


#endif 
