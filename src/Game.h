#ifndef GAME_H
#define GAME_H

#include "rsdl.hpp"
#include "AssetsAddressLookup.h"
#include "Mario.h"
#include <string>

class Game {
public:
    Game(std::string assets_folder);

    void run_level(std::string level_addr);

    void draw_background();

private:
    void load_level(std::string level_addr);

    Window win;
    AssetsAddressLookup assets;
    int camera_x;

};


#endif
