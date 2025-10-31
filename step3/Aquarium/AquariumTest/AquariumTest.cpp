/**
 * @file AquariumTest.cpp
 * @author Cameron Schwindaman
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Aquarium.h>
#include <FishBeta.h>

using namespace std;

TEST(AquariumTest, Construct){
    Aquarium aquarium;
}

TEST(AquariumTest, HitTest) {
    Aquarium aquarium;

    ASSERT_EQ(aquarium.HitTest(100, 200), nullptr) <<
        L"Testing empty aquarium";

    shared_ptr<FishBeta> fish1 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish1);
    fish1->SetLocation(100, 200);

    ASSERT_TRUE(aquarium.HitTest(100, 200) == fish1) <<
          L"Testing fish at 100, 200";

    ASSERT_TRUE(aquarium.HitTest(10, 200) == nullptr) <<
      L"Testing fish at 10, 200";

    ASSERT_TRUE(aquarium.HitTest(200, 200) == nullptr) <<
      L"Testing fish at 200, 200";

    ASSERT_TRUE(aquarium.HitTest(100, 0) == nullptr) <<
      L"Testing fish at 100, 0";

    ASSERT_TRUE(aquarium.HitTest(100, 300) == nullptr) <<
      L"Testing fish at 100, 300";

    ASSERT_TRUE(aquarium.HitTest(100 - 125/2 + 17, 200 - 117/2 + 16) == nullptr) <<
      L"Testing fish at transparent pixel";

    shared_ptr<FishBeta> fish2 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish2);
    fish2->SetLocation(100, 200);

    ASSERT_TRUE(aquarium.HitTest(100, 200) == fish2) <<
      L"Testing fish at 100, 200";
}

