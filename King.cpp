#include "Figures.cpp"

King::King(bool color, short let, short num) : Figures(color, let, num)
{
    color ? sign = "K" : sign = "k";
}

bool King::Beat_move(vector<vector<unique_ptr<Figures>>> &field, bool player, short let, short num)
{
    if (abs(let - this->let) < 2 && abs(num - this->num) < 2)
    {
        if (field[num][let] == nullptr || field[num][let]->Get_color() != player)
        {
            return true;
        }
    }
    return false;
}

bool
King::Check_move_direction(vector<vector<unique_ptr<Figures>>> &field, Players &player, short let, short num, string &error)
{
    if (this->Beat_move(field, player.Get_color(), let, num))
    {
        error = "";
        return true;
    }
    error = "You can't move here!\n";
    return false;
}

void King::Past_move(vector<vector<unique_ptr<Figures>>> &field, Players &player, short let, short num)
{
    player.Set_king(let, num);
}