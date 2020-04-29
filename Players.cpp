#include "Players.h"

using namespace std;

Players::Players() = default;


void Players::Set_name(string name)
{
    this->name = std::move(name);
}

void Players::Set_color(bool color)
{
    this->color = color;
}

bool Players::Get_color()
{
    return this->color;
}

string Players::Get_name()
{
    return this->name;
}

void Players::Set_king(short king_let, short king_num)
{
    this->king_let = king_let;
    this->king_num = king_num;
}

void Players::Set_king_let(short king_let)
{
    this->king_let = king_let;
}

void Players::Set_king_num(short king_num)
{
    this->king_num = king_num;
}

short Players::Get_king_let()
{
    return this->king_let;
}

short Players::Get_king_num()
{
    return this->king_num;
}

std::vector<std::string> Players::Get_moves()
{
    return  moves;
}

std::vector<int> Players::Get_time()
{
    return time;
}

void Players::Add_move(string &move)
{
    this->moves.push_back(move);
}

void Players::Remove_move()
{
    this->moves.pop_back();
}

void Players::Add_time(clock_t time)
{
    this->time.push_back(time);
}

void Players::Show_results(Players *players)
{
    cout<<"Moves history:"<<endl;
    short charge;
    if (players[0].color)
    {
        charge = 0;
    } else
    {
        charge = 1;
    }
    for (int i = 0, j = 0; j < players[charge].moves.size(); ++i, j += 2)
    {
        cout << i + 1 << ". " << players[charge].Get_name() << " " << players[charge].moves[j] << "->"
             << players[charge].moves[j + 1] << ", "
             << players[charge].time[i] << " seconds" << endl;
        if (players[(charge + 1) % 2].moves.size() > j)
        {
            cout << i + 1 << ". " << players[(charge + 1) % 2].Get_name() << " " << players[(charge + 1) % 2].moves[j]
                 << "->" << players[(charge + 1) % 2].moves[j + 1] << ", "
                 << players[(charge + 1) % 2].time[i] << " seconds" << endl;
        }
    }
    int time;
    for (int i = 0; i < 2; ++i, charge = (charge + 1) % 2)
    {
        time = 0;
        for (int j = 0; j < players[charge].time.size(); ++j)
        {
            time += players[charge].time[j];
        }
        cout << players[charge].Get_name() << " spent " << time / 60 << " minutes " << time % 60 << " seconds" << endl;
    }
}

void Players::Clear(Players *players)
{
    for (int i = 0; i < 2; ++i)
    {
        players[i].moves.clear();
        players[i].time.clear();
    }
    players[0].Set_king(4, 0);
    players[1].Set_king(4, 7);
}