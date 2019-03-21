#include "Mario.h"
#include "AssetsAddresses.h"
#include "Physics.h"
#include "utility.h"

using namespace std;

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

    rsdl::Rectangle drawing_position((int)position.x, (int)position.y, position.w, position.h);
    win.draw_img(address, drawing_position);
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

#include <ctime>
#include <chrono>
auto t_start = std::chrono::high_resolution_clock::now();


double Mario::max_vx = 4;
double Mario::max_vy = 8;

ExactRectangle Mario::get_position() const{
    return position;
}

double Mario::get_vx() {
    return vx;
}

double Mario::get_vy() {
    return vy;
}

void Mario::set_position(ExactRectangle position) {
    this->position = position;
}

void Mario::set_vx(double vx) {
    this->vx = closest_in_interval(vx, -max_vx, max_vx);
}

void Mario::set_vy(double vy) {
    this->vy = closest_in_interval(vy, -max_vy, max_vy);
}

void Mario::move_one_frame() {

//    auto t_end = std::chrono::high_resolution_clock::now();
//    cout<<"duration: "<<std::chrono::duration<double, std::milli>(t_end - t_start).count()<<endl;
//    cout<<"updated pos:"<<position<<endl;
//    cout<<"vx: "<<vx<<" vy: "<<vy<<endl;
//    cout<<"ax: "<<ax<<" ay: "<<ay<<endl;
    position.x += vx;
    vx = max(min(vx + ax, max_vx), -max_vx);
    position.y += vy;
    vy = min(vy + ay, max_vy);
    position = ExactRectangle(position.x, position.y, position.w, position.h);

//    t_start = std::chrono::high_resolution_clock::now();

}