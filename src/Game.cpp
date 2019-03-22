#include "Game.h"
#include "utility.h"
#include <fstream>

using namespace std;

Game::Game() : win(800, 480) {
    camera_x = 0;
}

void Game::run_level(std::string level_addr) {
    load_level(level_addr);
    game_running = true;

    while(game_running) {
        handle_events();
        update();
        draw();

        rsdl::delay(90);
    }
}


void Game::draw_background() {

    const int bg_width = 2000, bg_height = 1000;
    const int bg_x = camera_x % bg_width;
    const int bg_y = bg_height - win.get_height();

    bool reached_end = camera_x % bg_width + win.get_width() >= bg_height;

    if (!reached_end) {
        win.draw_img(
                BG_IMG_ADDR,
                rsdl::Rectangle(0, 0, win.get_width(), win.get_height()),
                rsdl::Rectangle(bg_x, bg_y, win.get_width(), win.get_height())
        );
    } else {
        int first_part_width = bg_width - bg_x;
        int second_part_width = win.get_width() - first_part_width;
        win.draw_img(
                BG_IMG_ADDR,
                rsdl::Rectangle(0, 0, first_part_width, win.get_height()),
                rsdl::Rectangle(bg_x, bg_y, first_part_width, win.get_height())
        );

        win.draw_img(
                BG_IMG_ADDR,
                rsdl::Rectangle(first_part_width, 0, second_part_width, win.get_height()),
                rsdl::Rectangle(0, bg_y, second_part_width, win.get_height())
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

void Game::load_map_cell(int x, int y, char cell) {
    ExactRectangle position(x * CELL_SIZE_PX, y * CELL_SIZE_PX, CELL_SIZE_PX, CELL_SIZE_PX);

    switch(cell) {
        case '#':
            add_block(new Block(position, GROUND_BLOCK_ADDR)); break;
        case '@':
            add_block(new Block(position, REGULAR_BLOCK_ADDR)); break;
        case 'M':
            mario = new Mario(position); break;
        case 'b':
            add_brick(new RegularBrick(position)); break;
        case '?':
            add_brick(new QuestionBrick(position)); break;
//        default:
//            cerr<<"invalid chracter "<<cell<<" in map. exiting."<<endl;
//            exit(EXIT_FAILURE);
    }
}

void Game::draw() {
    draw_background();
    for (int i = 0; i < blocks.size(); i++) {
        blocks[i]->draw(win);
    }
    for (int i = 0; i < bricks.size(); i++) {
        bricks[i]->draw(win);
    }
    mario->draw(win);
    win.update_screen();
}

Game::~Game() {
    delete mario;
    delete_vector(blocks);
    delete_vector(bricks);
}

void Game::handle_events() {
    while (win.has_pending_event()) {
        rsdl::Event e = win.poll_for_event();

        switch (e.get_type()) {
            case rsdl::Event::KEY_PRESS:
                mario->handle_key_press(e.get_pressed_key());
                break;
            case rsdl::Event::KEY_RELEASE:
                mario->handle_key_release(e.get_pressed_key());
                break;
            case rsdl::Event::QUIT:
                game_running = false;
                break;
        }
    }
}

void Game::update() {
    mario->update(obstacles);
}

void Game::add_block(Block* block) {
    blocks.push_back(block);
    obstacles.push_back(block);
}

void Game::add_brick(Brick* brick) {
    bricks.push_back(brick);
    obstacles.push_back(brick);
}

void Game::remove_brick(Brick *brick) {
    bricks.erase(bricks.begin() + find_in_vector(bricks, brick));
    obstacles.erase(obstacles.begin() + find_in_vector(obstacles, (Object*)brick));
}

