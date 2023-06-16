//
// Created by user on 6/17/23.
//

#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
#include <cstdlib>
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
    int score, del;
    int maxwidth;
    int maxheight;
    char dir, part_char, edge_char, fruit_char;
    bool eat_fruits;
    snake_game_position fruit;
    vector <snake_game_position> snake;

    void Init_Game_Window();

    void Create_Window(string m);

    void Create_Snake();

    void Show_Score();

    void DrawScore();

    void Appear_Fruit();

    bool FatalCollision();

    void Move_Snake();

    bool Get_Fruit();

public:
    snake_game(string m);

    ~snake_game();

    void Play_Game();
};

#endif
