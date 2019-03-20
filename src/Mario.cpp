#include "Mario.h"
#include "AssetsAddresses.h"
#include "Physics.h"

using namespace std;

Mario::Mario(Rectangle _position) : position(_position) {
    state = STANDING;
    direction = RIGHT;
    strength = NORMAL;

    exact_x = position.x;
    exact_y = position.y;
    cout<<"mario position:"<<position<<endl;

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

//    cout<<address<<endl;
    win.draw_img(address, position);
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

void Mario::update() {

//    auto t_end = std::chrono::high_resolution_clock::now();
//    cout<<"duration: "<<std::chrono::duration<double, std::milli>(t_end - t_start).count()<<endl;
//    cout<<"updated pos:"<<position<<endl;
//    cout<<"vx: "<<vx<<" vy: "<<vy<<endl;
//    cout<<"ax: "<<ax<<" ay: "<<ay<<endl;
    exact_x += vx;
    vx = max(min(vx + ax, max_vx), -max_vx);
    exact_y += vy;
    vy = min(vy + ay, max_vy);
    position = Rectangle(exact_x, exact_y, position.w, position.h);

//    t_start = std::chrono::high_resolution_clock::now();
}


double Mario::max_vx = 4;
double Mario::max_vy = 8;

Rectangle Mario::get_position() {
    return position;
}

double Mario::get_vx() {
    return vx;
}

double Mario::get_vy() {
    return vy;
}
