//
// Created by ahmad on 3/18/19.
//

#include "Mario.h"
#include "AssetsAddresses.h"

using namespace std;

Mario::Mario(Rectangle _position) : position(_position) {
    state = STANDING;
    direction = RIGHT;
    strength = NORMAL;
    ay = +10;
    exact_x = _position.x;
    exact_y = _position.y;
}

void Mario::draw(Window& win) {
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
        ax = 5;
    } else if (key == 'a') {
        ax = -5;
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
        ay = ;
    }
}

void Mario::update() {
    exact_x += vx;
    vx += ax;
    exact_y += vy;
    vy += ay;
    position = Rectangle(exact_x, exact_x, position.w, position.h);
}
