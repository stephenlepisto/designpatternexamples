#include "Visitor_Element_Classes.h"
#include "Visitor_Visitor_Class.h"

namespace DesignPatternExamples_cpp
{
    int ElementIdBaseClass::_nextInstanceId = 0;

    // Defined here instead of Visitor_Element_Classes.h to avoid a circular
    // dependency (ElementVisitor is defined in Visitor_Visitor_Class.h because
    // the visitors derive from it, however, the element classes need to know
    // the ElementVisitor class as well as shown here so the ElementVisitor
    // class has a forward declaration in Visitor_Element_Classes.h to satisfy
    // the class declarations in that header).
    void ElementDerivedOne::accept(ElementVisitor* visitor)
    {
        if (visitor != nullptr)
        {
            visitor->visit(this);
        }
    }

    // Defined here instead of Visitor_Element_Classes.h to avoid a circular
    // dependency (ElementVisitor is defined in Visitor_Visitor_Class.h because
    // the visitors derive from it, however, the element classes need to know
    // the ElementVisitor class as well as shown here so the ElementVisitor
    // class has a forward declaration in Visitor_Element_Classes.h to satisfy
    // the class declarations in that header).
    void ElementDerivedTwo::accept(ElementVisitor* visitor)
    {
        if (visitor != nullptr)
        {
            visitor->visit(this);
        }
    }

} // end namespace
