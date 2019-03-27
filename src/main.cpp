#include "Game.h"
#include<iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout<<"please provide a map name"<<endl;
        exit(EXIT_FAILURE);
    }
    Game game;
    game.run_level(argv[1]);
}
