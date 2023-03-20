## @file
#  @brief
#  Declaration of the
#  @ref DesignPatternExamples_python.flyweight.flyweight_classes.Flyweight_Context "Flyweight_Context",
#  @ref DesignPatternExamples_python.flyweight.flyweight_classes.Flyweight_Class "Flyweight_Class",
#  @ref DesignPatternExamples_python.flyweight.flyweight_classes.BigResource "BigResource", and
#  @ref DesignPatternExamples_python.flyweight.flyweight_classes.BigResourceManager "BigResourceManager"
#  classes as used in the @ref flyweight_pattern.

## Represents the context for an instance of the
#  @ref DesignPatternExamples_python.flyweight.flyweight_classes.Flyweight_Class "Flyweight_Class".
#  In this case, the context includes position and velocity.
#  
#  This context is manipulated outside the Flyweight_Class by the
#  controlling entity (in this case, the exercise in program.cpp).  The
#  Flyweight_Class just holds onto the context.
class Flyweight_Context:

    ## Constructor
    #
    #  @param position_x
    #         X position of the top left corner of the big resource.
    #  @param position_y
    #         Y position of the top left corner of the big resource.
    #  @param velocity_x
    #         Initial X velocity.
    #  @param velocity_y
    #         Initial Y velocity.
    def __init__(self, position_x = 0.0, position_y = 0.0, velocity_x = 0.0, velocity_y = 0.0) -> None:
        self.Position_X = position_x
        self.Position_Y = position_y
        self.Velocity_X = velocity_x
        self.Velocity_Y = velocity_y

    ## @var Position_X
    #       X position of the top left corner of the big resource.
    #  @var Position_Y
    #       Y position of the top left corner of the big resource.
    #  @var Velocity_X
    #       X velocity as a float.
    #  @var Velocity_Y
    #       Y velocity, as a float.


#========================================================================
#========================================================================
#========================================================================

## Associates a context with a big resource.
class Flyweight_Class:

    ## @name Properties
    #  @{

    ## Property getter for the context for this class instance: `value = o.Context`
    @property
    def Context(self) -> Flyweight_Context:
        return self._context

    ## Property setter for th context for this class instance: `o.Context = value`
    @Context.setter
    def Context(self, context : Flyweight_Context) -> None:
        self._context = context


    ## Property getter for the "image" width from underlying big resource: `value = o.ImageWidth`
    @property
    def ImageWidth(self) -> int:
        if self._resource:
            return self._resource.ImageWidth
        return 0


    ## Property getter for the "image" height from underlying big resource: `value = o.ImageHeight`
    @property
    def ImageHeight(self) -> int:
        if self._resource:
            return self._resource.ImageHeight
        return 0
    
    ## @}

    ## Constructor
    #
    #  @param resource
    #         The resource being represented by this class.  This takes
    #         advantage of the fact that Python classes are always passed by
    #         reference so no actual copying of the resource is done.
    #  @param context
    #         A @ref DesignPatternExamples_python.flyweight.flyweight_classes.Flyweight_Context "Flyweight_Context"
    #         instance containing the context for this Flyweight_Class instance.
    def __init__(self, resource = None, context = Flyweight_Context()) -> None:
        self._resource = resource
        self._context = context

    ## @var _resource
    #       The big resource being referenced by this flyweight class.  In C#,
    #       a class is always a reference to an instance of the class so we
    #       take advantage of that here.  In other languages, this would be
    #       a pointer to the big resource or a handle from which a pointer
    #       could be obtained.
    #  @var _context
    #       The context associated with this class.  The calling entity uses
    #       this context to manipulate the flyweight class.


    ## Render the image associated with this flyweight instance into the given
    #  display at the given position.
    #
    #  Note that although this class has access to the context, it really
    #  shouldn't so as to keep a loose coupling between the context and
    #  this class.  Therefore, the entity calling Render() will pass the
    #  position in as parameters even though that position is likely
    #  coming from the context.
    #
    #  @param display
    #         A list of character arrays representing the display.
    #  @param position_x
    #         leftmost position within the display to place the upper left
    #         corner of the image,
    #  @param position_y
    #         topmost position within the display to place the upper left
    #         corner of the image.
    def Render(self, display : list[bytearray], position_x : int, position_y : int) -> None:
        if self._resource:
            self._resource.Render(display, position_x, position_y)


#========================================================================
#========================================================================
#========================================================================


