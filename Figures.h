#ifndef CHESS_FIGURES_H
#define CHESS_FIGURES_H

#include "Players.cpp"

class Figures
{
protected:
    string sign;
    bool color;
    short let;
    short num;
    bool moved = false;

protected:
    bool Straight(vector<vector<unique_ptr<Figures>>> &field, bool player, short let, short num);

    bool Diagonal(vector<vector<unique_ptr<Figures>>> &field, bool player, short let, short num);

public:
    Figures(bool color, short let, short num);

    short Get_num();

    short Get_let();

    string Get_sign();

    bool Get_color();

    bool Get_moved();

    void Set_moved(bool moved);

    void Set_num( short num);

    void Set_let(short let);

    void Set_sign(string sign);

    void Set_color(bool color);

    virtual bool Beat_move(vector<vector<unique_ptr<Figures>>> &field, bool player, short let, short num) = 0;

    virtual void Past_move(vector<vector<unique_ptr<Figures>>> &field, Players &player, short let, short num);

    virtual bool Check_move_direction(vector<vector<unique_ptr<Figures>>> &field, Players &player, short let, short num, string &error) = 0;
};

class Pawn : public Figures
{
private:
    short direction;

public:
    Pawn(bool color, short let, short num);

    bool Check_move_direction(vector<vector<unique_ptr<Figures>>> &field, Players &player, short let, short num, string &error) override;

    bool Beat_move(vector<vector<unique_ptr<Figures>>> &field, bool player, short let, short num) override;

    void Past_move(vector<vector<unique_ptr<Figures>>> &field, Players &player, short let, short num) override;
};

class Rock : public Figures
{
public:
    Rock(bool color, short let, short num);

    bool Beat_move(vector<vector<unique_ptr<Figures>>> &field, bool player, short let, short num) override;

    bool Check_move_direction(vector<vector<unique_ptr<Figures>>> &field, Players &player, short let, short num, string &error) override;
};

class Knight : public Figures
{
public:
    Knight(bool color, short let, short num);

    bool Beat_move(vector<vector<unique_ptr<Figures>>> &field, bool player, short let, short num) override;

    bool Check_move_direction(vector<vector<unique_ptr<Figures>>> &field, Players &player, short let, short num, string &error) override;
};

class Bishop : public Figures
{
public:
    Bishop(bool color, short let, short num);

    bool Beat_move(vector<vector<unique_ptr<Figures>>> &field, bool player, short let, short num) override;

    bool Check_move_direction(vector<vector<unique_ptr<Figures>>> &field, Players &player, short let, short num, string &error) override;
};

class Queen : public Figures
{
public:
    Queen(bool color, short let, short num);

    bool Beat_move(vector<vector<unique_ptr<Figures>>> &field, bool player, short let, short num) override;

    bool Check_move_direction(vector<vector<unique_ptr<Figures>>> &field, Players &player, short let, short num, string &error) override;
};

class King : public Figures
{
public:
    King(bool color, short let, short num);

    void Past_move(vector<vector<unique_ptr<Figures>>> &field, Players &player, short let, short num) override;

    bool Beat_move(vector<vector<unique_ptr<Figures>>> &field, bool player, short let, short num) override;

    bool Check_move_direction(vector<vector<unique_ptr<Figures>>> &field, Players &player, short let, short num, string &error) override;
};

#endif //CHESS_FIGURES_H