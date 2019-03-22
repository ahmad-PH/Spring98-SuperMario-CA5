#include "Mario.h"
#include "AssetsAddresses.h"
#include "Physics.h"
#include "utility.h"

using namespace std;


const double Mario::max_vx = 15;
const double Mario::max_vy = 25;
const double Mario::friction_constant = 0.18;
const int Mario::walking_counter_divider = 1000;
const int Mario::n_walking_frames = 3;
const int Mario::max_jump_time = 6;


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

    if (state == WALKING) {
        address+= "-" + to_string(walking_index + 1);
    }

    address += ".png";

    win.draw_img(address, convertToRectangle(position));
}

void Mario::handle_key_press(char key) {

    if (key == 'd') {
        ax = 2;
    } else if (key == 'a') {
        ax = -2;
    } else if (key == 'w') {
        if (state != JUMPING) {
            vy = -15;
            ay = 0;
            jump_timer = max_jump_time;
        }
    }
}

void Mario::handle_key_release(char key) {
    cout<<"key release called: "<<key<<" "<<ax<<endl;
    if (key == 'd' && ax >= 0) {
        ax = 0;
    } else if (key == 'a' && ax < 0) {
        ax = 0;
    } else if (key == 'w') {
        ay = GRAVITATIONAL_ACCELERATION;
        jump_timer = 0;
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
    vx = max(min(vx, max_vx), -max_vx);
    vy = max(min(vy + ay, max_vy), -max_vy);
}


void Mario::update(const std::vector<Object *> &obstacles) {
    move_one_frame_with_obstacles(obstacles);
    apply_friction();
    update_state(obstacles);
    update_direction();
    handle_jump_timer();
}

void Mario::update_state(const std::vector<Object *> &obstacles) {
    if (!is_touching_ground(obstacles)) {
        state = JUMPING;
    } else if (vx != 0) {
        if (state != WALKING) {
            state = WALKING;
            walking_counter = walking_index = 0;
        } else {
            walking_counter++;
            walking_index = (walking_counter % walking_counter_divider) % n_walking_frames;
        }
    } else {
        state = STANDING;
    }
}

bool Mario::is_touching_ground(const vector<Object *>& obstacles) {
    bool result = false;
    for (int i = 0; i < obstacles.size(); i++) {
        if (compare_floats(obstacles[i]->get_position().y, position.y + position.h)) {
            result = true;
//            cout<<"mario: "<<get_position()<<" is touching: "<<obstacles[i]->get_position()<<endl;
        }
    }
    return result;
}

void Mario::update_direction() {
    if (vx > 0) {
        direction = RIGHT;
    } else if (vx < 0) {
        direction = LEFT;
    }
}

void Mario::apply_friction() {
    if (ax != 0 || vx == 0)
        return;

    if (state == WALKING) {
        if (vx > 0) {
            vx = max(vx - (friction_constant * vx), 0.0);
            if (vx < 2)
                vx = 0;
        }
        else if (vx < 0) {
            vx = min(vx - (friction_constant * vx), 0.0);
            if (vx > -2)
                vx = 0;
        }
    }
}

void Mario::handle_jump_timer() {
    if (jump_timer > 0)
        jump_timer--;
    if (jump_timer == 0)
        ay = GRAVITATIONAL_ACCELERATION;
}
