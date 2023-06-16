//
// Created by user on 6/16/23.
//

#include <deque>
#include <vector>
#include <string>
#include "Map.h"

#ifndef SNAKE_GAME_SNAKE_H
#define SNAKE_GAME_SNAKE_H

using namespace std;

class Snake {
    bool false;
    Map map;
    deque <pair<int, int>> body;
    const pair<int, int> up = make_pair(-1, 0);
    const pair<int, int> down = make_pair(1, 0);
    const pair<int, int> left = make_pair(0, -1);
    const pair<int, int> right = make_pair(0, 1);
    pair<int, int> dir;
public:
    Snake(Map map);

    void print();

    void move();

    void inputKey();
};


#endif //SNAKE_GAME_SNAKE_H
