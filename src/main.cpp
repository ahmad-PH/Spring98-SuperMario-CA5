#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"
#include <SDL2/SDL_mixer.h>

using namespace std;

int main() {
    Game game;
    game.run_level("../assets/maps/1.txt");
}
