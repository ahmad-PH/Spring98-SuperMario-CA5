#include "Game.h"
#include <fstream>

using namespace std;

Game::Game(string assets_folder) : win(800, 600), assets(assets_folder) {
    camera_x = 0;
}

void Game::draw_background() {

    const int bg_width = 2000, bg_height = 1000;
    const int bg_x = camera_x % bg_width;
    const int bg_y = bg_height - win.get_height();

    bool reached_end = camera_x % bg_width + win.get_width() >= bg_height;

    if (!reached_end) {
        win.draw_img(
                assets.get("bg_img"),
                Rectangle(0, 0, win.get_width(), win.get_height()),
                Rectangle(bg_x, bg_y, win.get_width(), win.get_height())
        );
    } else {
        int first_part_width = bg_width - bg_x;
        int second_part_width = win.get_width() - first_part_width;
        win.draw_img(
                assets.get("bg_img"),
                Rectangle(0, 0, first_part_width, win.get_height()),
                Rectangle(bg_x, bg_y, first_part_width, win.get_height())
        );

        win.draw_img(
                assets.get("bg_img"),
                Rectangle(first_part_width, 0, second_part_width, win.get_height()),
                Rectangle(0, bg_y, second_part_width, win.get_height())
        );

    }

    win.update_screen();
}

void Game::load_level(string level_addr) {
    ifstream level_file(level_addr.c_str());

    string line;
    while(getline(level_file, line)) {
        cout<<line<<endl;
    }
}


void Game::run_level(std::string level_addr) {
    load_level(level_addr);
}

