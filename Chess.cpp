#include "Chess.h"

bool Chess::Load_game(vector<vector<unique_ptr<Figures>>> &field, Players *players, const string &saves_path, short &charge)
{
    ifstream fin;
    unique_ptr<Figures> figure;
    string temp_string;
    bool temp_bool;
    short temp_short;

    string sign;
    bool color;
    bool moved;
    short let;
    short num;

    string save_name;

    string error = "";
    do
    {
        cout << error;
        cout << "Please, enter a name of a save you want to load\t";
        cin >> save_name;
        fin.open(saves_path + save_name + ".txt");
        if (!fin.is_open())
        {
            error = "There isn't a save with such name. You can try again or quit by command \"/back\"\t";
        }
    } while (!fin.is_open() && save_name != "/back");

    if (fin.is_open())
    {
        fin >> charge;
        for (int i = 0; i < 2; ++i)
        {
            fin >> temp_bool;
            players[i].Set_color(temp_bool);

            fin >> temp_short;
            players[i].Set_king_let(temp_short);

            fin >> temp_short;
            players[i].Set_king_num(temp_short);

            fin >> temp_string;
            players[i].Set_name(temp_string);

            fin >> temp_string;
            while (temp_string != "moves_vector_end")
            {
                players[i].Add_move(temp_string);
                fin >> temp_string;
            }

            fin >> temp_string;
            while (temp_string != "time_vector_end")
            {
                //may not work!!
                players[i].Add_time(stoi(temp_string));
                //players[i].time.push_back(stoi(temp_string));
                fin >> temp_string;
            }
        }

        while (!fin.eof())
        {
            fin >> sign;
            fin >> color;
            fin >> moved;
            fin >> let;
            fin >> num;

            if (sign == "P" || sign == "p")
            {
                figure = unique_ptr<Pawn>(new Pawn(color, let, num));

            } else if (sign == "R" || sign == "r")
            {
                figure = unique_ptr<Rock>(new Rock(color, let, num));
            } else if (sign == "Kn" || sign == "kn")
            {
                figure = unique_ptr<Knight>(new Knight(color, let, num));
            } else if (sign == "B" || sign == "b")
            {
                figure = unique_ptr<Bishop>(new Bishop(color, let, num));
            } else if (sign == "Q" || sign == "q")
            {
                figure = unique_ptr<Queen>(new Queen(color, let, num));
            } else if (sign == "K" || sign == "k")
            {
                figure = unique_ptr<King>(new King(color, let, num));
            }
            figure->Set_moved(moved);
            field[figure->Get_num()][figure->Get_let()] = move(figure);
        }
        fin.close();
        return true;
    }
    return false;
}

void Chess::Save_game(vector<vector<unique_ptr<Figures>>> &field, Players *players, const string &saves_path, short charge)
{
    ofstream fout;
    string save_name;
    mkdir("../saves");
    do
    {
        cout << "Please, enter a name of a saving\t";
        cin >> save_name;
        fout.open(saves_path + save_name + ".txt", ofstream::app);
        if (!fout.is_open())
        {
            cout << "Incorrect name! Please, try again." << endl;
        }
    } while (!fout.is_open());

    if (fout.is_open())
    {
        fout << charge << endl;
        for (int i = 0; i < 2; ++i)
        {
            fout << players[i].Get_color() << endl;
            fout << players[i].Get_king_let() << endl;
            fout << players[i].Get_king_num() << endl;
            fout << players[i].Get_name() << endl;

            for (int j = 0; j < players[i].Get_moves().size(); ++j)
            {
                fout << players[i].Get_moves()[j] << endl;
            }
            fout << "moves_vector_end" << endl;

            for (int j = 0; j < players[i].Get_time().size(); ++j)
            {
                fout << players[i].Get_time()[j] << endl;
            }
            fout << "time_vector_end" << endl;
        }

        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                if (field[i][j] != nullptr)
                {
                    fout << field[i][j]->Get_sign() << endl;
                    fout << field[i][j]->Get_color() << endl;
                    fout << field[i][j]->Get_moved() << endl;
                    fout << field[i][j]->Get_let() << endl;
                    fout << field[i][j]->Get_num() << endl;
                }
            }
        }
        fout.close();
    }
}

