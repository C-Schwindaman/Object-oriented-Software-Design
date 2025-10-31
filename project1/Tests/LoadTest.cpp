 /**
  * @file LoadTest.cpp
  * @author Caleb Blackwell, Meghan Carter
  */

 #include <pch.h>
 #include <fstream>
 #include <Game.h>
 #include <LevelLoader.h>
 #include "gtest/gtest.h"

 using namespace std;

 TEST(LoadTest, LoadLevelSize)
 {
     Game game;
     LevelLoader loader;

     std::string testFile = "levels/level2.xml";
     loader.XmlLoad(&game, testFile);

     ASSERT_EQ(game.GetLevelWidth(), 1440);
     ASSERT_EQ(game.GetLevelHeight(), 960);
 }

 TEST(LoadTest, LoadTileSize)
 {
     Game game;
     LevelLoader loader;

     std::string testFile = "levels/level1.xml";
     loader.XmlLoad(&game, testFile);

     ASSERT_EQ(game.GetTileWidth(), 48);
     ASSERT_EQ(game.GetTileHeight(), 48);
 }
