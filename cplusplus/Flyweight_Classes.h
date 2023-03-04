/// @file
/// @brief
/// Declaration of the @ref DesignPatternExamples_cpp::Flyweight_Context "Flyweight_Context" struct,
/// and the @ref DesignPatternExamples_cpp::Flyweight_Class "Flyweight_Class",
/// @ref DesignPatternExamples_cpp::BigResource "BigResource", and
/// @ref DesignPatternExamples_cpp::BigResourceManager "BigResourceManager"
/// classes used in the @ref flyweight_pattern "Flyweight pattern".

#pragma once
#ifndef __FLYWEIGHT_CLASSES_H__
#define __FLYWEIGHT_CLASSES_H__

#include <memory>
#include <string>
#include <vector>

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Represents the context for an instance of the Flyweight_Class.
    /// In this case, the context includes position and velocity.
    /// 
    /// This context is manipulated outside the Flyweight_Class by the
    /// controlling entity (in this case, the exercise in program.cpp).  The
    /// Flyweight_Class just holds onto the context.
    /// </summary>
    struct Flyweight_Context
    {
        double Position_X;
        double Position_Y;
        double Velocity_X;
        double Velocity_Y;

        /// <summary>
        /// Default constructor
        /// </summary>
        Flyweight_Context()
            : Position_X(0.0)
            , Position_Y(0.0)
            , Velocity_X(0.0)
            , Velocity_Y(0.0)
        {
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="position_x">X position of the top left corner of the big resource.</param>
        /// <param name="position_y">Y position of the top left corner of the big resource.</param>
        /// <param name="velocity_x">Initial X velocity.</param>
        /// <param name="velocity_y">Initial Y velocity.</param>
        Flyweight_Context(double position_x, double position_y, double velocity_x, double velocity_y)
        {
            Position_X = position_x;
            Position_Y = position_y;
            Velocity_X = velocity_x;
            Velocity_Y = velocity_y;
        }
    };



    //========================================================================
    //========================================================================
    //========================================================================

    class BigResource; // forward reference

    /// <summary>
    /// Associates a context with a big resource.
    /// </summary>
    class Flyweight_Class
    {
    public:
        using unique_ptr_t = std::unique_ptr<Flyweight_Class>;

    private:
        /// <summary>
        /// The big resource being referenced by this flyweight class.  In C#,
        /// a class is always a reference to an instance of the class so we
        /// take advantage of that here.  In other languages, this would be
        /// a pointer to the big resource or a handle from which a pointer
        /// could be obtained.
        /// </summary>
        BigResource* _resource;

        /// <summary>
        /// The context associated with this class.  The calling entity
        /// uses this context to manipulate the flyweight class.
        /// </summary>
        Flyweight_Context _context;

    public:
        /// <summary>
        /// Default constructor
        /// </summary>
        Flyweight_Class()
            : _resource(nullptr)
        {
        }

        /// <summary>
        /// Constructor (accessible only to the class factory).
        /// </summary>
        /// <param name="resource">The resource being represented by this class.  This
        /// takes advantage of the fact that C# classes are always passed by reference so
        /// no actual copying of the resource is done.</param>
        /// <param name="context">A Flyweight_Context instance containing the context for this
        /// Flyweight_Class instance.</param>
        Flyweight_Class(BigResource* resource, Flyweight_Context context);

        /// <summary>
        /// Destructor
        /// </summary>
        ~Flyweight_Class();

        /// <summary>
        /// Retrieve the context for this class instance.
        /// </summary>
        Flyweight_Context Context();


        /// <summary>
        /// Set the context for this class instance.
        /// </summary>
        void SetContext(Flyweight_Context context);


        /// <summary>
        /// Retrieve the "image" width from underlying big resource.
        /// </summary>
        int ImageWidth();


        /// <summary>
        /// Retrieve the "image" height from underlying big resource.
        /// </summary>
        int ImageHeight();

        /// <summary>
        /// Render the image associated with this flyweight instance into the given
        /// display at the given position.
        /// </summary>
        /// <param name="display">A list of character arrays representing the display.</param>
        /// <param name="position_x">leftmost position within the display to place
        /// the upper left corner of the image,</param>
        /// <param name="position_y">topmost position within the display to place
        /// the upper left corner of the image.</param>
        /// <remarks>
        /// Note that although this class has access to the context, it really
        /// shouldn't so as to keep a loose coupling between the context and
        /// this class.  Therefore, the entity calling Render() will pass the
        /// position in as parameters even though that position is likely
        /// coming from the context.
        /// </remarks>
        void Render(std::vector<std::vector<char>>& display, int position_x, int position_y);
    };

    using FlyweightClassList = std::vector<Flyweight_Class::unique_ptr_t>;


    //========================================================================
    //========================================================================
    //========================================================================



    /// <summary>
    /// Represents some big resource.  In this case, a text "image" rendered
    /// as a list of strings.  each entry in the list is the same width.
    /// The height of the "image" is the number of entries in the list.
    /// This image is provided by the user.
    ///  
    /// The resource is represented by an ID.  This ID is known by the user
    /// and is passed to the Flyweight_Class factory so the Flyweight_Class
    /// can get a reference to an instance of this BigResource class.
    /// Instances of this BigResource class are managed through the
    /// BigResourceManager class.
    /// </summary>
    class BigResource
    {
    public:
        using unique_ptr_t = std::unique_ptr<BigResource>;

    private:
        std::vector<std::string> _resource;
        int _resourceId;

    public:
        /// <summary>
        /// Constructor (accessibly only to the class factory).
        /// </summary>
        /// <param name="resource">The resource to manage.</param>
        /// <param name="resourceId">ID of the resource.</param>
        BigResource(std::vector<std::string> resource, int resourceId)
        {
            _resource = resource;
            _resourceId = resourceId;
        }

        ~BigResource() { }


        /// <summary>
        /// Render the big resource into the given display at the given position.
        /// </summary>
        /// <param name="display">The display in which to render.</param>
        /// <param name="position_x">X position where to put upper left corner of resource.</param>
        /// <param name="position_y">Y position where to put upper left corner of resource.</param>
        void Render(std::vector<std::vector<char>>& display, int position_x, int position_y);

        /// <summary>
        /// Retrieve the resource ID for this resource.
        /// </summary>
        int ResourceId();

        /// <summary>
        /// Retrieve the "image" width of the resource.
        /// </summary>
        int ImageWidth();

        /// <summary>
        /// Retrieve the "image" height of the resource.
        /// </summary>
        int ImageHeight();

        /// <summary>
        /// Generate a Flyweight class that will represent this big resource
        /// in some context-dependent way.
        /// </summary>
        /// <param name="context">A Flyweight_Context instance containing the context for the
        /// desired Flyweight_Class instance.</param>
        /// <returns>A new instance of the Flyweight_Class.</returns>
        Flyweight_Class::unique_ptr_t CreateFlyweight(Flyweight_Context context);
    };



    //========================================================================
    //========================================================================
    //========================================================================



    /// <summary>
    /// Represents a manager for big resources.  Also provides the class
    /// factory for the Flyweight_Class instances that are associated with a
    /// particular big resource.
    /// </summary>
    /// <remarks>
    /// Note: The raw resource is provided by the caller and an ID is then
    /// associated with it.  The ID is returned to the caller who then passes
    /// that ID to the Flyweight_Class factory along with a context.
    /// 
    /// In the exercise, only one big resource is ever created so this class
    /// is likely overkill for an example but it fully shows the architectural
    /// context in which a flyweight class is utilized.
    /// </remarks>
    class BigResourceManager
    {
    private:
        using BigResourceList = std::vector<std::unique_ptr<BigResource>>;

        /// <summary>
        /// A list of all big resources managed by this class.
        /// </summary>
        static BigResourceList _resources;

        /// <summary>
        /// The next ID to assign a raw resource for management.
        /// </summary>
        static int _nextResourceId;

        /// <summary>
        /// Retrieve the next resource ID that can be used.
        /// </summary>
        /// <returns>The next resource ID.</returns>
        static int GetNextResourceId();

        /// <summary>
        /// Retrieve the BigResource corresponding to the specified ID.
        /// </summary>
        /// <param name="resourceId">ID of the big resource to find.</param>
        /// <returns>Returns a BigResource object corresponding to the specified ID.
        /// Returns null if there is no corresponding IBigResource object.</returns>
        static BigResource* FindResource(int resourceId);

    public:
        /// <summary>
        /// Add a new big resource and return the ID of the resource.
        /// </summary>
        /// <param name="rawResource">The resource to add.</param>
        /// <returns>Returns the ID of the new big resource added to the manager.</returns>
        static int AddResource(std::vector<std::string> rawResource);

        /// <summary>
        /// Create a new instance of the Flyweight_Class associated with the
        /// given big resource and a context, in this case an X,Y position.
        /// </summary>
        /// <param name="bigResourceId">ID of the big resource to associate with.</param>
        /// <param name="context">A Flyweight_Context instance containing the context for the
        /// desired Flyweight_Class instance.</param>
        /// <returns>A new instance of the Flyweight_Class.  Returns null if the big resource
        /// was not found.</returns>
        static Flyweight_Class::unique_ptr_t CreateFlyweight(int bigResourceId, Flyweight_Context context);
    };

} // end namespace

#endif // __FLYWEIGHT_CLASSES_H__

