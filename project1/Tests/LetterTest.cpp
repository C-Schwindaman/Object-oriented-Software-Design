/**
 * @file LetterTest.cpp
 * @author Serena Brown
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Letter.h>
#include <Game.h>
#include <Visitor.h>

using namespace std;


TEST(LetterTest, Constructor)
{
    Game game;
    Letter letter(&game, 2, 3, 50, 50, L"sd.png", 5);

    ASSERT_EQ(letter.GetX(), 2 * 50);
    ASSERT_EQ(letter.GetY(), 3 * 50);
    ASSERT_EQ(letter.GetWidth(), 50);
    ASSERT_EQ(letter.GetHeight(), 50);
    ASSERT_EQ(letter.GetValue(), 5);
}


TEST(LetterTest, HitTest)
{
    Game game;
    Letter letter(&game, 2, 3, 50, 50, L"sd.png", 5);

    ASSERT_TRUE(letter.HitTest(2 * 50 + 10, 3 * 50 + 10));

    // Click outside
    ASSERT_FALSE(letter.HitTest(2 * 50 - 10, 3 * 50 - 10));
}


TEST(LetterTest, Movement)
{
    Game game;
    Letter letter(&game, 2, 3, 50, 50, L"sd.png", 5);

    letter.SetLocation(300, 400);
    letter.Update(0.5);

    ASSERT_NE(letter.GetX(), 2 * 50);
    ASSERT_NE(letter.GetY(), 3 * 50);
}

