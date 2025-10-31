/**
 * @file GameTest.cpp
 * @author Serena Brown
 */



#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <memory>
#include <GameView.h>
#include <wx/string.h>
#include <wx/filename.h>


using namespace std;


TEST(GameTest, BasicLevelLoad) {
    Game game;
    // game.LoadLevel("levels/level0.xml");
    // game.Clear();
    for (int level = 0; level <= 3; level++) {
        wxString filename = wxString::Format(L"levels/level%d.xml", level);
        game.LoadLevel(filename.ToStdString());

        game.Clear();
    }
    SUCCEED();
}


TEST(GameTest, AddPlayer) {
    Game game;

    ASSERT_TRUE(game.GetItems().empty());

    game.AddPlayer(&game, 1, 1, 50, 50, L"sparty.png", L"sparty-mouth.png", 1.5, 40, 86);
    game.AddPlayer(&game, 2, 2, 50, 50, L"chest.png", L"chest-lid.png", 0.8, 30, 86);

    ASSERT_FALSE(game.GetItems().empty());
}

TEST(GameTest, AddLetter) {
    Game game;

    ASSERT_TRUE(game.GetItems().empty());

    game.AddLetter(&game, 1, 1, 50, 50, L"al.png", 10);
    game.AddLetter(&game, 2, 2, 50, 50, L"bl.png", 11);

    ASSERT_FALSE(game.GetItems().empty());
}

TEST(GameTest, AddGiven) {
    Game game;

    ASSERT_TRUE(game.GetItems().empty());

    game.AddGiven(&game, 1, 1, 50, 50, L"ad.png", 10);
    game.AddGiven(&game, 2, 2, 50, 50, L"bd.png", 11);

    ASSERT_FALSE(game.GetItems().empty());
}

TEST(GameTest, AddTray) {
    Game game;

    ASSERT_TRUE(game.GetItems().empty());

    game.AddTray(&game, 1, 1, 50, 50, L"tray.png", 5);

    ASSERT_FALSE(game.GetItems().empty());
}

TEST(GameTest, Clear) {
    Game game;

    game.AddPlayer(&game, 1, 1, 50, 50, L"sparty.png", L"sparty-mouth.png", 1.5, 40, 86);
    game.AddLetter(&game, 2, 2, 50, 50, L"al.png", 10);
    game.AddTray(&game, 3, 3, 50, 50, L"tray.png", 5);

    ASSERT_FALSE(game.GetItems().empty());

    game.Clear();

    ASSERT_TRUE(game.GetItems().empty());
}
