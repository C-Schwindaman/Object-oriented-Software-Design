/**
 * @file Component.cpp
 * @author Cameron Schwindaman
 */

#include "pch.h"
#include "Component.h"

/**
 * Draw the component
 * @param graphics Graphics object to render to
 */
void Component::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    DrawPolygon(graphics, mLocation.m_x, mLocation.m_y);
    if (mIsPolygon)
    {
        mPolygon->DrawPolygon(graphics, mLocation.m_x, mLocation.m_y);
    }
}

/**
 * Set the polygon of the component
 * @param polygon New polygon of the component
 */
void Component::SetPolygon(Polygon* polygon)
{
    mPolygon = polygon;
    mIsPolygon = true;
}