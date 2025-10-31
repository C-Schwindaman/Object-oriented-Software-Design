/**
 * @file VisitorTest.cpp
 * @author Serena Brown
 */

#include <pch.h>
#include "gtest/gtest.h"

#include <Game.h>
#include <Letter.h>
#include <Player.h>
#include <Tray.h>
#include <Container.h>
#include <Visitor.h>


using namespace std;


class TestVisitor : public Visitor
{
public:
    void VisitContainer(Container* build) override { mNumContainers++; };
    void VisitTray(Tray* build) override { mNumTrays++; };
    void VisitPlayer(Player* build) override { mNumPlayers++; };
    void VisitLetter(std::shared_ptr<Letter> build) override { mNumLetters++; }
    int mNumContainers = 0;
    int mNumTrays = 0;
    int mNumLetters = 0;
    int mNumPlayers = 0;
};

TEST(TestVisitor, EmptyVisitor)
{
    Game game;

    TestVisitor emptyVisitor;
    game.Accept(&emptyVisitor);
    ASSERT_EQ(0, emptyVisitor.mNumContainers) ;
    ASSERT_EQ(0, emptyVisitor.mNumLetters) ;
    ASSERT_EQ(0, emptyVisitor.mNumTrays) ;
    ASSERT_EQ(0, emptyVisitor.mNumPlayers) ;

}

TEST(TestVisitor, TestVisitorCountsObjects)
{
    Game game;

//    auto container = make_shared<Container>(&game, L"present.png", L"present-front.png");
    auto tray = make_shared<Tray>(&game, 1, 1, 50, 50, L"tray.png", 4, 32);
    auto letter = make_shared<Letter>(&game, 1, 1, 50, 50, L"sd.png", 5);
    auto player = make_shared<Player>(&game, 2, 2, 50, 50, L"chest.png", 48, L"chest-lid.png", 0.8, 30, 86);

    TestVisitor visitor;

//    container->Accept(&visitor);
    tray->Accept(&visitor);
    letter->Accept(&visitor);
    player->Accept(&visitor);

    ASSERT_EQ(visitor.mNumContainers, 0);
    ASSERT_EQ(visitor.mNumTrays, 1);
    ASSERT_EQ(visitor.mNumLetters, 1);
    ASSERT_EQ(visitor.mNumPlayers, 1);
}


TEST(TestVisitor, TestVisitorWithMultipleObjects)
{
    Game game;

//    auto container1 = make_shared<Container>(&game, L"present.png", L"present-front.png");
//    auto container2 = make_shared<Container>(&game, L"present.png", L"present-front.png");
    auto tray1 = make_shared<Tray>(&game, 1, 1, 50, 50, L"tray.png", 4, 32);
    auto tray2 = make_shared<Tray>(&game, 2, 2, 50, 50, L"tray.png", 4, 32);
    auto letter1 = make_shared<Letter>(&game, 1, 1, 50, 50, L"sd.png", 5);
    auto letter2 = make_shared<Letter>(&game, 2, 2, 50, 50, L"sd.png", 10);
    auto player1 = make_shared<Player>(&game, 2, 2, 50, 50, L"chest.png", 48, L"chest-lid.png", 0.8, 30, 86);
    auto player2 = make_shared<Player>(&game, 2, 2, 50, 50, L"chest.png", 48, L"chest-lid.png", 0.8, 30, 86);

    TestVisitor visitor;

//    container1->Accept(&visitor);
//    container2->Accept(&visitor);
    tray1->Accept(&visitor);
    tray2->Accept(&visitor);
    letter1->Accept(&visitor);
    letter2->Accept(&visitor);
    player1->Accept(&visitor);
    player2->Accept(&visitor);

    ASSERT_EQ(visitor.mNumContainers, 0);
    ASSERT_EQ(visitor.mNumTrays, 2);
    ASSERT_EQ(visitor.mNumLetters, 2);
    ASSERT_EQ(visitor.mNumPlayers, 2);
}


TEST(TestVisitor, TestVisitorHandlesNoObjects)
{
    TestVisitor visitor;

    ASSERT_EQ(visitor.mNumContainers, 0);
    ASSERT_EQ(visitor.mNumTrays, 0);
    ASSERT_EQ(visitor.mNumLetters, 0);
    ASSERT_EQ(visitor.mNumPlayers, 0);
}


TEST(TestVisitor, TestVisitorOnSingleObjectType)
{
    Game game;

    auto letter1 = make_shared<Letter>(&game, 1, 1, 50, 50, L"id.png", 5);
    auto letter2 = make_shared<Letter>(&game, 2, 2, 50, 50, L"id.png", 10);
    auto letter3 = make_shared<Letter>(&game, 3, 3, 50, 50, L"id.png", 15);

    TestVisitor visitor;

    letter1->Accept(&visitor);
    letter2->Accept(&visitor);
    letter3->Accept(&visitor);

    ASSERT_EQ(visitor.mNumLetters, 3);
    ASSERT_EQ(visitor.mNumContainers, 0);
    ASSERT_EQ(visitor.mNumTrays, 0);
    ASSERT_EQ(visitor.mNumPlayers, 0);
}