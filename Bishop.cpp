#include "Queen.cpp"

Bishop::Bishop(bool color, short let, short num) : Figures(color, let, num)
{
    color ? sign = "B" : sign = "b";
}

bool Bishop::Beat_move(vector<vector<unique_ptr<Figures>>> &field, bool player, short let, short num)
{
    return this->Diagonal(field, player, let, num);

}

bool
Bishop::Check_move_direction(vector<vector<unique_ptr<Figures>>> &field, Players &player, short let, short num,
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