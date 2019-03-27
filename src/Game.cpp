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
    win.play_music(BACKGROUND_MUSIC);
    game_running = true;

    while(game_running) {
        handle_events();
        update();
        draw();

        delay(90);
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
    charmap map;
    while(getline(level_file, line)) {
        vector<char> row;
        for (int i = 0; i < line.size(); i++)
            row.push_back(line[i]);
        map.push_back(row);
    }

    charmap annotations = annotate_map(map);

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            load_map_cell(j, i, map[i][j], annotations[i][j]);
        }
    }
}

void Game::load_map_cell(int x, int y, char cell, char annotation) {
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
            add_brick(new QuestionBrick(position, this, RED_MUSHROOM)); break;
        case 'h':
            add_brick(new QuestionBrick(position, this, HEALTH_MUSHROOM)); break;
        case 'l':
            add_enemy(new LittleGoomba(position, this)); break;
        case 'k':
            add_enemy(new KoopaTroopa(position, this)); break;
        case '.':
            break;
        case '|': {
            string img_name;
            switch (annotation) {
                case 'L':
                    img_name = "head-left";
                    break;
                case 'R':
                    img_name = "head-right";
                    break;
                case 'l':
                    img_name = "left";
                    break;
                case 'r':
                    img_name = "right";
                    break;
            }
            add_block(new Block(position, PIPE_ADDR + img_name + ".png", this));
            break;
        }
        case 'f': {
            string img_name = (annotation == 'h' ? "head" : "body");
            add_object(new FlagBlock(position, this, FLAG_ADDR + img_name + ".png"));
            break;
        }
        default:
            cerr<<"invalid chracter "<<cell<<" in map. exiting."<<endl;
            exit(EXIT_FAILURE);
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
    for (int i = 0; i < objects.size(); i++) {
        mario->handle_interaction_with_object(objects[i]);
        objects[i]->handle_interaction_with_mario(unchanged_mario);
    }
    delete unchanged_mario;

    for (int i = 0; i < enemies.size(); i++) {
        for (int j = 0; j < enemies.size(); j++) {
            if (i == j) continue;
            enemies[i]->handle_interaction_with_enemy(enemies[j]);
        }
    }

}

void Game::remove_object(Object* object) {
    erase(objects, object);
    delete object;
}

void Game::add_object(Object *object) {
    objects.push_back(object);
}

void Game::increment_coins() {
    n_coins++;
}

void Game::draw_banner() {
    show_text(win, "COINS", Point(win.get_width()/3 - 50, 10));
    show_text(win, to_string(n_coins), Point(win.get_width()/3 - 20, 40));
    show_text(win, "LIVES", Point(win.get_width()*2/3 - 50, 10));
    show_text(win, to_string(n_lives), Point(win.get_width()*2/3 - 25, 40));
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
    if (n_lives > 1) {
        n_lives--;
        win.stop_music();
        play_sound_effect(MARIOS_DEATH_SOUND);
        delay(3000);
        win.play_music(BACKGROUND_MUSIC);
        camera_x = 0;
        mario->reset(marios_initial_pos);
    } else {
        win.fill_rect(Rectangle(0, 0, win.get_width(), win.get_height()), BLACK);
        show_text(win, "YOU LOSE!", Point(win.get_width()/2 - 80, win.get_height()/2 - 30), 40);
        win.update_screen();
        game_running = false;
        win.stop_music();
        play_sound_effect(GAMEOVER_SOUND);
        delay(4500);
    }

}

charmap Game::annotate_map(const charmap& map) {
    charmap result;
    for (int i = 0; i < map.size(); i++) {
        vector<char> row;
        for (int j = 0; j < map[i].size(); j++) {
            row.push_back(annotate_cell(i, j, map));
        }
        result.push_back(row);
    }
    return result;
}

char Game::annotate_cell(int i, int j, const charmap &map) {
    if (map[i][j] == '|') {
        if (map[i - 1][j] != '|' && map[i][j - 1] != '|')
            return 'L';
        else if (map[i - 1][j] != '|' && map[i][j + 1] != '|')
            return 'R';
        else if (map[i][j - 1] != '|')
            return 'l';
        else if (map[i][j + 1] != '|')
            return 'r';
    } else if (map[i][j] == 'f') {
        if (map[i-1][j] != 'f')
            return 'h';
        else
            return 'b';
    } else {
        return ' ';
    }
}

void Game::on_win() {
    if (!game_running)
        return;;

    win.fill_rect(Rectangle(0, 0, win.get_width(), win.get_height()), BLACK);
    show_text(win, "YOU WIN!", Point(win.get_width()/2 - 80, win.get_height()/2 - 30), 40);
    win.update_screen();
    game_running = false;
    win.stop_music();
    play_sound_effect(LEVEL_CLEAR_SOUND);
    delay(6500);
}

void Game::increment_lives() {
    n_lives++;
}

void Game::play_sound_effect(std::string filename) {
    win.play_sound_effect(filename);
}
