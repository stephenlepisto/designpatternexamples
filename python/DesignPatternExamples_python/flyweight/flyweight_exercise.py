## @file
# @brief
# Implementation of the
# @ref DesignPatternExamples_python.flyweight.flyweight_exercise.Flyweight_Exercise "Flyweight_Exercise"()
# function as used in the @ref flyweight_pattern.

from io import StringIO
import random

from .flyweight_helpers import Helpers
from .flyweight_classes import BigResourceManager, Flyweight_Class, Flyweight_Context

## Generate a big resource, in this case, a text "image" of the specified
#  width and height.  The image is a box.
#
#  @param width
#         Width of the "text" image, in characters.  Minimum width is 3.
#  @param height
#         Height of the "text" image, in characters.  Minimum height is 3.
#  @returns
#     An index to the generated index in the BigResourceManager.
def _Flyweight_GenerateBigResource(width : int, height : int) -> int:
    width = max(3, width)
    height = max(3, height)

    image = [] # type: list[bytearray]
    for row in range(0, height):
        image_row = None
        if row == 0 or ((row + 1) == height):
            # top and bottom row are the same.
            image_row = bytearray("+{0}+".format('-' * (width - 2)).encode())
        else:
            # All other rows are each the same.
            image_row = bytearray("|{0}|".format('0' * (width - 2)).encode())
        image.append(image_row)

    resourceId = BigResourceManager.AddResource(image)
    return resourceId


## Clear the "display" to a background image, erasing whatever was there before.
#
#  @param display
#         A list of `bytearray`s representing the display.
def _Flyweight_ClearDisplay(display : list[bytearray]) -> None:
    for row in display:
        for index in range(0, len(row)):
            row[index] = ord('~')


##  Generate a display area in which to render the big resource.
#
#  @param width
#         Width of the display area.
#  @param height
#         Height of the display area.
#  @returns
#     A List of character arrays representing the display area.
def _Flyweight_GenerateDisplay(width : int, height : int) -> list[bytearray]:
    display = []

    for row in range(0, height):
        display.append(bytearray((' ' * width).encode()))

    _Flyweight_ClearDisplay(display)
    return display


## Render the display to the screen.
#
#  @param display
#         A list of `bytearray`s representing the display.
def _Flyweight_ShowDisplay(display : list[bytearray]) -> None:
    #output = StringIO()
    for row in display:
        print("  ", end='')
        print(row.decode())


## Move the given flyweight instances within the display, bouncing them off
#  the edges of the display.
#  
#  The display size and image size are provided here
#
#  @param flyweightInstances
#         List of
#         @ref DesignPatternExamples_python.flyweight.flyweight_classes.Flyweight_Class "Flyweight_Class"
#         instances to move.
#  @param display_width
#         Width of display.
#  @param display_height
#         Height of display.
def _Flyweight_MoveFlyweights(flyweightInstances : list[Flyweight_Class], display_width : int, display_height : int) -> None:
    for flyweight in flyweightInstances:
        context = flyweight.Context()
        image_width = flyweight.ImageWidth()
        image_height = flyweight.ImageHeight()
        newx = context.Position_X + context.Velocity_X
        newy = context.Position_Y + context.Velocity_Y

        if newx < 0 or (newx + image_width) > display_width:
            # Bounce off left or right edge.
            context.Velocity_X = -context.Velocity_X
            if newx < 0:
                newx = 0
            else:
                newx = display_width - image_width

        if newy < 0 or (newy + image_height) > display_height:
            # Bounce off top or bottom edge.
            context.Velocity_Y = -context.Velocity_Y
            if newy < 0:
                newy = 0
            else:
                newy = display_height - image_height

        context.Position_X = newx
        context.Position_Y = newy
        flyweight.SetContext(context)


## Render the image into the display, once for each flyweight instance.
#
#  @param flyweightInstances
#         List of
#         @ref DesignPatternExamples_python.flyweight.flyweight_classes.Flyweight_Class "Flyweight_Class"
#         instances to render.
#  @param displayArea
#         The "display" in which to render.
def _Flyweight_RenderFlyweights(flyweightInstances : list[Flyweight_Class], displayArea : list[bytearray]) -> None:
    # Render the image into the "display", one image for each instance
    # of the Flyweight class.
    for flyweight in flyweightInstances:
        context = flyweight.Context()
        flyweight.Render(displayArea, int(context.Position_X), int(context.Position_Y))


## Generate a random velocity, which includes a speed and a direction.
#  The velocity is 0.2 to 1.0 (in increments of 0.2) and the direction
#  is either + or -.
#
#  @returns
#    Returns the velocity.
def GenerateVelocity() -> float:
    speed = ((random.random() * 5) + 1) / 5.0
    direction = 1.0 if ((random.random() * 100) > 50) else -1.0
    return speed * direction


