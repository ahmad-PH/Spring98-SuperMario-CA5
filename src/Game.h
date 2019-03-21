#ifndef GAME_H
#define GAME_H

#include "rsdl.hpp"
#include "AssetsAddresses.h"
#include "Mario.h"
#include "Block.h"
#include <string>
#include <vector>

#define CELL_SIZE_PX 32

class Game {
public:
    Game();
    void run_level(std::string level_addr);
    void draw_background();
    void draw();
    ~Game();

private:
    void load_level(std::string level_addr);
    void load_map_cell(int x, int y, char cell);
    void handle_events();
    void update();
    void update_mario();

    rsdl::Window win;
    int camera_x;

    bool game_running;

    Mario* mario;
    std::vector<Block> blocks;

};


#endif
