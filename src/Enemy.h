#ifndef SRC_ENEMY_H
#define SRC_ENEMY_H

#include "AutomaticMovingObject.h"
#include "AnimationIndexHandler.h"

class Enemy : public AutomaticMovingObject {
public:
    Enemy(ExactRectangle position, Game* game);
    void update() override;
    virtual void on_collision_with_mario(Collision col) = 0;
    bool is_dead() const { return _is_dead; }
protected:
    bool started_moving;
    bool _is_dead;
};

class LittleGoomba : public Enemy {
public:
    LittleGoomba(ExactRectangle position, Game* game);
    std::string get_image_addr() const override;
    void update() override;
    void on_collision_with_mario(Collision col) override;

private:
    AnimationIndexHandler animation_index_handler;
    int death_cleanup_counter;
};

class KoopaTroopa : public Enemy {
public:
    using Enemy::Enemy;
    std::string get_image_addr() const override;
    void on_collision_with_mario(Collision col) override;
};

#endif //SRC_ENEMY_H
