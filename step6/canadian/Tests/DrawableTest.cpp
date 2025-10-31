/**
 * @file DrawableTest.cpp
 * @author Cameron Schwindaman
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Drawable.h>

class DrawableMock : public Drawable
{
    public:
    DrawableMock(const std::wstring &name) : Drawable(name) {}

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override {}
    bool HitTest(wxPoint pos) override { return false; }
};

TEST(DrawableTest, Constructor)
{
    DrawableMock drawable(L"Harold");
    ASSERT_EQ(std::wstring(L"Harold"), drawable.GetName());
}

TEST(DrawableTest, Position)
{
    DrawableMock drawable(L"Harold");
    ASSERT_EQ(drawable.GetPosition(), wxPoint(0, 0));

    drawable.SetPosition(wxPoint(123, 456));
    ASSERT_EQ(drawable.GetPosition(), wxPoint(123, 456));
}

TEST(DrawableTest, Rotation)
{
    DrawableMock drawable(L"Harold");
    ASSERT_NEAR(drawable.GetRotation(), 0, 0.000000001);

    drawable.SetRotation(123.456);
    ASSERT_NEAR(drawable.GetRotation(), 123.456, 0.000000001);
}

TEST(DrawableTest, Association)
{
    DrawableMock body(L"Body");
    auto arm = std::make_shared<DrawableMock>(L"Arm");
    auto leg = std::make_shared<DrawableMock>(L"Leg");

    ASSERT_EQ(nullptr, arm->GetParent());
    ASSERT_EQ(nullptr, leg->GetParent());

    body.AddChild(arm);
    body.AddChild(leg);

    ASSERT_EQ(&body, arm->GetParent());
    ASSERT_EQ(&body, leg->GetParent());
}