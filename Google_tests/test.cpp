#include "gtest/gtest.h"
#include "../Chess.cpp"

TEST(check_sell, check_all)
{
    string error = "";

    short let;
    short num;
    string cell = "";

    vector<vector<unique_ptr<Figures>>> field = Chess::Field_builder();
    Chess::Default_filler(field);

    vector<Players> players(2);
    players[0].Set_king(4, 0);
    players[0].Set_color(true);
    players[1].Set_king(4, 7);
    players[1].Set_color(false);

    cell = "asd";
    EXPECT_FALSE(Chess::Check_cell(cell, field, players[0], let, num, error));
    EXPECT_FALSE(Chess::Check_cell(cell, field, players[1], let, num, error));

    cell = "B7";
    EXPECT_FALSE(Chess::Check_cell(cell, field, players[0], let, num, error));
    EXPECT_TRUE(Chess::Check_cell(cell, field, players[1], let, num, error));

    cell = "a2";
    EXPECT_TRUE(Chess::Check_cell(cell, field, players[0], let, num, error));
    EXPECT_FALSE(Chess::Check_cell(cell, field, players[1], let, num, error));

    cell = "a9";
    EXPECT_FALSE(Chess::Check_cell(cell, field, players[0], let, num, error));
    EXPECT_FALSE(Chess::Check_cell(cell, field, players[1], let, num, error));

    cell = "k3";
    EXPECT_FALSE(Chess::Check_cell(cell, field, players[0], let, num, error));
    EXPECT_FALSE(Chess::Check_cell(cell, field, players[1], let, num, error));
}

TEST(check_sell, check_sell_name)
{
    string error = "";

    short let;
    short num;

    string cell = "asd";
    EXPECT_FALSE(Chess::Check_cell_name(cell, let, num, error));

    cell = "f";
    EXPECT_FALSE(Chess::Check_cell_name(cell, let, num, error));

    cell = "4";
    EXPECT_FALSE(Chess::Check_cell_name(cell, let, num, error));

    cell = "K3";
    EXPECT_TRUE(Chess::Check_cell_name(cell, let, num, error));

    cell = "d8";
    EXPECT_TRUE(Chess::Check_cell_name(cell, let, num, error));
}

TEST(check_sell, check_sell_number)
{
    string error = "";

    short let = 0;
    short num = 0;
    EXPECT_TRUE(Chess::Check_cell_number(let, num, error));

    let = -1;
    EXPECT_FALSE(Chess::Check_cell_number(let, num, error));

    let = 8;
    EXPECT_FALSE(Chess::Check_cell_number(let, num, error));

    let = 0;
    num = -1;
    EXPECT_FALSE(Chess::Check_cell_number(let, num, error));

    num = 8;
    EXPECT_FALSE(Chess::Check_cell_number(let, num, error));
}

TEST(check_sell, check_sell_figure)
{
    string error = "";

    short let;
    short num;

    vector<vector<unique_ptr<Figures>>> field = Chess::Field_builder();
    Chess::Default_filler(field);

    vector<Players> players(2);
    players[0].Set_king(4, 0);
    players[0].Set_color(true);
    players[1].Set_king(4, 7);
    players[1].Set_color(false);

    let = 3;
    num = 3;
    EXPECT_FALSE(Chess::Check_cell_figure(field, players[0], let, num, error));
    EXPECT_FALSE(Chess::Check_cell_figure(field, players[1], let, num, error));

    num = 7;
    EXPECT_FALSE(Chess::Check_cell_figure(field, players[0], let, num, error));
    EXPECT_TRUE(Chess::Check_cell_figure(field, players[1], let, num, error));

    num = 1;
    EXPECT_TRUE(Chess::Check_cell_figure(field, players[0], let, num, error));
    EXPECT_FALSE(Chess::Check_cell_figure(field, players[1], let, num, error));
}

