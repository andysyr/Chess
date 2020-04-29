#include "Bishop.cpp"

Knight::Knight(bool color, short let, short num) : Figures(color, let, num)
{
    color ? sign = "Kn" : sign = "kn";
}

bool Knight::Beat_move(vector<vector<unique_ptr<Figures>>> &field, bool player, short let, short num)
{
    if (field[num][let] == nullptr || field[num][let]->Get_color() != player)
    {
        if (abs(let - this->let) == 1 && abs(num - this->num) == 2 ||
            abs(let - this->let) == 2 && abs(num - this->num) == 1)
        {
            return true;
        }
    }
    return false;
}

bool
Knight::Check_move_direction(vector<vector<unique_ptr<Figures>>> &field, Players &player, short let, short num,
                             string &error)
{
    if (this->Beat_move(field, player.Get_color(), let, num))
    {
        error = "";
        return true;
    }
    error = "You can't move here!\n";
    return false;
}