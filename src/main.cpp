#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"

using namespace std;

struct Map {

};


int main() {
    Game g("../assets");
    g.draw();
    SDL_Delay(7000);
}