TEST(check_movement, pawn)
{
    string error = "";
    short let;
    short num;

    vector<vector<unique_ptr<Figures>>> field = Chess::Field_builder();

    vector<Players> players(2);
    players[0].Set_king(4, 0);
    players[0].Set_color(true);
    players[1].Set_king(4, 7);
    players[1].Set_color(false);

    field[0][4] = unique_ptr<King>(new King(true, 4, 0));
    field[7][4] = unique_ptr<King>(new King(false, 4, 7));

    field[1][7] = unique_ptr<Pawn>(new Pawn(true, 7, 1));
    field[1][6] = unique_ptr<Pawn>(new Pawn(true, 6, 1));
    field[1][3] = unique_ptr<Pawn>(new Pawn(true, 3, 1));

    field[3][1] = unique_ptr<Bishop>(new Bishop(false, 1, 3));
    field[2][6] = unique_ptr<Rock>(new Rock(false, 6, 2));

    let = 3;
    num = 2;
    EXPECT_FALSE(Chess::Check_movement(field, field[1][3], players[0], let, num, error));

    let = 5;
    num = 2;
    EXPECT_FALSE(Chess::Check_movement(field, field[1][6], players[0], let, num, error));

    let = 6;
    num = 2;
    EXPECT_FALSE(Chess::Check_movement(field, field[1][6], players[0], let, num, error));

    let = 6;
    num = 2;
    EXPECT_TRUE(Chess::Check_movement(field, field[1][7], players[0], let, num, error));

    let = 7;
    num = 2;
    EXPECT_TRUE(Chess::Check_movement(field, field[1][7], players[0], let, num, error));

    let = 7;
    num = 3;
    EXPECT_TRUE(Chess::Check_movement(field, field[1][7], players[0], let, num, error));
}

TEST(check_movement, knight)
{
    string error = "";
    short let;
    short num;

    vector<vector<unique_ptr<Figures>>> field = Chess::Field_builder();

    vector<Players> players(2);
    players[0].Set_king(4, 0);
    players[0].Set_color(true);
    players[1].Set_king(4, 7);
    players[1].Set_color(false);

    field[0][4] = unique_ptr<King>(new King(true, 4, 0));
    field[7][4] = unique_ptr<King>(new King(false, 4, 7));

    field[4][2] = unique_ptr<Knight>(new Knight(true, 2, 4));
    field[4][7] = unique_ptr<Knight>(new Knight(true, 7, 4));

    field[2][6] = unique_ptr<Knight>(new Knight(false, 6, 2));

    field[3][5] = unique_ptr<Pawn>(new Pawn(true, 5, 3));
    field[5][5] = unique_ptr<Pawn>(new Pawn(true, 5, 5));
    field[6][6] = unique_ptr<Pawn>(new Pawn(true, 6, 6));

    let = 6;
    num = 6;
    EXPECT_FALSE(Chess::Check_movement(field, field[4][7], players[0], let, num, error));

    let = 5;
    num = 5;
    EXPECT_FALSE(Chess::Check_movement(field, field[4][7], players[0], let, num, error));

    let = 5;
    num = 3;
    EXPECT_FALSE(Chess::Check_movement(field, field[4][7], players[0], let, num, error));

    let = 6;
    num = 2;
    EXPECT_TRUE(Chess::Check_movement(field, field[4][7], players[0], let, num, error));

    let = 1;
    num = 5;
    EXPECT_FALSE(Chess::Check_movement(field, field[4][2], players[0], let, num, error));

    let = 0;
    num = 6;
    EXPECT_FALSE(Chess::Check_movement(field, field[4][2], players[0], let, num, error));

    let = 1;
    num = 6;
    EXPECT_TRUE(Chess::Check_movement(field, field[4][2], players[0], let, num, error));

    let = 3;
    num = 6;
    EXPECT_TRUE(Chess::Check_movement(field, field[4][2], players[0], let, num, error));

    let = 0;
    num = 5;
    EXPECT_TRUE(Chess::Check_movement(field, field[4][2], players[0], let, num, error));

    let = 4;
    num = 5;
    EXPECT_TRUE(Chess::Check_movement(field, field[4][2], players[0], let, num, error));

    let = 0;
    num = 3;
    EXPECT_TRUE(Chess::Check_movement(field, field[4][2], players[0], let, num, error));

    let = 4;
    num = 3;
    EXPECT_TRUE(Chess::Check_movement(field, field[4][2], players[0], let, num, error));

    let = 1;
    num = 2;
    EXPECT_TRUE(Chess::Check_movement(field, field[4][2], players[0], let, num, error));

    let = 3;
    num = 2;
    EXPECT_TRUE(Chess::Check_movement(field, field[4][2], players[0], let, num, error));
}

