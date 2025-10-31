/**
 * @file ItemTest.cpp
 * @author Serena Brown
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <Letter.h>
#include <Tray.h>
#include <Container.h>
#include <Player.h>

using namespace std;


TEST(ItemTest, TrayConstructor)
{
    Game game;
    Tray tray(&game, 1, 1, 50, 50, L"tray.png", 4, 32);

    ASSERT_EQ(tray.GetCapacity(), 4);
    ASSERT_EQ(tray.GetLetterCount(), 0);
}



TEST(ItemTest, LetterHitTest)
{
    Game game;
    Letter letter(&game, 2, 3, 50, 50, L"sd.png", 5);

    // Click inside the letter bounds
    ASSERT_TRUE(letter.HitTest(2 * 50 + 10, 3 * 50 + 10));

    // Click outside the letter bounds
    ASSERT_FALSE(letter.HitTest(2 * 50 - 10, 3 * 50 - 10));
}

TEST(ItemTest, LetterMovement)
{
    Game game;
    Letter letter(&game, 2, 3, 50, 50, L"sd.png", 5);

    letter.SetLocation(300, 400);
    letter.Update(0.5);

    ASSERT_NE(letter.GetX(), 2 * 50);
    ASSERT_NE(letter.GetY(), 3 * 50);
}


TEST(ItemTest, PlayerMovement)
{
    Game game;
    Player player(&game, 2, 3, 50, 50, L"sparty.png",48, L"sparty-mouth.png", 1.5, 40, 86);

    player.SetPlayerLocation(300, 400);
    player.Update(0.5);

    ASSERT_NE(player.GetX(), 2 * 50);
    ASSERT_NE(player.GetY(), 3 * 50);
}


TEST(ItemTest, TrayCapacity)
{
    Game game;
    Tray tray(&game, 1, 1, 50, 50, L"tray.png", 4, 32);
    auto letter1 = make_shared<Letter>(&game, 1, 1, 50, 50, L"sd.png", 5);
    auto letter2 = make_shared<Letter>(&game, 2, 2, 50, 50, L"ld.png", 10);

    ASSERT_TRUE(tray.AddLetter(letter1));
    ASSERT_TRUE(tray.AddLetter(letter2));
    ASSERT_EQ(tray.GetLetterCount(), 2);

    tray.RemoveLetter(letter1);
    ASSERT_EQ(tray.GetLetterCount(), 1);
}

