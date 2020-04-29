#include "Figures.h"

Figures::Figures(bool color, short let, short num)
{
    this->let = let;
    this->num = num;
    this->color = color;
}

short Figures::Get_num()
{
    return num;
}

short Figures::Get_let()
{
    return let;
}

string Figures::Get_sign()
{
    return sign;
}

bool Figures::Get_color()
{
    return color;
}

bool Figures::Get_moved()
{
    return this->moved;
}

void Figures::Set_moved(bool moved)
{
    this->moved = moved;
}

void Figures::Set_num(short num)
{
    this->num = num;
}

void Figures::Set_let(short let)
{
    this->let = let;
}

void Figures::Set_sign(string sign)
{
    this->sign = sign;
}

void Figures::Set_color(bool color)
{
    this->color = color;
}

void Figures::Past_move(vector<vector<unique_ptr<Figures>>> &field, Players &player, short let, short num)
{

}

bool Figures::Straight(vector<vector<unique_ptr<Figures>>> &field, bool player, short let, short num)
{
    short move = -1;
    if (field[num][let] == nullptr || field[num][let]->Get_color() != player)
    {
        if (this->let == let)
        {
            if (this->num > num)
            {
                move = 1;
            }
            num += move;
            while (num != this->num)
            {
                if (field[num][this->let] != nullptr)
                {
                    return false;
                }
                num += move;
            }
            return true;
        } else
        {
            if (this->num == num)
            {
                if (this->let > let)
                {
                    move = 1;
                }
                let += move;
                while (let != this->let)
                {
                    if (field[this->num][let] != nullptr)
                    {
                        return false;
                    }
                    let += move;
                }
                return true;
            }
        }
    }
    return false;
}

bool Figures::Diagonal(vector<vector<unique_ptr<Figures>>> &field, bool player, short let, short num)
{
    short move_let = -1;
    short move_num = -1;
    if (field[num][let] == nullptr || field[num][let]->Get_color() != player)
    {
        if (abs(let - this->let) == abs(num - this->num))
        {
            if (this->let > let)
            {
                move_let = 1;
            }
            if (this->num > num)
            {
                move_num = 1;
            }
            let += move_let;
            num += move_num;
            while (let != this->let)
            {
                if (field[num][let] != nullptr)
                {
                    return false;
                }
                let += move_let;
                num += move_num;
            }
            return true;
        }
    }
    return false;
}