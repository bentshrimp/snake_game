//
// Created by user on 6/17/23.
//
#include "snake_game.h"
#include "Mission.h"
#include <string>
#include <vector>
#include <fstream>
#include <unistd.h>

using namespace std;

snake_game_position::snake_game_position(int dx, int dy) {
    x = dx;
    y = dy;
}

snake_game_position::snake_game_position() {
    x = 0;
    y = 0;
}

snake_game::snake_game(string m, int s, int l, int g) : s(s), l(l), g(g) {
    part_char = 'O';
    edge_char = 'X';
    fruit_char = '@';
    gateScore = 0;
    fruit.x = 0;
    fruit.y = 0;
    score = 0;
    del = 110000;
    bool eat_fruits = 0;
    dir = 'l';
    srand(time(NULL));

    Init_Game_Window();
    Create_Window(m);
    Create_Snake();
    Appear_Fruit();
    Show_Score();
    Show_Mission(s, l, g);
    Appear_Gate(m);
    refresh();
}

snake_game::~snake_game() {
    nodelay(stdscr, false); // 사용자의 입력을 기다림 -> 입력 전까지 실행 x
    getch();
    endwin();
}

void snake_game::Init_Game_Window() {
    initscr(); // Curses 모드 시작
    nodelay(stdscr, true); // 입력 기다림 x 바로 실행
    keypad(stdscr, true); // 키 입력
    noecho(); // 키 입력을 화면에 표시 x
    curs_set(0); // 커서를 보이지 않게함
    getmaxyx(stdscr, maxheight, maxwidth);

    return;
}

void snake_game::Create_Window(string m) {
    vector <string> str;
    string line;
    ifstream file(m); // example.txt 파일을 연다. 없으면 생성.
    if (file.is_open()) {
        while (getline(file, line)) {
            str.push_back(line);
        }
        file.close(); // 열었떤 파일을 닫는다.
    }
    maxheight = str.size();
    maxwidth = str[0].size();

    for (int i = 0; i < str.size(); i++) {
        for (int j = 0; j < str[0].size(); j++) {
            char c = str[i][j];
            switch (c) {
                case '1':
                    c = edge_char;
                    break;
                case '2':
                    c = '*';
                    break;
                default:
                    c = ' ';
            }
            mvaddch(i, j, c);
        }
    }
}

void snake_game::Create_Snake() {

    for (int i = 0; i < 3; i++) {
        snake.push_back(snake_game_position(maxwidth / 2 + i, maxheight / 2));
    }
    for (int i = 0; i < snake.size(); i++) {
        move(snake[i].y, snake[i].x); // 자정한 좌표로 이동
        addch(part_char); // part_char 를 현재 커서에 출력, 커서는 출력한 문자 다음으로 이동
    }
    return;
}

void snake_game::Show_Score() {
    move(1, maxwidth + 2);
    printw("SCORE BOARD");
    move(3, maxwidth + 2);
    printw("Score: %d", score);
    move(5, maxwidth + 2);
    printw("Length: %d", 3 + score/10);
    move(7, maxwidth + 2);
    printw("Gate usage: %d", gateScore / 2);
}

void snake_game::Show_Mission(Mission s, Mission l, Mission g) {
    move(11, maxwidth + 2);
    printw("Mission");
    move(13, maxwidth + 2);
    printw("Score: %d", s.score);
    move(15, maxwidth + 2);
    printw("Length: %d", l.score);
    move(17, maxwidth + 2);
    printw("Gate: %d", g.score);
}


void snake_game::Appear_Fruit() {
    while (1) { // 무한 루프 시작
        int tmp_x = rand() % maxwidth +
                    1; // temp_x 변수에 1부터 maxwidth까지의 난수를 할당, +1을 통해 0을 피하고 1부터 값을 가짐, %maxwidth 을 통해 tmp_x 값이 maxwidth 보다 작게
        int tmp_y = rand() % maxheight + 1;

        for (int i = 0; i < snake.size(); i++) {
            if (snake[i].x == tmp_x && snake[i].y == tmp_y)
                continue; // 이 반복문은 fruit가 snake의 위치에 생기지 않도록 함
        }
        if (tmp_x >= maxwidth - 2 || tmp_y >= maxheight - 3)
            continue; // 현재 fruit의 위치(tmp_x, tmp_y)가 게임 창의 범위 안에 있는지 확인

        fruit.x = tmp_x; //set fruit
        fruit.y = tmp_y;
        break;
    }
    mvaddch(fruit.y, fruit.x, fruit_char);
    refresh();
}

bool snake_game::FatalCollision() // snake 의 충돌 여부를 검사
{
    // 뱀의 머리(snake[0])의 x좌표가 0이거나 maxwith-1 과 같거나, y좌표가 0이거나 maxheight-2 와 같으면 충돌이 발생한거로 판단 -> true 리턴 -> 뱀이 가장자리에 도착한거로 판단
//    if (snake[0].x == 0 || snake[0].x == maxwidth - 1 || snake[0].y == 0 || snake[0].y == maxheight - 2)
//        return true;
    if (mvinch(snake[0].x, snake[0].y) == edge_char) {
        return true;
    }
    /*
    뱀의 머리와 몸통 부분과의 충돌 검사
    뱀의 머리 (snake[0])의 위치와 현재 검사 중인 몸통 부분(snake[i])와 위치가 일치하는지 확인
    위의 조건들을 모두 통과하면 충돌이 없는거로 판단 -> false 리턴
    */
    for (int i = 2; i < snake.size(); i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            return true;
    }
    return false;
}

