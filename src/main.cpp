#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"

using namespace std;

#include "Object.h"
#include "utility.h"

class A {

};

class B : public A {};


int main() {
    Game g;
    g.run_level("../assets/maps/1.txt");
}
