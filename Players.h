#ifndef CHESS_PLAYERS_H
#define CHESS_PLAYERS_H

#include <utility>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <math.h>
#include <random>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <io.h>

class Players
{
private:
    bool color;
    short king_let;
    short king_num;
    std::string name;
    std::vector<std::string> moves;
    std::vector<int> time;

public:
    Players();

    void Set_name(std::string name);

    void Set_color(bool color);

    void Set_king(short king_let, short king_num);

    void Set_king_let(short king_let);

    void Set_king_num(short king_num);

    void Add_move(std::string &move);

    void Remove_move();

    void Add_time(clock_t time);

    std::string Get_name();

    bool Get_color();

    short Get_king_let();

    short Get_king_num();

    std::vector<std::string> Get_moves();

    std::vector<int> Get_time();

    static void Show_results(Players *players);

    static void Clear(Players *players);
};

#endif //CHESS_PLAYERS_H