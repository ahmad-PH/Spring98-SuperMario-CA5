#ifndef SRC_ENEMY_H
#define SRC_ENEMY_H

#include "AutomaticMovingObject.h"
#include "AnimationIndexHandler.h"

class Enemy : public AutomaticMovingObject {
public:
    Enemy(ExactRectangle position, Game* game);
    void update() override;
protected:
    bool started_moving;
};

class LittleGoomba : public Enemy {
public:
    LittleGoomba(ExactRectangle position, Game* game);
    std::string get_image_addr() const override;
    void update() override;
private:
    AnimationIndexHandler animation_index_handler;
};

class KoopaTroopa : public Enemy {
public:
    using Enemy::Enemy;
    std::string get_image_addr() const override;
};

#endif //SRC_ENEMY_H
