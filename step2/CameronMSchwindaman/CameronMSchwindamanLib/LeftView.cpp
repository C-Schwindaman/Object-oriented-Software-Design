/**
 * @file LeftView.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "LeftView.h"

/**
 * Initialize the left view class.
 * @param parent The parent window for this class
 */
void LeftView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY);
    SetBackgroundColour(wxColour(24, 69, 59)); // MSU Green
}