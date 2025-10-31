/**
 * @file HeadButtVisitor.h
 * @author Fatim
 *
 *
 */
 
#ifndef HEADBUTTVISITOR_H
#define HEADBUTTVISITOR_H

#include "Visitor.h"
#include "Container.h"
/**
 * HeadButtVisitor class.
 *
 */
class HeadButtVisitor : public Visitor{
private:
    /// Is container's headbutt active?
    bool mContainerHead= false;
public:
    HeadButtVisitor() {}
    /**
     * @param container Pointer to the container being visited.
     */
    void VisitContainer(Container* container) override;
    /**
     * @return True if headbutt succeeded
     */
    bool WasContainerHeadbutted() const { return mContainerHead; }

};



#endif //HEADBUTTVISITOR_H