## Helper method to generate the specified number of flyweight class
#  instances and associate those instances with individual contexts
#  and a single big resource.
#  
#  The image and display sizes are provided so as to randomize the
#  position of each flyweight within the display.
#
#  @param bigResourceId
#         ID of the big resource to use.
#  @param numFlyweights
#         Number of flyweight instances to create.
#  @param image_width
#         Width of the big resource image.
#  @param image_height
#         Height of the big resource image.
#  @param display_width
#         Width of the display in which the flyweight is to be rendered.
#  @param display_height
#         Height of the display in which the flyweight is to be rendered.
#  @returns
#     A list containing the requested number of Flyweight class instances, each
#     attached to the specified "big" resource.
def _Flyweight_GenerateFlyweightClasses(bigResourceId : int, numFlyweights : int,
    image_width : int, image_height : int, display_width : int, display_height : int) -> list[Flyweight_Class]:
    flyweightInstances = []

    # Generate the instances of the flyweight class, randomizing the position
    # of each flyweight within the display.
    for index in range(0, numFlyweights):
        context = Flyweight_Context()
        # Make sure the entire image can be rendered at each position
        context.Position_X = random.random() * (display_width - image_width)
        context.Position_Y = random.random() * (display_height - image_height)
        # Randomize the initial velocity.
        context.Velocity_X = GenerateVelocity()
        context.Velocity_Y = GenerateVelocity()

        # Create an instance of the Flyweight_Class for the given big
        # resource and with the new context.
        flyweightInstances.append(BigResourceManager.CreateFlyweight(bigResourceId, context))
    return flyweightInstances


##  Example of using the @ref flyweight_pattern.
#  
#  The Flyweight pattern is used when a large object needs to be
#  represented by a much lighter weight class, possibly multiple
#  instances of said light-weight class.
#  
#  In this example, a large object is represented by a so-called "big
#  resource" or image (a two-dimensional array of text characters).
#  Flyweight classes that represent position and velocity are
#  attached to the big resource image so they all share the same image
#  but have different positions and velocities.  The image is rendered
#  to a display area through the Flyweight class.  The Flyweight
#  class instances then have their positions updated, bouncing off the
#  edges of the display area 60 times a second.  This continues for
#  1000 iterations or until a key is pressed.

# ! [Using Flyweight in Python]
def Flyweight_Exercise():
    print()
    print("Flyweight Exercise")

    # Define the display and image size.
    DISPLAY_WIDTH = 80
    DISPLAY_HEIGHT = 20
    IMAGE_WIDTH = 30
    IMAGE_HEIGHT = 5
    NUMFLYWEIGHTS = 5
    NUM_ITERATIONS = 1000

    bigResourceId = _Flyweight_GenerateBigResource(IMAGE_WIDTH, IMAGE_HEIGHT)
    flyweightInstances = _Flyweight_GenerateFlyweightClasses(bigResourceId, NUMFLYWEIGHTS,
        IMAGE_WIDTH, IMAGE_HEIGHT, DISPLAY_WIDTH, DISPLAY_HEIGHT)

    # Create the "display".
    # We use a list of character arrays so we can write to each
    # character position individually.  In C#, strings are immutable
    # and changing a character in a string is not allowed.
    displayArea = _Flyweight_GenerateDisplay(DISPLAY_WIDTH, DISPLAY_HEIGHT)

    # Finally, display the rendered output.
    print("  The image rendered {0} times:".format(NUMFLYWEIGHTS))
    print() # Blank line for iteration count
    _Flyweight_RenderFlyweights(flyweightInstances, displayArea)
    _Flyweight_ShowDisplay(displayArea)

    helpers = Helpers()
    # Now let's have some fun and bounce those images around for a while!
    # (Or until a keypress.)
    cursorLeft, cursorTop = helpers.getcursorposition()
    if cursorLeft != -1 and cursorTop != -1:
        cursorTop -= DISPLAY_HEIGHT + 1

    for index in range(0, NUM_ITERATIONS):
        if cursorLeft != -1:
            helpers.setcursorposition(cursorTop - 1, cursorLeft)
        print("  {0:5}/{1} iterations [press a key to exit early]".format(index + 1, NUM_ITERATIONS))
        if cursorLeft != -1:
            helpers.setcursorposition(cursorTop, cursorLeft)

        _Flyweight_ClearDisplay(displayArea)
        _Flyweight_MoveFlyweights(flyweightInstances, DISPLAY_WIDTH, DISPLAY_HEIGHT)
        _Flyweight_RenderFlyweights(flyweightInstances, displayArea)
        _Flyweight_ShowDisplay(displayArea)
        helpers.sleep(16) # 60 frames a second
        if helpers.checkforkey():
            helpers.readkey()
            break

    print("  Done.")
# ! [Using Flyweight in Python]