vector<vector<unique_ptr<Figures>>> Chess::Field_builder()
{
    vector<vector<unique_ptr<Figures >>> field(8);

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            field[i].push_back(nullptr);
        }
    }
    return field;
}

void Chess::Default_filler(vector<vector<unique_ptr<Figures>>> &field)
{
    for (short i = 0; i < 8; ++i)
    {
        for (short j = 0; j < 8; ++j)
        {
            if (field[i][j] != nullptr)
            {
                field[i][j].reset(nullptr);
            }
        }
    }

    for (short i = 0; i < 8; ++i)
    {
        field[1][i] = unique_ptr<Pawn>(new Pawn(true, i, 1));
        field[6][i] = unique_ptr<Pawn>(new Pawn(false, i, 6));
    }

    field[0][0] = unique_ptr<Rock>(new Rock(true, 0, 0));
    field[7][0] = unique_ptr<Rock>(new Rock(false, 0, 7));

    field[0][1] = unique_ptr<Knight>(new Knight(true, 1, 0));
    field[7][1] = unique_ptr<Knight>(new Knight(false, 1, 7));

    field[0][2] = unique_ptr<Bishop>(new Bishop(true, 2, 0));
    field[7][2] = unique_ptr<Bishop>(new Bishop(false, 2, 7));

    field[0][3] = unique_ptr<Queen>(new Queen(true, 3, 0));
    field[7][3] = unique_ptr<Queen>(new Queen(false, 3, 7));

    field[0][4] = unique_ptr<King>(new King(true, 4, 0));
    field[7][4] = unique_ptr<King>(new King(false, 4, 7));

    field[0][5] = unique_ptr<Bishop>(new Bishop(true, 5, 0));
    field[7][5] = unique_ptr<Bishop>(new Bishop(false, 5, 7));

    field[0][6] = unique_ptr<Knight>(new Knight(true, 6, 0));
    field[7][6] = unique_ptr<Knight>(new Knight(false, 6, 7));

    field[0][7] = unique_ptr<Rock>(new Rock(true, 7, 0));
    field[7][7] = unique_ptr<Rock>(new Rock(false, 7, 7));
}

Players *Chess::Ident_players()
{
    auto *players = new Players[2];
    string name, rand_choise;

    for (short i = 0; i < 2; ++i)
    {
        cout << "Please, player No" << i + 1 << ", enter your name: ";
        cin >> name;
        players[i].Set_name(name);
    }

    do
    {
        cout << "input 'y' if you want to randomize the sides, unless - input 'n' : ";
        cin >> rand_choise;
    } while (rand_choise != "y" && rand_choise != "n");

    srand(time(NULL));

    if (rand_choise == "y" && static_cast<bool>(rand() % 2))
    {
        players[0].Set_color(false);
        players[0].Set_king(4, 7);
        players[1].Set_color(true);
        players[1].Set_king(4, 0);
    } else
    {
        players[0].Set_color(true);
        players[0].Set_king(4, 0);
        players[1].Set_color(false);
        players[1].Set_king(4, 7);
    }
    return players;
}

void Chess::Show_field(vector<vector<unique_ptr<Figures>>> &field)
{
    char letter = 'a';
    cout << "    ";
    for (short i = 0; i < 8; ++i)
    {
        cout << setw(3) << char(letter + i);
    }
    cout << endl;
    cout << "    ";
    for (short i = 0; i < 8; ++i)
    {
        cout << setw(3) << "-";
    }
    cout << endl;
    for (short i = 7; i >= 0; --i)
    {
        cout << i + 1 << setw(3) << "|";
        for (short j = 0; j < 8; ++j)
        {
            if (field[i][j] != nullptr)
            {
                cout << setw(3) << field[i][j]->Get_sign();
            } else
            {
                cout << setw(3) << "*";
            }
        }
        cout << setw(3) << "|" << setw(3) << i + 1 << endl;
    }
    cout << "    ";
    for (short i = 0; i < 8; ++i)
    {
        cout << setw(3) << "-";
    }
    cout << endl;
    cout << "    ";
    for (short i = 0; i < 8; ++i)
    {
        cout << setw(3) << char(letter + i);
    }
    cout << endl;
}

