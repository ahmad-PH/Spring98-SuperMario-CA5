#include "Enemy.h"
#include "AssetsAddresses.h"
#include "Game.h"

using namespace std;

void Enemy::update() {
    AutomaticMovingObject::update();
    if (game->get_camera_x() + game->get_window()->get_width() > position.x &&
        !started_moving) {
        started_moving = true;
        vx = -5;
    }
}

Enemy::Enemy(ExactRectangle position, Game *game) :
    AutomaticMovingObject(position, game) {
    vx = vy = ax = 0;
    ay = GRAVITATIONAL_ACCELERATION;
    started_moving = false;
}

std::string KoopaTroopa::get_image_addr() const {
    return KOOPA_TROOPA_ADDR "walking-right-1.png";
}

std::string LittleGoomba::get_image_addr() const {
    return string(LITTLE_GOOMBA_ADDR) + "walking-" + to_string(animation_index_handler.current() + 1) + ".png";
}

LittleGoomba::LittleGoomba(ExactRectangle position, Game *game) :
    Enemy(position, game), animation_index_handler(2, 2) {}

void LittleGoomba::update() {
    Enemy::update();
    animation_index_handler.next();
}
