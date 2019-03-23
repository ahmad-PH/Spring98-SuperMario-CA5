#ifndef SRC_MARIO_H
#define SRC_MARIO_H

#include "rsdl.hpp"
#include "Object.h"
#include "ExactRectangle.h"
#include "AnimationIndexHandler.h"
#include "Game.h"
#include <string>

class Mario : public MovingObject {
public:
    Mario(ExactRectangle position, Game* game);
    std::string get_image_addr() const override;
    void handle_key_press(char key);
    void handle_key_release(char key);
    void set_vx(double vx) override;
    void set_vy(double vy) override;
    virtual void update();

private:
    virtual void move_one_frame();
    void update_state();
    void update_direction();
    bool is_touching_ground();
    void apply_friction();
    void handle_jump_continuation();
    void avoid_exiting_left_edge_of_screen();

    enum State {STANDING, WALKING, JUMPING, SLIDING} state;
    enum Direction {LEFT, RIGHT} direction;
    enum Strength {NORMAL, BIG} strength;

    int jump_timer;
    bool jump_key_held;
    AnimationIndexHandler walk_index_handler;

    static const double max_vx, max_vy;
    static const double friction_constant, stop_threshold;
    static const int walking_counter_divider, n_walking_frames;
    static const int max_jump_time;

};


#endif 
