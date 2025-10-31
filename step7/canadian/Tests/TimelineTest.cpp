/**
 * @file TimelineTest.cpp
 * @author Cameron Schwindaman
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Timeline.h>
#include <AnimChannelAngle.h>

TEST(ActorTest, NumFrames)
{
    Timeline timeline;
    ASSERT_EQ(300, timeline.GetNumFrames());

    timeline.SetNumFrames(100);
    ASSERT_EQ(100, timeline.GetNumFrames());
}

TEST(ActorTest, FrameRate)
{
    Timeline timeline;
    ASSERT_EQ(30, timeline.GetFrameRate());

    timeline.SetFrameRate(10);
    ASSERT_EQ(10, timeline.GetFrameRate());
}

TEST(ActorTest, CurrentTime)
{
    Timeline timeline;
    ASSERT_NEAR(0, timeline.GetCurrentTime(), 0.00001);

    timeline.SetCurrentTime(1.23);
    ASSERT_NEAR(1.23, timeline.GetCurrentTime(), 0.00001);
}

TEST(TimelineTest, GetDuration)
{
    Timeline timeline;

    // Default value
    ASSERT_NEAR(10, timeline.GetDuration(), 0.0001);

    // Changed duration
    timeline.SetFrameRate(375);
    ASSERT_NEAR(300.0 / 375.0, timeline.GetDuration(), 0.0001);

    timeline.SetNumFrames(789);
    ASSERT_NEAR(789.0 / 375.0, timeline.GetDuration(), 0.0001);
}

TEST(TimelineTest, GetCurrentFrame)
{
    Timeline timeline;

    // Default value
    ASSERT_EQ(0, timeline.GetCurrentFrame());

    // Changed time
    timeline.SetCurrentTime(9.27);
    ASSERT_EQ(278, timeline.GetCurrentFrame());
}

TEST(TimelineTest, Add)
{
    Timeline timeline;
    AnimChannelAngle channel;

    timeline.AddChannel(&channel);
    ASSERT_EQ(&timeline, channel.GetTimeline());
}