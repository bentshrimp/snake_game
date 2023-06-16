//
// Created by user on 6/16/23.
//

#ifndef SNAKE_GAME_MAP_H
#define SNAKE_GAME_MAP_H

#include <vector>
#include <string>

using namespace std;

class Map {
    int width, height;
    vector<string> str;
public:
    Map(string m);
    void print();
    vector<string> getMap();
    int getWidth();
    int getHeight();
};


#endif //SNAKE_GAME_MAP_H
