/**
 * @file Machine1Factory.cpp
 *
 * @author Anik Momtaz
 */

#include "pch.h"
#include "Machine1Factory.h"
#include "Machine.h"
#include "Shape.h"
#include "Motor.h"
#include "Pulley.h"
#include "BubbleBlower.h"

/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";

/**
 * Constructor
 * @param resourcesDir Path to the resources directory
 */
Machine1Factory::Machine1Factory(std::wstring resourcesDir) :
    mResourcesDir(resourcesDir)
{
    mImagesDir = mResourcesDir + ImagesDirectory;
}

/**
 * Factory method to create machine #1
 * @return
 */
std::shared_ptr<Machine> Machine1Factory::Create()
{
    // The machine itself
    auto machine = std::make_shared<Machine>(1);

    const int BackgroundWidth = 1200;
    const int BackgroundHeight = 800;

    const int BaseWidth = 360;  // Width of the base
    const int BaseHeight = 40;  // Height of the base

    const int PlatformWidth = 320;  // Width of the base
    const int PlatformHeight = 40;  // Height of the base

    const int MotorX = 0;	// Motor X location
    const int Post1X = -100;	// Post X location
    const int Post2X = 100;	// Second post X location

    int Post1Height = 260;
    int Post2Height = 160;
    int PostWidth = 20;

    const int MotorSize = 80;
    const int YOffset = -42;

    //
    // The base
    //
    auto base = std::make_shared<Shape>();

    base->Rectangle(int(-BaseWidth/2), 0, BaseWidth, BaseHeight);
    base->SetImage(mImagesDir + L"/base.png");
    machine->AddComponent(base);

    //
    // The platform
    //
    auto platform = std::make_shared<Shape>();

    platform->Rectangle(int(-PlatformWidth/2) + Post1X, -(Post1Height + int(PlatformHeight/2)), PlatformWidth, PlatformHeight);
    platform->SetImage(mImagesDir + L"/platform.png");
    machine->AddComponent(platform);

    //
    // The motor
    //
    auto motor =  std::make_shared<Motor>(mImagesDir);
    motor->SetPosition(MotorX, -38 + YOffset);
    motor->SetSpeed(1.0);
    machine->AddComponent(motor);

    //
    // The bubble blower
    //
    auto blower =  std::make_shared<BubbleBlower>(mImagesDir);
    blower->SetPosition(Post1X, -380);
    blower->SetRotation(-0.15);
    blower->SetRotation(0);
    machine->AddComponent(blower);

    //
    // Post to hold the first pulley
    // Must be added before the motor pulley so it draws behind the belt
    //
    auto post1 = CreatePost(Post1X, -BaseHeight, PostWidth, Post1Height);
    machine->AddComponent(post1);

    //
    // Post to hold the second pulley
    //
    auto post2 = CreatePost(Post2X, -BaseHeight, PostWidth, Post2Height);
    machine->AddComponent(post2);

    //
    // The pulley driven by the motor
    // Radius=15pixels
    //
    auto pulley1 = std::make_shared<Pulley>(15);
    pulley1->SetImage(mImagesDir + L"/pulley2.png");
    pulley1->SetPosition(MotorX, -38 - MotorSize / 2);
    pulley1->SetPhase(0.1);	// Rotate it a little bit
    machine->AddComponent(pulley1);

    // This is how I made a connection from a source to a sink
    // This is the case where they are driven at the same speed
    motor->GetSource()->AddSink(pulley1->GetSink());

    //
    // The pulley on the bubble blower platform. Driven by the motor pulley
    // Radius=40pixels
    //
    auto pulley2 = std::make_shared<Pulley>(40);
    pulley2->SetImage(mImagesDir + L"/pulley.png");
    pulley2->SetPosition(Post1X, post1->GetY() - Post1Height + 10);
    pulley2->SetPhase(0.1);	// Rotate it a little bit
    machine->AddComponent(pulley2);

    pulley2->GetSource()->AddSink(blower->GetSink());

    // This is how I made a connection from a pulley to another pulley using a belt
    pulley1->Drive(pulley2);

    //
    // Pulley directly driven by that pulley
    // Radius=15px
    //
    auto pulley3 = std::make_shared<Pulley>(15);
    pulley3->SetImage(mImagesDir + L"/pulley2.png");
    pulley3->SetPosition(pulley2);
    machine->AddComponent(pulley3);

    pulley2->GetSource()->AddSink(pulley3->GetSink());

    //
    // Pulley on the second post
    // Radius=40px
    //
    auto pulley4 = std::make_shared<Pulley>(40);
    pulley4->SetImage(mImagesDir + L"/pulley.png");
    pulley4->SetPosition(Post2X, post2->GetY() - Post2Height + 10);
    pulley4->SetPhase(0.1);	// Rotate it a little bit
    machine->AddComponent(pulley4);

    pulley3->Drive(pulley4);

    //
    // The flag
    //
    auto flag = std::make_shared<Shape>();
    flag->AddPoint(-50, 0);
    flag->AddPoint(-50, -100);
    flag->AddPoint(5, -100);
    flag->AddPoint(5, 0);
    flag->SetImage(mImagesDir + L"/flag.png");
    flag->SetPosition(pulley4);
    machine->AddComponent(flag);

    pulley4->GetSource()->AddSink(flag->GetSink());

    //
    // Pulley directly driven by that pulley
    // Radius=15px
    //
    auto pulley5 = std::make_shared<Pulley>(15);
    pulley5->SetImage(mImagesDir + L"/pulley2.png");
    pulley5->SetPosition(pulley4);
    machine->AddComponent(pulley5);

    pulley4->GetSource()->AddSink(pulley5->GetSink());

    return machine;
}

/**
 * Create a shape to use as a post to hold pulleys or platforms.
 *
 * @param x X position of bottom center of post in pixels
 * @param y Y position of bottom of post in pixels
 * @param wid Post width in pixels
 * @param hit Post height in pixels
 * @return Shape object
 */
std::shared_ptr<Shape> Machine1Factory::CreatePost(int x, int y, int wid, int hit)
{
    auto post = std::make_shared<Shape>();
    post->Rectangle(-wid/2, 0, wid, hit);
    post->SetImage(mImagesDir + L"/post.png");
    post->SetPosition(x, y);

    return post;
}