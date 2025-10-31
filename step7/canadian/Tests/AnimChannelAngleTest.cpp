/**
 * @file AnimChannelAngleTest.cpp
 * @author Cameron Schwindaman
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <AnimChannelAngle.h>

TEST(AnimChannelAngleTest, Name)
{
    AnimChannelAngle animChannelAngle;
    animChannelAngle.SetName(L"Harold");
    ASSERT_EQ(L"Harold", animChannelAngle.GetName());
}