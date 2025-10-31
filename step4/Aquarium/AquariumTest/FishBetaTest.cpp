/**
* @file FishBetaTest.cpp
 * @author Cameron Schwindaman
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <FishBeta.h>
#include <Aquarium.h>

TEST(FishBetaTest, Construct) {
    Aquarium aquarium;
    FishBeta item(&aquarium);
}