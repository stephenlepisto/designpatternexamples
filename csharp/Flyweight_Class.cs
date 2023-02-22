// The flyweight pattern is used to represent some resource that can be shared
// multiple times.  The flyweight class contains just enough information to
// identify the resource and some context in which the instance of each
// flyweight class is used.  Instances of flyweight classes are always
// obtained through a class factory that is provided with the context
// information as a parameter.
//
// The intent is to represent the shared resource with a small, lightweight
// class instance that can be used many times without incurring large
// memory penalties that might occur if the shared resource was actually
// duplicated many times.
//
// An early form of flyweight class is a handle to a resource.  The handle
// was typically a 32-bit value and could be easily shared and passed around
// with minimal impact to the system.  The drawback is context information
// could not be easily attached to the handle.
//
// The contents of a flyweight class typically consists of a handle to the
// resource and some context information.  The context information is provided
// by the caller to the flyweight factory to be inserted into a new instance
// of the flyweight class.
//
// This example uses an image as the "big" resource.  The flyweight class
// represents a position for that image as the context.  The flyweight class
// also contains velocity information for moving the flyweight instance
// around a display.  Of course, everything is in text but it's the thought
// that counts.
//
// This module contains the following classes:
//  - Flyweight_Context
//    The context to be attached to the Flyweight_Class instance
//  - Flyweight_Class
//    The flyweight class example representing a BigResource
//  - BigResource
//    The big resource to be represented by a flyweight class
//  - BigResourceManager
//    A manager of big resources and the class factory for the
//    Flyweight_Class.
//
// See Program.cs, Flyweight_Exercise() for details on how to use these
// classes.

