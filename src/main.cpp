#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"

using namespace std;

struct Map {

};


int main() {
    Game g;
    g.run_level("../assets/maps/1.txt");
}