TEST(check_movement, rock)
{
    string error = "";
    short let;
    short num;

    vector<vector<unique_ptr<Figures>>> field = Chess::Field_builder();

    vector<Players> players(2);
    players[0].Set_king(4, 0);
    players[0].Set_color(true);
    players[1].Set_king(4, 7);
    players[1].Set_color(false);

    field[0][4] = unique_ptr<King>(new King(true, 4, 0));
    field[7][4] = unique_ptr<King>(new King(false, 4, 7));

    field[1][4] = unique_ptr<Rock>(new Rock(true, 4, 1));
    field[6][4] = unique_ptr<Rock>(new Rock(false, 4, 6));
    field[1][2] = unique_ptr<Rock>(new Rock(false, 2, 1));

    let = 4;
    num = 0;
    EXPECT_FALSE(Chess::Check_movement(field, field[1][4], players[0], let, num, error));

    let = 0;
    num = 1;
    EXPECT_FALSE(Chess::Check_movement(field, field[1][4], players[0], let, num, error));

    let = 4;
    num = 7;
    EXPECT_FALSE(Chess::Check_movement(field, field[1][4], players[0], let, num, error));

    let = 4;
    num = 3;
    EXPECT_TRUE(Chess::Check_movement(field, field[1][4], players[0], let, num, error));

    let = 4;
    num = 6;
    EXPECT_TRUE(Chess::Check_movement(field, field[1][4], players[0], let, num, error));
}

TEST(check_movement, bishop)
{
    string error = "";
    short let;
    short num;

    vector<vector<unique_ptr<Figures>>> field = Chess::Field_builder();

    vector<Players> players(2);
    players[0].Set_king(4, 0);
    players[0].Set_color(true);
    players[1].Set_king(4, 7);
    players[1].Set_color(false);

    field[0][4] = unique_ptr<King>(new King(true, 4, 0));
    field[7][4] = unique_ptr<King>(new King(false, 4, 7));

    field[2][2] = unique_ptr<Bishop>(new Bishop(true, 2, 2));
    field[3][1] = unique_ptr<Queen>(new Queen(false, 1, 3));

    let = 4;
    num = 0;
    EXPECT_FALSE(Chess::Check_movement(field, field[2][2], players[0], let, num, error));

    let = 1;
    num = 1;
    EXPECT_FALSE(Chess::Check_movement(field, field[2][2], players[0], let, num, error));

    let = 0;
    num = 4;
    EXPECT_FALSE(Chess::Check_movement(field, field[2][2], players[0], let, num, error));

    let = 1;
    num = 3;
    EXPECT_TRUE(Chess::Check_movement(field, field[2][2], players[0], let, num, error));

    let = 3;
    num = 1;
    EXPECT_TRUE(Chess::Check_movement(field, field[2][2], players[0], let, num, error));
}

TEST(check_movement, queen)
{
    string error = "";
    short let;
    short num;

    vector<vector<unique_ptr<Figures>>> field = Chess::Field_builder();

    vector<Players> players(2);
    players[0].Set_king(4, 0);
    players[0].Set_color(true);
    players[1].Set_king(4, 7);
    players[1].Set_color(false);

    field[0][4] = unique_ptr<King>(new King(true, 4, 0));
    field[7][4] = unique_ptr<King>(new King(false, 4, 7));

    field[3][5] = unique_ptr<Queen>(new Queen(true, 5, 3));
    field[5][3] = unique_ptr<Queen>(new Queen(false, 3, 5));

    field[3][7] = unique_ptr<Pawn>(new Pawn(true, 7, 3));

    let = 4;
    num = 5;
    EXPECT_FALSE(Chess::Check_movement(field, field[3][5], players[0], let, num, error));

    let = 1;
    num = 7;
    EXPECT_FALSE(Chess::Check_movement(field, field[3][5], players[0], let, num, error));

    let = 7;
    num = 3;
    EXPECT_FALSE(Chess::Check_movement(field, field[3][5], players[0], let, num, error));

    let = 0;
    num = 3;
    EXPECT_TRUE(Chess::Check_movement(field, field[3][5], players[0], let, num, error));

    let = 6;
    num = 2;
    EXPECT_TRUE(Chess::Check_movement(field, field[3][5], players[0], let, num, error));

    let = 3;
    num = 5;
    EXPECT_TRUE(Chess::Check_movement(field, field[3][5], players[0], let, num, error));
}