bool Chess::Two_kings_draw(vector<vector<unique_ptr<Figures>>> &field)
{
    short counter = 0;
    for (short i = 0; i < 8 && counter <= 2; ++i)
    {
        for (int j = 0; j < 8 && counter <= 2; ++j)
        {
            if (field[i][j] != nullptr)
            {
                counter++;
            }
        }
    }
    return counter <= 2;
}

bool Chess::Check_checkmate_or_rogue(vector<vector<unique_ptr<Figures>>> &field, Players &player)
{
    string error = "";
    for (short i = 0; i < 8; ++i)
    {
        for (short j = 0; j < 8; ++j)
        {
            if (field[i][j] != nullptr && field[i][j]->Get_color() == player.Get_color())
            {
                if (Moving_possibility(field, field[i][j], player, error))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Chess::Check_cell_name(string &cell, short &let, short &num, string &error)
{
    if (cell.length() == 2)
    {
        if (cell[0] < 'a')
        {
            cell[0] += 32;
        }
        let = cell[0] - 'a';
        num = cell[1] - '1';
        error = "";
        return true;
    }
    error = "Incorrect name of a cell! Please, try again\n";
    return false;
}

bool Chess::Check_cell_number(short let, short num, string &error)
{
    if (let < 0 || let > 7 || num < 0 || num > 7)
    {
        error = "Incorrect number of a cell! Please, try again\n";
        return false;
    }
    error = "";
    return true;
}

bool Chess::Check_cell_figure(vector<vector<unique_ptr<Figures>>> &field, Players &player, short &let, short &num, string &error)
{
    if (field[num][let] != nullptr && field[num][let]->Get_color() == player.Get_color())
    {
        error = "";
        return true;
    }
    error = "There's no your figure on this cell. Please, Try again\n";
    return false;
}

bool Chess::Check_cell(string &cell, vector<vector<unique_ptr<Figures>>> &field, Players &player, short &let, short &num, string &error)
{
    return Check_cell_name(cell, let, num, error) && Check_cell_number(let, num, error) && Check_cell_figure(field, player, let, num, error);
}

bool Chess::Check_Shah(vector<vector<unique_ptr<Figures>>> &field, unique_ptr<Figures> &figure, Players &player, short let, short num, string &error)
{
    unique_ptr<Figures> temp = nullptr;
    bool shah = false;

    if (num != figure->Get_num() || let != figure->Get_let())
    {
        if(figure->Get_let() == player.Get_king_let() && figure->Get_num() == player.Get_king_num())
        {
            King_changer(player, let, num);
        }

        if (field[num][let] != nullptr)
        {
            temp = move(field[num][let]);
        }
        field[num][let] = move(field[figure->Get_num()][figure->Get_let()]);
    }

    for (short i = 0; i < 8 && !shah; ++i)
    {
        for (short j = 0; j < 8 && !shah; ++j)
        {
            if (field[i][j] != nullptr && field[i][j]->Get_color() == !player.Get_color())
            {
                shah = field[i][j]->Beat_move(field, !player.Get_color(), player.Get_king_let(), player.Get_king_num());
            }
        }
    }

    if (num != field[num][let]->Get_num() || let != field[num][let]->Get_let())
    {
        if(let == player.Get_king_let() && num == player.Get_king_num())
        {
            King_changer(player, field[num][let]->Get_let(), field[num][let]->Get_num());
        }

        field[field[num][let]->Get_num()][field[num][let]->Get_let()] = move(field[num][let]);
        if (temp != nullptr)
        {
            field[num][let] = move(temp);
        }
    }

    if (shah)
    {
        error = "There's a shah to you with this move!";
    } else
    {
        error = "";
    }
    return shah;
}

void Chess::King_changer(Players &player, short let, short num)
{
    player.Set_king(let, num);
}

bool Chess::Check_movement(vector<vector<unique_ptr<Figures>>> &field, unique_ptr<Figures> &figure, Players &player, short let, short num, string &error)
{
    bool res = figure->Check_move_direction(field, player, let, num, error) && !Check_Shah(field, figure, player, let, num, error);
    if(figure->Get_let() == player.Get_king_let() && figure->Get_num() == player.Get_king_num() && !res)
    {
        return Check_rogue(field, figure, player, let, num, error);
    }
    return res;
}

void Chess::Movement(vector<vector<unique_ptr<Figures>>> &field, unique_ptr<Figures> &figure, Players &player, short let, short num)
{
    if(figure->Get_let() == player.Get_king_let() && figure->Get_num() == player.Get_king_num())
    {
        if (!figure->Beat_move(field, player.Get_color(), let, num))
        {
            if (let < figure->Get_let())
            {
                Movement(field, field[figure->Get_num()][0], player, 3, figure->Get_num());
            } else
            {
                Movement(field, field[figure->Get_num()][7], player, 5, figure->Get_num());
            }
        }
    }
    field[num][let].reset(field[figure->Get_num()][figure->Get_let()].release());

    field[num][let]->Set_num(num);
    field[num][let]->Set_let(let);
    field[num][let]->Set_moved(true);

    field[num][let]->Past_move(field, player, let, num);
}

bool Chess::Moving_possibility(vector<vector<unique_ptr<Figures>>> &field, unique_ptr<Figures> &figure, Players &player, string &error)
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
         if(Check_movement(field, figure, player, i, j, error))
            {
                error = "";
                return true;
            }
        }
    }
    if(figure->Get_let() == player.Get_king_let() && figure->Get_num() == player.Get_king_num())
    {
        if(Check_rogue(field, figure, player, 2, 0, error) || Check_rogue(field, figure, player, 6, 0, error))
        {
            error = "";
            return true;
        }
    }
    error = "There isn't any possible moves for this figure right now!\n";
    return false;
}

bool Chess::Check_rogue(vector<vector<unique_ptr<Figures>>> &field, unique_ptr<Figures> &figure, Players &player, short let, short num, string &error)
{
    if (!figure->Get_moved() && num == figure->Get_num() && abs(figure->Get_let() - let) == 2)
    {
        if (let > figure->Get_let())
        {
            if (field[figure->Get_num()][7] != nullptr && !field[figure->Get_num()][7]->Get_moved())
            {
                for (short i = figure->Get_let() + 1; i < 7; ++i)
                {
                    if (field[figure->Get_num()][i] != nullptr)
                    {
                        return false;
                    }
                }
                for (short i = figure->Get_let(); i < figure->Get_let() + 3; ++i)
                {

                    if (Check_Shah(field, figure, player, i, figure->Get_num(), error))
                    {
                        return false;
                    }
                }
                return true;
            }
        } else
        {
            if (field[figure->Get_num()][0] != nullptr && !field[figure->Get_num()][0]->Get_moved())
            {
                for (short i = figure->Get_let() - 1; i > 0; --i)
                {
                    if (field[figure->Get_num()][i] != nullptr)
                    {
                        return false;
                    }
                }
                for (short i = figure->Get_let(); i > figure->Get_let() - 3; --i)
                {
                    if (Check_Shah(field, figure, player, i, figure->Get_num(), error))
                    {
                        return false;
                    }
                }
                return true;
            }
        }
    }
    return false;
}

void Chess::Game()
{
    bool endgame;
    short charge;
    short num;
    short let;
    int start_time;
    string command;
    string error;
    bool loading;
    const string saves_path = "..\\saves\\";

    vector<vector<unique_ptr<Figures>>> field = Field_builder();
    Players *players;

    do
    {
        do
        {
            cout << "For beginning new game enter \"new\", please" << endl
                 << "For loading game enter \"load\", please\t";
            cin >> command;
        } while (command != "new" && command != "load");


        if (command == "load")
        {
            players = new Players[2];
            loading = Load_game(field, players, saves_path, charge);
        } else
        {
            players = Ident_players();
            Default_filler(field);
            loading = true;
        }
    } while (!loading);

    do
    {
        if (command == "y")
        {
            Default_filler(field);
        }

        if (command != "load")
        {
            if (players[0].Get_color())
            {
                charge = 0;
            } else
            {
                charge = 1;
            }
        }
        error = "";
        command = "";
        endgame = false;

        Show_field(field);
        do
        {
            if (command != "undo")
            {
                start_time = clock();
            }
            do
            {
                cout << error << endl;
                cout << players[charge].Get_name() << ", choose a figure to move (write down it's position)" << endl
                     << "Or you can give up by writing down command \"defeat\"" << endl
                     << "If you want to save the game and quit, write down command \"save\"" << endl;
                cin >> command;
                if (command == "defeat" || command == "save")
                {
                    break;
                }
            } while (!Check_cell(command, field, players[charge], let, num, error) ||
                     !Moving_possibility(field, field[num][let], players[charge], error));

            if (command == "defeat")
            {
                endgame = true;
                cout << "Well, ok, you've given up." << endl << "Winner is " << players[(charge + 1) % 2].Get_name();
                break;
            }
            if (command == "save")
            {
                break;
            }
            players[charge].Add_move(command);
            unique_ptr<Figures> &temp = field[num][let];

            do
            {
                cout << error << endl;
                cout << "Write down position to move (or write down \"undo\" to undo your choise) :" << endl;
                cin >> command;
                if (command == "undo")
                {
                    players[charge].Remove_move();
                    break;
                }

            } while (!Check_cell_name(command, let, num, error) ||
                     !Check_cell_number(let, num, error) ||
                     !Check_movement(field, temp, players[charge], let, num, error));
            if (command != "undo" && command != "defeat")
            {
                Movement(field, temp, players[charge], let, num);
                players[charge].Add_move(command);
                players[charge].Add_time((clock() - start_time) / 1000);
                ++charge %= 2;

                if (Check_checkmate_or_rogue(field, players[charge]))
                {
                    if (Check_Shah(field, field[players[charge].Get_king_num()][players[charge].Get_king_let()],
                                   players[charge], players[charge].Get_king_let(), players[charge].Get_king_num(), error))
                    {
                        cout << "It is a checkmate!" << endl << "Winner is " << players[(charge + 1) % 2].Get_name()
                             << endl
                             << "Congratulations!" << endl;
                    } else
                    {
                        cout << "It seems to be a rogue here. Well, it's draw!" << endl;
                    }
                    endgame = true;
                } else if (Two_kings_draw(field))
                {
                    cout << "The fight is over and it's another draw!" << endl;
                    endgame = true;
                } else if (Check_Shah(field, field[players[charge].Get_king_num()][players[charge].Get_king_let()],
                                      players[charge], players[charge].Get_king_let(), players[charge].Get_king_num(), error))
                {
                    cout << "It's a check to your brave king, " << players[charge].Get_name() << "!" << endl;
                    error = "";
                }
                Show_field(field);
            }
        } while (!endgame);

        if (endgame)
        {
            Players::Show_results(players);
            Players::Clear(players);

            cout << "Do you want to play once more? ( \"y\" or \"n\"):\t";
            do
            {
                cin >> command;
                if (command != "y" && command != "n")
                {
                    cout << "Incorrect input! Please, try again!" << endl;
                }
            } while (command != "y" && command != "n");
        } else
        {
            Save_game(field, players, saves_path, charge);
        }
    } while (command == "y");

    delete []players;
}