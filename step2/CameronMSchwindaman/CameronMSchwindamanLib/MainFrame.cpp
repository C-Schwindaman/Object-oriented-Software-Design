/**
 * @file MainFrame.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "MainFrame.h"
#include "LeftView.h"
#include "RightView.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Cameron M Schwindaman", wxDefaultPosition,  wxSize( 1000,800 ));

    // Create a sizer that will lay out child windows horizontally
    auto sizer = new wxBoxSizer( wxHORIZONTAL );

    // Create the left view class object and add it to the sizer
    auto leftView = new LeftView();
    leftView->Initialize(this);
    sizer->Add(leftView,1, wxEXPAND | wxALL );

    // Create the right view class object and add it to the sizer
    auto rightView = new RightView();
    rightView->Initialize(this);
    sizer->Add(rightView,3, wxEXPAND | wxALL);

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();
}