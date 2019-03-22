#include "Mario.h"
#include "AssetsAddresses.h"
#include "Physics.h"
#include "utility.h"

using namespace std;


double Mario::max_vx = 4;
double Mario::max_vy = 8;
double Mario::friction_constant = 0.5;



Mario::Mario(ExactRectangle _position) {
    state = STANDING;
    direction = RIGHT;
    strength = NORMAL;

    position = _position;
    vx = vy = ax = 0;
    ay = GRAVITATIONAL_ACCELERATION;
}

void Mario::draw(rsdl::Window& win) {
    string address = MARIO_ADDR;

    if (strength == NORMAL)
        address += "/normal";
    else if (strength == BIG)
        address += "/big";

    if (state == STANDING)
        address += "/standing";
    else if (state == WALKING)
        address += "/walking";
    else if (state == JUMPING)
        address += "/jumping";

    if (direction == RIGHT)
        address += "-right";
    else if (direction == LEFT)
        address += "-left";

    address += ".png";

    win.draw_img(address, convertToRectangle(position));
}

void Mario::handle_key_press(char key) {

    if (key == 'd') {
        ax = 0.5;
    } else if (key == 'a') {
        ax = -0.5;
    } else if (key == 'w') {
        if (state != JUMPING) {
            vy = -10;
        }
    }
}

void Mario::handle_key_release(char key) {
    if (key == 'd' && ax >= 0) {
        ax = 0;
    } else if (key == 'a' && ax < 0) {
        ax = 0;
    } else if (key == 'w' && ay == 0) {
        ay = GRAVITATIONAL_ACCELERATION;
    }
}

//#include <ctime>
//#include <chrono>
//auto t_start = std::chrono::high_resolution_clock::now();

void Mario::set_vx(double vx) {
    this->vx = closest_in_interval(vx, -max_vx, max_vx);
}

void Mario::set_vy(double vy) {
    this->vy = closest_in_interval(vy, -max_vy, max_vy);
}

void Mario::move_one_frame() {
    MovingObject::move_one_frame();
    apply_friction();
    vx = max(min(vx, max_vx), -max_vx);
    vy = max(min(vy + ay, max_vy), -max_vy);
}

void Mario::apply_friction() {
    cout<<"in apply friction: "<<state<<endl;
    if (state == WALKING) {
        if (vx > 0)
            vx = max(vx-friction_constant, 0.0);
        else if (vx < 0)
            vx = min(vx+friction_constant, 0.0);
    }
}


void Mario::update(const std::vector<Object *> &obstacles) {
    move_one_frame_with_obstacles(obstacles);
    update_state(obstacles);
    apply_friction();
}

void Mario::update_state(const std::vector<Object *> &obstacles) {
    cout<<"in update state, mario pos: "<<get_position()<<endl;
    bool touching_ground = false;
    for (int i = 0; i < obstacles.size(); i++) {
        if (compare_floats(obstacles[i]->get_position().y, position.y + position.h)) {
            touching_ground = true;
            cout<<"mario: "<<get_position()<<" is touching: "<<obstacles[i]->get_position()<<endl;
        }
    }
    if (!touching_ground)
        state = JUMPING;
    else if (vx != 0)
        state = WALKING;
    else
        state = STANDING;
}



