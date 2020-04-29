#ifndef CHESS_H
#define CHESS_H

#include "Pawn.cpp"

class Chess
{
public:
    static void Game();

    static bool Load_game(vector<vector<unique_ptr<Figures>>> &field, Players *players, const string &saves_path, short &charge);

    static void Save_game(vector<vector<unique_ptr<Figures>>> &field, Players *players, const string &saves_path, short charge);

    static vector<vector<unique_ptr<Figures>>> Field_builder();

    static void Default_filler(vector<vector<unique_ptr<Figures>>> &field);

    static Players *Ident_players();

    static void Show_field(vector<vector<unique_ptr<Figures>>> &field);

    static bool Two_kings_draw(vector<vector<unique_ptr<Figures>>> &field);

    static bool Check_checkmate_or_rogue(vector<vector<unique_ptr<Figures>>> &field, Players &player);

    static bool Check_cell_name(string &cell, short &let, short &num, string &error);

    static bool Check_cell_number(short let, short num, string &error);

    static bool Check_cell_figure(vector<vector<unique_ptr<Figures>>> &field, Players &player, short &let, short &num, string &error);

    static bool Check_cell(string &cell, vector<vector<unique_ptr<Figures>>> &field, Players &player, short &let, short &num, string &error);

    static bool Check_Shah(vector<vector<unique_ptr<Figures>>> &field, unique_ptr<Figures> &figure, Players &player, short let, short num, string &error);

    static void King_changer(Players &player, short let, short num);

    static bool Check_movement(vector<vector<unique_ptr<Figures>>> &field, unique_ptr<Figures> &figure,Players &player, short let, short num, string &error);

    static void Movement(vector<vector<unique_ptr<Figures>>> &field, unique_ptr<Figures> &figure, Players &player, short let, short num);

    static bool Check_rogue(vector<vector<unique_ptr<Figures>>> &field, unique_ptr<Figures> &figure, Players &player, short let, short num, string &error);

    static bool Moving_possibility(vector<vector<unique_ptr<Figures>>> &field, unique_ptr<Figures> &figure, Players &player, string &error);
};

#endif //CHESS_H