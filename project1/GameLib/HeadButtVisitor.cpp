/**
 * @file HeadButtVisitor.cpp
 * @author Fatim
 */

#include "pch.h"
#include "HeadButtVisitor.h"
#include "Container.h"
/**
 *
 * @param container Pointer to the container being visited.
 */
void HeadButtVisitor::VisitContainer(Container* container)
{
    // Call the container's headbutt method
    bool success = container->Headbutt();

    // Update our flag if successful
    if (success)
    {
        mContainerHead = true;
    }
}