void snake_game::Appear_Gate(string m) {
    vector <string> str;
    string line;
    ifstream file(m); // example.txt 파일을 연다. 없으면 생성.
    if (file.is_open()) {
        while (getline(file, line)) {
            str.push_back(line);
        }
        file.close(); // 열었떤 파일을 닫는다.
    }

    int gate_x;
    int gate_y;

    for (int i = 0; i < 2; i++) {
        while (1) {
            gate_x = rand() % maxwidth;
            gate_y = rand() % maxheight;
            if (str[gate_x][gate_y] == '1') {
                door.push_back(make_pair(gate_x, gate_y));
                mvaddch(gate_x, gate_y, ' ');
                break;
            }
        }
    }
}

bool snake_game::throughGate() {
    for (int i = 0; i < 2; i++) {
        if (make_pair(snake[0].y, snake[0].x) == door[i]) {
            gateScore++;
            Show_Score();
            return true;
        }
    }
    return false;
}

bool snake_game::Get_Fruit() {
    if (snake[0].x == fruit.x && snake[0].y == fruit.y) { // 뱀의 머리의 위차가 과일의 위치와 일치하는지 확인 일치하면 과일을 먹은 것으로 간주
        Appear_Fruit(); // 새로운 과일 생성
        score += 10;
        Show_Score();

        if ((score % 100) == 0) // 점수를 100으로 나눈 나머지가 0이라면
            del -= 1000;
        return eat_fruits = true; // 몸 길이 늘어남
    } else return eat_fruits = false; // 과일을 먹은 상태를 나타내는 플래그

    return eat_fruits;
}

void snake_game::Move_Snake() {
    int KeyPressed = getch(); //getch() 함수를 호출해 사용자의 키 입력을 받음
    switch (KeyPressed) {
        case KEY_LEFT:
            if (dir != 'r') { dir = 'l'; } // 현재 이동 방향이 오른쪽이 아닌경우 왼쪽으로 변경
            break;
        case KEY_RIGHT:
            if (dir != 'l') { dir = 'r'; }
            break;
        case KEY_UP:
            if (dir != 'd') { dir = 'u'; }
            break;
        case KEY_DOWN:
            if (dir != 'u') { dir = 'd'; }
            break;
        case KEY_BACKSPACE: // 게임 종료
            dir = 'q';
            break;
    }
    if (!eat_fruits) {
        move(snake[snake.size() - 1].y, snake[snake.size() - 1].x);
        // 뱀의 꼬리 부분으로 커서를 이동시킴
        printw(" ");
        /*
        빈 공백 문자를 출력
        이는 뱀의 꼬리를 지우는 역활
        */
        refresh(); // 변경된 화면을 표시
        snake.pop_back(); // 벡터의 마지막 요소 == 꼬리를 제거
    }

    int exit_x;
    int exit_y;

    if (throughGate()) {
        for (int i = 0; i < 2; i++) {
            if (door[i] == make_pair(snake[0].y, snake[0].x)) {
                exit_x = door[-i + 1].second;
                exit_y = door[-i + 1].first;
            }
        }
        if (exit_x == 0) {
            dir = 'r';
        } else if (exit_x == maxwidth - 1) {
            dir = 'l';
        } else if (exit_y == 0) {
            dir = 'd';
        } else if (exit_y == maxheight - 1) {
            dir = 'u';
        }

        if (dir == 'l') {
            snake.insert(snake.begin(), snake_game_position(exit_x - 1, exit_y));
        } else if (dir == 'r') {
            snake.insert(snake.begin(), snake_game_position(exit_x + 1, exit_y));
        } else if (dir == 'u') {
            snake.insert(snake.begin(), snake_game_position(exit_x, exit_y - 1));
        } else if (dir == 'd') {
            snake.insert(snake.begin(), snake_game_position(exit_x, exit_y + 1));
        }
//        move(exit_y, exit_x);
    } else {
        // 이 코드는 현재 뱀의 이동 방향에 따라 뱀의 머리를 새로운 위치에 삽입해 뱀을 이동시키는 역활을 함
        if (dir == 'l') {
            snake.insert(snake.begin(), snake_game_position(snake[0].x - 1, snake[0].y));
        } else if (dir == 'r') {
            snake.insert(snake.begin(), snake_game_position(snake[0].x + 1, snake[0].y));
        } else if (dir == 'u') {
            snake.insert(snake.begin(), snake_game_position(snake[0].x, snake[0].y - 1));
        } else if (dir == 'd') {
            snake.insert(snake.begin(), snake_game_position(snake[0].x, snake[0].y + 1));
        }
    }
    move(snake[0].y, snake[0].x);
    addch(part_char);
    refresh();

    return;
}


bool snake_game::Play_Game() {
    while (1) {
        if (FatalCollision() && !throughGate()) {
            move((maxheight - 2) / 2, (maxwidth - 5) / 2);
            printw("GAME OVER");
            return false;
            break;
        }
        if (s.check(score) && l.check(snake.size()) && g.check(gateScore/2)) {
            move((maxheight - 2) / 2, (maxwidth - 5) / 2);
            printw("GAME CLEAR");
            return true;
            break;
        }
        Get_Fruit();
        Move_Snake();

        if (dir == 'q') {
            return false;
            break;
        }
        usleep(del);
    }
}