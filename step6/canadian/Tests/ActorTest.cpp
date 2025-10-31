/**
 * @file ActorTest.cpp
 * @author Cameron Schwindaman
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Actor.h>

TEST(ActorTest, Constructor)
{
    Actor actor(L"Harold");
    ASSERT_EQ(std::wstring(L"Harold"), actor.GetName());
}

TEST(ActorTest, Enabled)
{
    Actor actor(L"Harold");
    ASSERT_TRUE(actor.IsEnabled());

    actor.SetEnabled(false);
    ASSERT_FALSE(actor.IsEnabled());
}

TEST(ActorTest, Clickable)
{
    Actor actor(L"Harold");
    ASSERT_TRUE(actor.IsClickable());

    actor.SetClickable(false);
    ASSERT_FALSE(actor.IsClickable());
}

TEST(ActorTest, Position)
{
    Actor actor(L"Harold");
    ASSERT_EQ(actor.GetPosition(), wxPoint(0, 0));

    actor.SetPosition(wxPoint(123, 456));
    ASSERT_EQ(actor.GetPosition(), wxPoint(123, 456));
}