// The Visitor design pattern.  See Visitor_Visitor_Class.cs for details.
//
// This module contains definitions of the element classes to be used in the
// Visitor example.


namespace DesignPatternExamples
{
    /// <summary>
    /// All visitors must implement this base class and then override one or
    /// more of the visit() methods, depending on which element type the
    /// visitor class is interested in.
    /// 
    /// For every new element class added, a new visit() method needs to be
    /// added to this base class and then all visitor classes must be rebuilt.
    /// There is no way around this as the Element and Visitor classes are
    /// closely intertwined at least at the interface level.
    /// </summary>
    public class ElementVisitor
    {
        /// <summary>
        /// Perform an operation on ElementDerivedOne types.
        /// </summary>
        /// <param name="element">The element to affect.</param>
        public virtual void visit(ElementDerivedOne element) { }

        /// <summary>
        /// Perform an operation on ElementDerivedTwo types.
        /// </summary>
        /// <param name="element">The element to affect.</param>
        public virtual void visit(ElementDerivedTwo element) { }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// The interface that all element classes must implement if they are
    /// to participate in the visitor pattern.
    /// </summary>
    public interface IElementVisitInterface
    {
        /// <summary>
        /// The visitor will call this method on each element it wants to
        /// visit.
        /// </summary>
        /// <param name="visitor">The visitor.</param>
        void accept(ElementVisitor visitor);
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Base class for all Element classes.  This base class provides a unique
    /// instance ID to each element and a property to get that ID.
    /// </summary>
    public class ElementBaseClass
    {
        /// <summary>
        /// The next Instance ID to assign.
        /// </summary>
        static int _nextInstanceId;

        /// <summary>
        /// The current ID for this instance.
        /// </summary>
        int _instanceId;

        /// <summary>
        /// Default Constructor.
        /// </summary>
        public ElementBaseClass()
        {
            _instanceId = _nextInstanceId;
            ++_nextInstanceId;
        }

        /// <summary>
        /// Retrieve the current ID for this instance.
        /// </summary>
        public int InstanceId
        {
            get
            {
                return _instanceId;
            }
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// One element with some specific properties (not needed here for the
    /// visitor demonstration).
    /// </summary>
    public class ElementDerivedOne : ElementBaseClass, IElementVisitInterface
    {
        /// <summary>
        /// The visitor indirectly calls this method (through polymorphism on
        /// inherited interface).
        /// </summary>
        /// <param name="visitor">The visitor.</param>
        void IElementVisitInterface.accept(ElementVisitor visitor)
        {
            visitor.visit(this);
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Second element with some specific properties (not needed here for the
    /// visitor demonstration).
    /// </summary>
    public class ElementDerivedTwo : ElementBaseClass, IElementVisitInterface
    {
        /// <summary>
        /// The visitor indirectly calls this method (through polymorphism on
        /// inherited interface).
        /// </summary>
        /// <param name="visitor">The visitor.</param>
        void IElementVisitInterface.accept(ElementVisitor visitor)
        {
            visitor.visit(this);
        }
    }
}
