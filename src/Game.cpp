#include "Game.h"
#include <fstream>

using namespace std;

Game::Game() : win(800, 480) {
    camera_x = 0;
}

void Game::draw_background() {

    const int bg_width = 2000, bg_height = 1000;
    const int bg_x = camera_x % bg_width;
    const int bg_y = bg_height - win.get_height();

    bool reached_end = camera_x % bg_width + win.get_width() >= bg_height;

    if (!reached_end) {
        win.draw_img(
                BG_IMG_ADDR,
                Rectangle(0, 0, win.get_width(), win.get_height()),
                Rectangle(bg_x, bg_y, win.get_width(), win.get_height())
        );
    } else {
        int first_part_width = bg_width - bg_x;
        int second_part_width = win.get_width() - first_part_width;
        win.draw_img(
                BG_IMG_ADDR,
                Rectangle(0, 0, first_part_width, win.get_height()),
                Rectangle(bg_x, bg_y, first_part_width, win.get_height())
        );

        win.draw_img(
                BG_IMG_ADDR,
                Rectangle(first_part_width, 0, second_part_width, win.get_height()),
                Rectangle(0, bg_y, second_part_width, win.get_height())
        );

    }
}

void Game::load_level(string level_addr) {
    ifstream level_file(level_addr.c_str());

    string line;
    int y = 0;
    while(getline(level_file, line)) {
        for (int x = 0; x < line.size(); x++) {
            load_map_cell(x, y, line[x]);
        }
        y++;
    }
}

void Game::run_level(std::string level_addr) {
    load_level(level_addr);
    game_running = true;

    while(game_running) {
        handle_events();
        draw();

        SDL_Delay(100);
    }
}

void Game::load_map_cell(int x, int y, char cell) {
    Rectangle position(x * CELL_SIZE_PX, y * CELL_SIZE_PX, CELL_SIZE_PX, CELL_SIZE_PX);

    switch(cell) {
        case '#':
            blocks.push_back(Block(position, GROUND_BLOCK_ADDR));
            break;
        case 'M':
            mario = new Mario(position);

//        default:
//            cerr<<"invalid chracter "<<cell<<" in map. exiting."<<endl;
//            exit(EXIT_FAILURE);
    }
}

void Game::draw() {
    draw_background();
    for (int i = 0; i < blocks.size(); i++) {
        blocks[i].draw(win);
    }
    mario->draw(win);

    win.update_screen();
}

Game::~Game() {
    delete mario;
}

void Game::handle_events() {
    while (win.has_pending_event()) {
        Event e = win.poll_for_event();

        switch (e.get_type()) {
            case Event::KEY_PRESS:
                mario->handle_key_press(e.get_pressed_key());
                break;
            case Event::KEY_RELEASE:
                mario->handle_key_release(e.get_pressed_key());
                break;
            case Event::QUIT:
                game_running = false;
                break;
        }
    }
}
