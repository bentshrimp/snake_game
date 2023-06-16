//
// Created by user on 6/16/23.
//
#include <vector>
#include <string>
#include "ncurses.h"

#ifndef SNAKE_GAME_MAP_H
#define SNAKE_GAME_MAP_H

using namespace std;

class Map {
    int size;
    vector <string> m;
public:
    Map(string src);
};


#endif //SNAKE_GAME_MAP_H