using System.Collections.Generic;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents the context for an instance of the Flyweight_Class.
    /// In this case, the context includes position and velocity.
    /// 
    /// This context is manipulated outside the Flyweight_Class by the
    /// controlling entity (in this case, the exercise in Program.cs).  The
    /// Flyweight_Class just holds onto the context.
    /// </summary>
    public struct Flyweight_Context
    {
        public int Position_X;
        public int Position_Y;
        public int Velocity_X;
        public int Velocity_Y;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="position_x">X position of the top left corner of the big resource.</param>
        /// <param name="position_y">Y position of the top left corner of the big resource.</param>
        /// <param name="velocity_x">Initial X velocity.</param>
        /// <param name="velocity_y">Initial Y velocity.</param>
        public Flyweight_Context(int position_x, int position_y, int velocity_x, int velocity_y)
        {
            Position_X = position_x;
            Position_Y = position_y;
            Velocity_X = velocity_x;
            Velocity_Y = velocity_y;
        }
    }



    //========================================================================
    //========================================================================
    //========================================================================



    /// <summary>
    /// Associates a context with a big resource.
    /// </summary>
    public class Flyweight_Class
    {
        /// <summary>
        /// The big resource being referenced by this flyweight class.  In C#,
        /// a class is always a reference to an instance of the class so we
        /// take advantage of that here.  In other languages, this would be
        /// a pointer to the big resource or a handle from which a pointer
        /// could be obtained.
        /// </summary>
        private BigResource _resource;

        /// <summary>
        /// The context associated with this class.  The calling entity
        /// uses this context to manipulate the flyweight class.
        /// </summary>
        private Flyweight_Context _context;


        /// <summary>
        /// Constructor (accessible only to the class factory).
        /// </summary>
        /// <param name="resource">The resource being represented by this class.  This
        /// takes advantage of the fact that C# classes are always passed by reference so
        /// no actual copying of the resource is done.</param>
        /// <param name="context">A Flyweight_Context instance containing the context for this
        /// Flyweight_Class instance.</param>
        internal Flyweight_Class(BigResource resource, Flyweight_Context context)
        {
            _resource = resource;
            _context = context;
        }


        /// <summary>
        /// Retrieve or set the context for this class instance.
        /// </summary>
        public Flyweight_Context Context
        {
            get
            {
                return _context;
            }
            set
            {
                _context = value;
            }
        }


        /// <summary>
        /// Retrieve the "image" width from underlying big resource.
        /// </summary>
        public int ImageWidth
        {
            get
            {
                if (_resource != null)
                {
                    return _resource.ImageWidth;
                }
                return 0;
            }
        }


        /// <summary>
        /// Retrieve the "image" height from underlying big resource.
        /// </summary>
        public int ImageHeight
        {
            get
            {
                if (_resource != null)
                {
                    return _resource.ImageHeight;
                }
                return 0;
            }
        }

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
        public void Render(List<char[]> display, int position_x, int position_y)
        {
            // Let the big resource handle the rendering at the given position.
            _resource.Render(display, position_x, position_y);
        }
    }



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
        List<string> _resource;
        int _resourceId;

        /// <summary>
        /// Constructor (accessibly only to the class factory).
        /// </summary>
        /// <param name="resource">The resource to manage.</param>
        /// <param name="resourceId">ID of the resource.</param>
        internal BigResource(List<string> resource, int resourceId)
        {
            _resource = resource;
            _resourceId = resourceId;
        }

        /// <summary>
        /// Render the big resource into the given display at the given position.
        /// </summary>
        /// <param name="display">The display in which to render.</param>
        /// <param name="position_x">X position where to put upper left corner of resource.</param>
        /// <param name="position_y">Y position where to put upper left corner of resource.</param>
        internal void Render(List<char[]> display, int position_x, int position_y)
        {
            int display_width = display[0].Length;
            int display_height = display.Count;
            int starting_position_x = position_x;
            int starting_position_y = position_y;

            // Size of image to render (can be smaller than actual image if image
            // lies partially of right or bottom of display).
            int image_render_width = _resource[0].Length;
            int image_render_height = _resource.Count;

            // Position into image to start rendering from (non-zero if
            // image is off the left or top edge of display).
            int starting_row_in_image = 0;
            int starting_col_in_image = 0;

            // Clip the image to the display.
            if (starting_position_x < 0)
            {
                starting_col_in_image = -starting_position_x;
                image_render_width += starting_position_x;
                starting_position_x = 0;
            }
            else if (starting_position_x + image_render_width > display_width)
            {
                image_render_width = display_width - starting_position_x;
            }
            if (starting_position_y < 0)
            {
                starting_row_in_image = - starting_position_y;
                image_render_height += starting_position_y;
                starting_position_y = 0;
            }
            else if (starting_position_y + image_render_height > display_height)
            {
                image_render_height = display_height - starting_position_y;
            }

            // If the image is even partially visible, render it
            if (image_render_width > 0 && image_render_height > 0)
            {
                int current_display_row = starting_position_y;
                int current_image_row = starting_row_in_image;
                for (int row = 0; row < image_render_height; ++row)
                {
                    for (int col = 0; col < image_render_width; ++col)
                    {
                        display[current_display_row][starting_position_x + col] = _resource[current_image_row][starting_col_in_image + col];
                    }
                    current_display_row += 1;
                    current_image_row += 1;
                }
            }
        }
        
        /// <summary>
        /// Retrieve the resource ID for this resource.
        /// </summary>
        public int ResourceId
        {
            get
            {
                return _resourceId;
            }
        }

        /// <summary>
        /// Retrieve the "image" width of the resource.
        /// </summary>
        public int ImageWidth
        {
            get
            {
                if (_resource != null && _resource.Count > 0)
                {
                    return _resource[0].Length;
                }
                return 0;
            }
        }

        /// <summary>
        /// Retrieve the "image" height of the resource.
        /// </summary>
        public int ImageHeight
        {
            get
            {
                if (_resource != null)
                {
                    return _resource.Count;
                }
                return 0;
            }
        }

        /// <summary>
        /// Generate a Flyweight class that will represent this big resource
        /// in some context-dependent way.
        /// </summary>
        /// <param name="context">A Flyweight_Context instance containing the context for the
        /// desired Flyweight_Class instance.</param>
        /// <returns>A new instance of the Flyweight_Class.</returns>
        public Flyweight_Class CreateFlyweight(Flyweight_Context context)
        {
            return new Flyweight_Class(this, context);
        }
    }



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
    public static class BigResourceManager
    {
        /// <summary>
        /// A list of all big resources managed by this class.
        /// </summary>
        static List<BigResource> _resources = new List<BigResource>();

        /// <summary>
        /// The next ID to assign a raw resource for management.
        /// </summary>
        static int _nextResourceId = 1;

        /// <summary>
        /// Retrieve the next resource ID that can be used.
        /// </summary>
        /// <returns>The next resource ID.</returns>
        static int GetNextResourceId()
        {
            int nextId = _nextResourceId;
            ++_nextResourceId;
            return nextId;
        }

        /// <summary>
        /// Add a new big resource and return the ID of the resource.
        /// </summary>
        /// <param name="rawResource">The resource to add.</param>
        /// <returns>Returns the ID of the new big resource added to the manager.</returns>
        public static int AddResource(List<string> rawResource)
        {
            int newResourceId = GetNextResourceId();
            BigResource addedResource = new BigResource(rawResource, newResourceId);
            _resources.Add(addedResource);

            return newResourceId;
        }

        /// <summary>
        /// Retrieve the BigResource corresponding to the specified ID.
        /// </summary>
        /// <param name="resourceId">ID of the big resource to find.</param>
        /// <returns>Returns a BigResource object corresponding to the specified ID.
        /// Returns null if there is no corresponding IBigResource object.</returns>
        internal static BigResource FindResource(int resourceId)
        {
            BigResource foundResource = null;
            foreach (BigResource resource in _resources)
            {
                if (resource.ResourceId == resourceId)
                {
                    foundResource = resource;
                    break;
                }
            }

            return foundResource;
        }

        /// <summary>
        /// Create a new instance of the Flyweight_Class associated with the
        /// given big resource and a context, in this case an X,Y position.
        /// </summary>
        /// <param name="bigResourceId">ID of the big resource to associate with.</param>
        /// <param name="context">A Flyweight_Context instance containing the context for the
        /// desired Flyweight_Class instance.</param>
        /// <returns>A new instance of the Flyweight_Class.  Returns null if the big resource
        /// was not found.</returns>
        public static Flyweight_Class CreateFlyweight(int bigResourceId, Flyweight_Context context)
        {
            Flyweight_Class flyweightClass = null;
            BigResource bigResource = FindResource(bigResourceId);
            if (bigResource != null)
            {
                flyweightClass = bigResource.CreateFlyweight(context);
            }
            return flyweightClass;
        }
    }
}
