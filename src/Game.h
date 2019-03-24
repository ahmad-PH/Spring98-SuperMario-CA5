#ifndef GAME_H
#define GAME_H

#include "rsdl.hpp"
#include "AssetsAddresses.h"
#include "Mario.h"
#include "Block.h"
#include "Brick.h"
#include "Enemy.h"
#include <string>
#include <vector>

#define CELL_SIZE_PX 32

class Mario;

class Game {
public:
    Game();
    void run_level(std::string level_addr);
    ~Game();

    std::vector<Object*> get_obstacles() const { return obstacles; }
    int get_camera_x() const { return camera_x; }
    void remove_object(Object* object);
    void add_object(Object* object);
    void increment_coin();
    rsdl::Window* get_window() { return &win; }

private:
    void load_level(std::string level_addr);
    void load_map_cell(int x, int y, char cell);
    void draw_background();
    void draw();
    void handle_events();
    void update();
    void update_camera();
    void set_mario(Mario* mario);
    void add_block(Block* block);
    void add_brick(Brick* brick);
    void remove_brick(Brick* brick);
    void add_enemy(Enemy* enemy);
    void remove_enemy(Enemy* enemy);
    void handle_object_interactions();
    void draw_banner();

    rsdl::Window win;
    int camera_x;
    bool game_running;
    Mario* mario;
    int n_coins, n_lives;

    std::vector<Block*> blocks;
    std::vector<Brick*> bricks;
    std::vector<Enemy*> enemies;
    std::vector<Object*> obstacles;
    std::vector<Object*> objects;
};


#endif
