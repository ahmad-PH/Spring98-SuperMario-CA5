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
    void set_vx(double vx) override;
    void set_vy(double vy) override;
    void update(const std::vector<Object *> &obstacles);

private:
    virtual void move_one_frame();

    void apply_friction();
    void update_state(const std::vector<Object*>& obstacles);

    enum State {STANDING, WALKING, JUMPING} state;
    enum Direction {LEFT, RIGHT} direction;
    enum Strength {NORMAL, BIG} strength;

    static double max_vx, max_vy;
    static double friction_constant;
};


#endif 