TEST(check_movement, king)
{
    string error = "";
    short let;
    short num;

    vector<vector<unique_ptr<Figures>>> field = Chess::Field_builder();

    vector<Players> players(2);
    players[0].Set_king(4, 0);
    players[0].Set_color(true);
    players[1].Set_king(4, 7);
    players[1].Set_color(false);

    field[0][4] = unique_ptr<King>(new King(true, 4, 0));
    field[7][4] = unique_ptr<King>(new King(false, 4, 7));

    field[3][5] = unique_ptr<Queen>(new Queen(false, 5, 3));
    field[1][5] = unique_ptr<Knight>(new Knight(false, 5, 1));

    field[0][0] = unique_ptr<Rock>(new Rock(true, 0, 0));
    field[0][7] = unique_ptr<Rock>(new Rock(true, 7, 0));

    let = 3;
    num = 0;
    EXPECT_FALSE(Chess::Check_movement(field, field[0][4], players[0], let, num, error));

    let = 4;
    num = 2;
    EXPECT_FALSE(Chess::Check_movement(field, field[0][4], players[0], let, num, error));

    let = 5;
    num = 0;
    EXPECT_TRUE(Chess::Check_movement(field, field[0][4], players[0], let, num, error));

    let = 4;
    num = 1;
    EXPECT_TRUE(Chess::Check_movement(field, field[0][4], players[0], let, num, error));

    let = 6;
    num = 0;
    EXPECT_TRUE(Chess::Check_movement(field, field[0][4], players[0], let, num, error));
}

TEST(endgame, two_kings_draw)
{
    vector<vector<unique_ptr<Figures>>> field = Chess::Field_builder();
    field[0][4] = unique_ptr<King>(new King(true, 4, 0));
    field[7][4] = unique_ptr<King>(new King(false, 4, 7));
    EXPECT_TRUE(Chess::Two_kings_draw(field));

    field[1][1] = unique_ptr<Pawn>(new Pawn(false, 1, 1));
    EXPECT_FALSE(Chess::Two_kings_draw(field));
}

TEST(endgame, Rogue)
{
    vector<vector<unique_ptr<Figures>>> field = Chess::Field_builder();
    field[0][7] = unique_ptr<King>(new King(true, 7, 0));
    field[7][4] = unique_ptr<King>(new King(false, 4, 7));

    string error = "";
    vector<Players> players(2);
    players[0].Set_king(7, 0);
    players[0].Set_color(true);
    players[1].Set_king(4, 7);
    players[1].Set_color(false);

    field[2][6] = unique_ptr<Queen>(new Queen(false, 6, 2));

    field[3][0] = unique_ptr<Pawn>(new Pawn(true, 0, 3));
    field[4][0] = unique_ptr<Rock>(new Rock(false, 0, 4));

    EXPECT_TRUE(Chess::Check_checkmate_or_rogue(field, players[0]));
}

TEST(endgame, Checkmate)
{
    vector<vector<unique_ptr<Figures>>> field = Chess::Field_builder();
    field[0][7] = unique_ptr<King>(new King(true, 7, 0));
    field[7][4] = unique_ptr<King>(new King(false, 4, 7));

    vector<Players> players(2);
    players[0].Set_king(7, 0);
    players[0].Set_color(true);
    players[1].Set_king(4, 7);
    players[1].Set_color(false);


    field[1][6] = unique_ptr<Queen>(new Queen(false, 6, 1));
    field[7][6] = unique_ptr<Rock>(new Rock(false, 6, 7));


    field[3][0] = unique_ptr<Pawn>(new Pawn(true, 0, 3));
    field[4][0] = unique_ptr<Rock>(new Rock(false, 0, 4));

    EXPECT_TRUE(Chess::Check_checkmate_or_rogue(field, players[0]));
}

TEST(moving_possibility, rock)
{
    vector<vector<unique_ptr<Figures>>> field = Chess::Field_builder();
    Chess::Default_filler(field);

    string error = "";
    vector<Players> players(2);
    players[0].Set_king(4, 0);
    players[0].Set_color(true);
    players[1].Set_king(4, 7);
    players[1].Set_color(false);

    EXPECT_FALSE(Chess::Moving_possibility(field, field[0][0], players[0], error));
    EXPECT_FALSE(Chess::Moving_possibility(field, field[7][7], players[1], error));

    field[0][1].reset(nullptr);
    field[6][7].reset(nullptr);

    EXPECT_TRUE(Chess::Moving_possibility(field, field[0][0], players[0], error));
    EXPECT_TRUE(Chess::Moving_possibility(field, field[7][7], players[1], error));
}