## Represents some big resource.  In this case, a text "image" rendered
#  as a list of strings.  each entry in the list is the same width.
#  The height of the "image" is the number of entries in the list.
#  This image is provided by the user.
#   
#  The resource is represented by an ID.  This ID is known by the user
#  and is passed to the
#  @ref DesignPatternExamples_python.flyweight.flyweight_classes.Flyweight_Class "Flyweight_Class"
#  factory so the Flyweight_Class can get a reference to an instance of this
#  BigResource class.  Instances of this BigResource class are managed through
#  the @ref DesignPatternExamples_python.flyweight.flyweight_classes.BigResourceManager "BigResourceManager"
#  class.
class BigResource:

    ## @name Properties
    #  @{

    ## Property getter for the resource ID for this resource: `value = o.ResourceId`
    @property
    def ResourceId(self) -> int:
        return self._resourceId

    
    ## Property getter for the "image" width of the resource: `value = o.ImageWidth`
    @property
    def ImageWidth(self) -> int:
        if self._resource:
            return len(self._resource[0])
        return 0

    
    ## Property getter for the "image" height of the resource: `value = o.ImageHeight`
    @property
    def ImageHeight(self) -> int:
        if self._resource:
            return len(self._resource)
        return 0

    ## @}

    ## Constructor (accessibly only to the class factory).
    #
    #  @param resource
    #         The resource to manage.
    #  @param resourceId
    #         ID of the resource.
    def __init__(self, resource : list[bytearray], resourceId : int):
        self._resource = resource
        self._resourceId = resourceId

    ## @var _resource
    #       a list of `bytearray`s representing the image (big resource)
    #  @var _resourceId
    #       The unique ID for this resource


    ## Render the big resource into the given display at the given position.
    #
    #  @param display
    #         The display in which to render.
    #  @param position_x
    #         X position where to put upper left corner of resource.
    #  @param position_y
    #         Y position where to put upper left corner of resource.
    def Render(self, display : list[bytearray], position_x : int, position_y : int) -> None:
        display_width = len(display[0])
        display_height = len(display)
        starting_position_x = position_x
        starting_position_y = position_y

        # Size of image to render (can be smaller than actual image if image
        # lies partially of right or bottom of display).
        image_render_width = len(self._resource[0])
        image_render_height = len(self._resource)

        # Position into image to start rendering from (non-zero if
        # image is off the left or top edge of display).
        starting_row_in_image = 0
        starting_col_in_image = 0

        # Clip the image to the display.
        if starting_position_x < 0:
            starting_col_in_image = -starting_position_x
            image_render_width += starting_position_x
            starting_position_x = 0
        elif (starting_position_x + image_render_width) > display_width:
            image_render_width = display_width - starting_position_x

        if starting_position_y < 0:
            starting_row_in_image = -starting_position_y
            image_render_height += starting_position_y
            starting_position_y = 0
        elif (starting_position_y + image_render_height) > display_height:
            image_render_height = display_height - starting_position_y

        # If the image is even partially visible, render it
        if image_render_width > 0 and image_render_height > 0:
            current_display_row = starting_position_y
            current_image_row = starting_row_in_image
            for row in range(0, image_render_height):
                for col in range(0, image_render_width):
                    display[current_display_row][starting_position_x + col] = \
                        self._resource[current_image_row][starting_col_in_image + col]
                current_display_row += 1
                current_image_row += 1


    ## Generate a Flyweight instance that will represent this big resource
    #  in some context-dependent way.
    #
    #  @param context
    #         A
    #         @ref DesignPatternExamples_python.flyweight.flyweight_classes.Flyweight_Context "Flyweight_Context"
    #         instance containing the context for the desired Flyweight_Class instance.
    #  @returns
    #    A new instance of the
    #    @ref DesignPatternExamples_python.flyweight.flyweight_classes.Flyweight_Class "Flyweight_Class".
    def CreateFlyweight(self, context : Flyweight_Context) -> Flyweight_Class:
        return Flyweight_Class(self, context)


#========================================================================
#========================================================================
#========================================================================



## Represents a manager for big resources.  Also provides the class
#  factory for the
#  @ref DesignPatternExamples_python.flyweight.flyweight_classes.Flyweight_Class "Flyweight_Class"
#  instances that are associated with a
#  particular big resource.
#
#  Note: The raw resource is provided by the caller and an ID is then
#  associated with it.  The ID is returned to the caller who then passes
#  that ID to the
#  @ref DesignPatternExamples_python.flyweight.flyweight_classes.Flyweight_Class "Flyweight_Class"
#  factory along with a context.
#  
#  In the exercise, only one big resource is ever created so this class
#  is likely overkill for an example but it fully shows the architectural
#  context in which a flyweight class is utilized.
class BigResourceManager:
    ## A list of all big resources managed by this class.
    _resources = [] # type list[BigResource]

    ## The next ID to assign a raw resource for management.
    _nextResourceId = 0

    ## Retrieve the next resource ID that can be used.
    #
    #  @returns
    #     The next resource ID.
    def GetNextResourceId() -> int:
        nextId = BigResourceManager._nextResourceId
        ++BigResourceManager._nextResourceId
        return nextId


    ## Retrieve the BigResource corresponding to the specified ID.
    #
    #  @param resourceId
    #         ID of the big resource to find.
    #  @returns
    #     Returns a BigResource object corresponding to the specified ID.
    #     Returns None if there is no corresponding BigResource object.
    def FindResource(resourceId : int) -> BigResource:
        foundResource = None # type: BigResource
        
        for resource in BigResourceManager._resources:
            if resource.ResourceId == resourceId:
                foundResource = resource
                break

        return foundResource


    ## Add a new big resource and return the ID of the resource.
    #
    #  @param rawResource
    #         The resource to add.
    #  @returns
    #     Returns the ID of the new big resource added to the manager.
    def AddResource(rawResource : list[bytearray]) -> int:
        newResourceId = BigResourceManager.GetNextResourceId()
        BigResourceManager._resources.append(BigResource(rawResource, newResourceId))
        return newResourceId


    ## Create a new instance of the
    #  @ref DesignPatternExamples_python.flyweight.flyweight_classes.Flyweight_Class "Flyweight_Class"
    #  associated with the given big resource and a context, in this case an
    #  X,Y position.
    #
    #  @param bigResourceId
    #         ID of the big resource to associate with.
    #  @param context
    #         A
    #         @ref DesignPatternExamples_python.flyweight.flyweight_classes.Flyweight_Context "Flyweight_Context"
    #         instance containing the context for the desired Flyweight_Class instance.
    #  @returns
    #     A new instance of the Flyweight_Class.  Returns None if the big
    #     resource was not found.
    def CreateFlyweight(bigResourceId : int, context : Flyweight_Context) -> Flyweight_Class:
        flyweightClass = None
        bigResource = BigResourceManager.FindResource(bigResourceId)
        if bigResource:
            flyweightClass = bigResource.CreateFlyweight(context)
        return flyweightClass

