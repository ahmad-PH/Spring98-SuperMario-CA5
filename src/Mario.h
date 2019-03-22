#ifndef SRC_MARIO_H
#define SRC_MARIO_H

#include "rsdl.hpp"
#include "Object.h"
#include "Geometry.h"
#include <string>

class Mario : public MovingObject {
public:
    Mario(ExactRectangle position);
    void draw(rsdl::Window& win);
    void handle_key_press(char key);
    void handle_key_release(char key);
    virtual void move_one_frame();
    void set_vx(double vx) override;
    void set_vy(double vy) override;

private:
    enum State {STANDING, WALKING, JUMPING} state;
    enum Direction {LEFT, RIGHT} direction;
    enum Strength {NORMAL, BIG} strength;

    static double max_vx, max_vy;
};


#endif 
