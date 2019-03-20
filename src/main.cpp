#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"

using namespace std;

#include "Object.h"

int main() {
    Game g;
    g.run_level("../assets/maps/1.txt");
}
