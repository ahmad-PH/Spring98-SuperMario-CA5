#include "Game.h"
#include "utility.h"
#include <fstream>

using namespace std;

Game::Game() : win(800, 480) {
    camera_x = 0;
    n_coins = 0;
    n_lives = 3;
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
            add_block(new Block(position, GROUND_BLOCK_ADDR, this)); break;
        case '@':
            add_block(new Block(position, REGULAR_BLOCK_ADDR, this)); break;
        case 'M':
            set_mario(new Mario(position, this)); break;
        case 'b':
            add_brick(new RegularBrick(position, this)); break;
        case '?':
            add_brick(new QuestionBrick(position, this, COIN)); break;
        case 'm':
            add_brick(new QuestionBrick(position, this, MUSHROOM)); break;
        case 'l':
            add_enemy(new LittleGoomba(position, this)); break;
        case 'k':
            add_enemy(new KoopaTroopa(position, this)); break;

//        default:
//            cerr<<"invalid chracter "<<cell<<" in map. exiting."<<endl;
//            exit(EXIT_FAILURE);
    }
}

void Game::draw() {
    draw_background();
    for (int i = 0; i < objects.size(); i++)
        objects[i]->draw(win, camera_x);
    draw_banner();
    win.update_screen();
}

Game::~Game() {
    delete_vector(objects);
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
    handle_object_interactions();
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->update();
    }
    update_camera();
}

void Game::add_block(Block* block) {
    blocks.push_back(block);
    obstacles.push_back(block);
    objects.push_back(block);
}

void Game::add_brick(Brick* brick) {
    bricks.push_back(brick);
    obstacles.push_back(brick);
    objects.push_back(brick);
}

void Game::remove_brick(Brick *brick) {
    erase(bricks, brick);
    erase(obstacles, (Object*)brick);
    remove_object(brick);
}

void Game::set_mario(Mario *mario) {
    this->mario = mario;
    objects.push_back(mario);
    marios_initial_pos = mario->get_position();
}

void Game::update_camera() {
    if (mario->get_position().x >  camera_x + (win.get_width() / 2)) {
        camera_x = mario->get_position().x - (win.get_width() / 2);
    }
}

void Game::handle_object_interactions() {
    Mario* unchanged_mario = new Mario(*mario);

    for (int i = 0; i < enemies.size(); i++)
        mario->handle_interaction_with_enemy(enemies[i]);

    for (int i = 0; i < objects.size(); i++)
        objects[i]->handle_interaction_with_mario(unchanged_mario);

    for (int i = 0; i < enemies.size(); i++) {
        for (int j = 0; j < enemies.size(); j++) {
            if (i == j) continue;
            enemies[i]->handle_interaction_with_enemy(enemies[j]);
        }
    }

    delete unchanged_mario;

//    for (int i = 0; i < bricks.size(); i++) {
//        bricks[i]->handle_interaction_with_mario(mario);
//    }
//    for (int i = 0; i < enemies.size(); i++) {
//        Mario* unchanged_mario = new Mario(*mario);
//        mario->handle_interaction_with_enemy(enemies[i]);
//        enemies[i]->handle_interaction_with_mario(unchanged_mario);
//        delete unchanged_mario;
//    }
//    for (int i = 0; i < enemies.size(); i++) {
//        for (int j = 0; j < enemies.size(); j++) {
//            if (i == j) continue;
//            enemies[i]->handle_interaction_with_enemy(enemies[j]);
//        }
//    }
}

void Game::remove_object(Object* object) {
    erase(objects, object);
    delete object;
}

void Game::add_object(Object *object) {
    objects.push_back(object);
}

void Game::increment_coin() {
    n_coins++;
}

void Game::draw_banner() {
    show_text(win, "COINS", rsdl::Point(win.get_width()/3 - 50, 10));
    show_text(win, to_string(n_coins), rsdl::Point(win.get_width()/3 - 20, 40));
    show_text(win, "LIVES", rsdl::Point(win.get_width()*2/3 - 50, 10));
    show_text(win, to_string(n_lives), rsdl::Point(win.get_width()*2/3 - 25, 40));
}

void Game::add_enemy(Enemy *enemy) {
    enemies.push_back(enemy);
    objects.push_back((Object*)enemy);
}

void Game::remove_enemy(Enemy *enemy) {
    erase(enemies, enemy);
    erase(objects, (Object*)enemy);
}

void Game::on_marios_death() {
    n_lives--;
    rsdl::delay(1000);
    camera_x = 0;
    mario->reset(marios_initial_pos);
}

