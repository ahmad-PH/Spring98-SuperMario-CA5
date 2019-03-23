#ifndef GAME_H
#define GAME_H

#include "rsdl.hpp"
#include "AssetsAddresses.h"
#include "Mario.h"
#include "Block.h"
#include "Brick.h"
#include <string>
#include <vector>

#define CELL_SIZE_PX 32

class Game {
public:
    Game();
    void run_level(std::string level_addr);
    ~Game();

private:
    void load_level(std::string level_addr);
    void load_map_cell(int x, int y, char cell);
    void draw_background();
    void draw();
    void handle_events();
    void update();
    void update_mario();
    void update_camera();
    void set_mario(Mario* mario);
    void add_block(Block* block);
    void add_brick(Brick* brick);
    void remove_brick(Brick* brick);


    rsdl::Window win;
    int camera_x;

    bool game_running;

    Mario* mario;
    std::vector<Block*> blocks;
    std::vector<Brick*> bricks;
    std::vector<Object*> obstacles;
    std::vector<Object*> objects;

};


#endif
