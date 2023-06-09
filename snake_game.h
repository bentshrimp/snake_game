//
// Created by user on 6/17/23.
//

#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
#include <cstdlib>
#include "Mission.h"
#include <ctime>

#ifndef SNAKEGAME_H
#define SNAKEGAME_H
using namespace std;

struct snake_game_position {
    int x, y;

    snake_game_position(int dx, int dy);

    snake_game_position();

};

class snake_game {
private:
    vector <pair<int, int>> door;
    int score, del, gateScore;
    int maxwidth;
    int maxheight;
    char dir, part_char, edge_char, fruit_char;
    bool eat_fruits;
    Mission s,l,g;
    snake_game_position fruit;
    vector <snake_game_position> snake;

    void Init_Game_Window();

    void Create_Window(string m);

    void Create_Snake();

    void Show_Score();

    void Show_Mission(Mission score, Mission len, Mission gate);

    bool Check_Mission();

    void DrawScore();

    void Appear_Fruit();

    bool FatalCollision();

    void Appear_Gate(string m);

    bool throughGate();

    void Move_Snake();

    bool Get_Fruit();

public:
    snake_game(string m, int s, int l, int g);

    ~snake_game();

    bool Play_Game();
};

#endif
