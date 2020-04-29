#include "King.cpp"

Queen::Queen(bool color, short let, short num) : Figures(color, let, num)
{
    color ? sign = "Q" : sign = "q";
}

bool Queen::Beat_move(vector<vector<unique_ptr<Figures>>> &field, bool player, short let, short num)
{
    return this->Diagonal(field, player, let, num) || this->Straight(field, player, let, num);
}

bool
Queen::Check_move_direction(vector<vector<unique_ptr<Figures>>> &field, Players &player, short let, short num,
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