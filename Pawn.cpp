#include "Rock.cpp"

Pawn::Pawn(bool color, short let, short num) : Figures(color, let, num)
{
    color ? sign = "P" : sign = "p";
    if (color)
    {
        this->direction = 1;
    } else
    {
        this->direction = -1;
    }
}

bool
Pawn::Beat_move(vector<vector<unique_ptr<Figures>>> &field, bool player, short let, short num)
{
    return field[num][let] != nullptr && field[num][let]->Get_color() != player &&
           num - this->num == this->direction && abs(this->let - let) == 1;
}

bool
Pawn::Check_move_direction(vector<vector<unique_ptr<Figures>>> &field, Players &player, short let, short num,
                           string &error)
{
    if (field[num][let] == nullptr && let == this->let)
    {
        if (num - this->num == this->direction)
        {
            error = "";
            return true;
        } else if (!this->moved && num - this->num == this->direction * 2 &&
                   field[this->num + this->direction][let] == nullptr)
        {
            error = "";
            return true;
        }
    } else
    {
        if (this->Beat_move(field, player.Get_color(), let, num))
        {
            error = "";
            return true;
        }
    }
    error = "You can't move here!\n";
    return false;
}

void Pawn::Past_move(vector<vector<unique_ptr<Figures>>> &field, Players &player, short let, short num)
{
    if (this->num % 7 == 0)
    {
        string choose;
        field[this->num][this->let].reset(nullptr);
        do
        {
            cout << "Which figure do you want to get from your pawn?" << endl
                 << "Q - for the queen" << endl
                 << "R - for the rock" << endl
                 << "K - for the knight" << endl
                 << "B - for the bishop" << endl;
            cin >> choose;
            if (choose[0] < 'a')
            {
                choose += 32;
            }
        } while (choose != "q" && choose != "r" && choose != "k" && choose != "b");

        if (choose == "q" || choose == "Q")
        {
            field[this->num][this->let] = move(unique_ptr<Queen>(new Queen(this->color, this->let, this->num)));
        } else if (choose == "r" || choose == "R")
        {
            field[this->num][this->let] = move(unique_ptr<Rock>(new Rock(this->color, this->let, this->num)));
        } else if (choose == "k" || choose == "K")
        {
            field[this->num][this->let] = move(unique_ptr<Knight>(new Knight(this->color, this->let, this->num)));
        } else if (choose == "b" || choose == "B")
        {
            field[this->num][this->let] = move(unique_ptr<Bishop>(new Bishop(this->color, this->let, this->num)));
        }
    }
}