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
    _is_dead = false;
}

//=================================LittleGoomba================================

LittleGoomba::LittleGoomba(ExactRectangle position, Game *game) :
        Enemy(position, game), animation_index_handler(2, 2) {}

std::string LittleGoomba::get_image_addr() const {
    string img_name;
    if (_is_dead)
        img_name = "dead";
    else
        img_name = string("walking-") + to_string(animation_index_handler.current() + 1);
    return string(LITTLE_GOOMBA_ADDR) + img_name + ".png";
}

void LittleGoomba::update() {
    Enemy::update();
    animation_index_handler.next();
    if (_is_dead) {
        death_cleanup_counter--;
        if (death_cleanup_counter <= 0)
            game->remove_enemy(this);
    }
}

void LittleGoomba::on_collision_with_mario(Collision col) {
    if (col.from_top) {
        _is_dead = true;
        vx = vy = ax = ay = 0;
        death_cleanup_counter = 10;
    }
}


//=================================KoopaTroopa================================
std::string KoopaTroopa::get_image_addr() const {
    return KOOPA_TROOPA_ADDR "walking-right-1.png";
}

void KoopaTroopa::on_collision_with_mario(Collision col) {

}