TEST(moving_possibility, bishop)
{
    vector<vector<unique_ptr<Figures>>> field = Chess::Field_builder();
    Chess::Default_filler(field);
    string error = "";
    vector<Players> players(2);
    players[0].Set_king(4, 0);
    players[0].Set_color(true);
    players[1].Set_king(4, 7);
    players[1].Set_color(false);

    EXPECT_FALSE(Chess::Moving_possibility(field, field[0][2], players[0], error));
    EXPECT_FALSE(Chess::Moving_possibility(field, field[7][5], players[1], error));

    field[1][1].reset(nullptr);
    field[6][6].reset(nullptr);

    EXPECT_TRUE(Chess::Moving_possibility(field, field[0][2], players[0], error));
    EXPECT_TRUE(Chess::Moving_possibility(field, field[7][5], players[1], error));
}

TEST(moving_possibility, queen)
{
    vector<vector<unique_ptr<Figures>>> field = Chess::Field_builder();
    Chess::Default_filler(field);
    string error = "";
    vector<Players> players(2);
    players[0].Set_king(4, 0);
    players[0].Set_color(true);
    players[1].Set_king(4, 7);
    players[1].Set_color(false);

    EXPECT_FALSE(Chess::Moving_possibility(field, field[0][3], players[0], error));
    EXPECT_FALSE(Chess::Moving_possibility(field, field[7][3], players[1], error));

    field[0][4].reset(nullptr);
    field[6][4].reset(nullptr);

    EXPECT_TRUE(Chess::Moving_possibility(field, field[0][3], players[0], error));
    EXPECT_TRUE(Chess::Moving_possibility(field, field[7][3], players[1], error));
}

TEST(moving_possibility, king)
{
    vector<vector<unique_ptr<Figures>>> field = Chess::Field_builder();
    Chess::Default_filler(field);
    string error = "";
    vector<Players> players(2);
    players[0].Set_king(4, 0);
    players[0].Set_color(true);
    players[1].Set_king(4, 7);
    players[1].Set_color(false);

    EXPECT_FALSE(Chess::Moving_possibility(field, field[0][4], players[0], error));
    EXPECT_FALSE(Chess::Moving_possibility(field, field[7][4], players[1], error));

    field[1][4].reset(nullptr);
    field[6][4].reset(nullptr);

    EXPECT_TRUE(Chess::Moving_possibility(field, field[0][4], players[0], error));
    EXPECT_TRUE(Chess::Moving_possibility(field, field[7][4], players[1], error));
}

TEST(moving_possibility, pawn)
{
    vector<vector<unique_ptr<Figures>>> field = Chess::Field_builder();
    field[0][4] = unique_ptr<King>(new King(true, 4, 0));
    field[7][4] = unique_ptr<King>(new King(false, 4, 7));

    string error = "";
    vector<Players> players(2);
    players[0].Set_king(4, 0);
    players[0].Set_color(true);
    players[1].Set_king(4, 7);
    players[1].Set_color(false);

    field[3][0] = unique_ptr<Pawn>(new Pawn(true, 0, 3));
    field[4][0] = unique_ptr<Rock>(new Rock(false, 0, 4));

    EXPECT_FALSE(Chess::Moving_possibility(field, field[3][0], players[0], error));

    field[4][1] = unique_ptr<Rock>(new Rock(false, 1, 4));

    EXPECT_TRUE(Chess::Moving_possibility(field, field[3][0], players[0], error));
}

TEST(moving_possibility, knight)
{
    vector<vector<unique_ptr<Figures>>> field = Chess::Field_builder();
    field[0][4] = unique_ptr<King>(new King(true, 4, 0));
    field[7][4] = unique_ptr<King>(new King(false, 4, 7));

    string error = "";
    vector<Players> players(2);
    players[0].Set_king(4, 0);
    players[0].Set_color(true);
    players[1].Set_king(4, 7);
    players[1].Set_color(false);

    field[1][4] = unique_ptr<Knight>(new Knight(true, 4, 1));
    field[6][4] = unique_ptr<Rock>(new Rock(false, 4, 6));

    EXPECT_FALSE(Chess::Moving_possibility(field, field[1][4], players[0], error));

    field[6][4].reset(nullptr);

    EXPECT_TRUE(Chess::Moving_possibility(field, field[1][4], players[0], error));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}