
/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::NullObject_Exercise "NullObject_Exercise"()
/// function as used in the @ref nullobject_pattern.

#include <iostream>

#include "helpers/formatstring.h"

#include "NullObject_Exercise.h"
#include "Null_Object.h"


namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Example of using the @ref nullobject_pattern "Null Object" design pattern.
    /// 
    /// The Null Object pattern is where an object or function acts as a
    /// stand-in for real commands but otherwise does nothing.
    /// 
    /// In this exercise, movement commands are presented as characters in
    /// a string, with the characters 'u', 'd', 'l', and 'r' representing
    /// the moves "up", "down", "left", and "right", respectively.  To
    /// keep the processing of this string simple, all other characters in
    /// the string are assigned a Null Object ("Do Nothing") version of
    /// the move command.
    /// 
    /// This example displays the commands after parsing and then
    /// "executes" commands, which consists of printing the commands out.
    /// 
    /// This example highlights the @ref nullobject_pattern while also
    /// utilizing the @ref command_pattern and @ref interpreter_pattern.
    /// </summary>
    // ! [Using NullObject in C++]
    void NullObject_Exercise()
    {
        std::cout << std::endl;
        std::cout << "NullObject Exercise" << std::endl;

        MoveProcessor moveProcessor;

        // A stream of recognized and unrecognized move commands.  The
        // unrecognized commands do nothing.
        std::string moveString = "ur#ld!lr";
        std::cout << "  Showing the move commands:" << std::endl;
        moveProcessor.ShowMoveList(moveString);

        std::cout << "  Executing the move commands:" << std::endl;
        std::cout << Helpers::formatstring("    %s -> ", moveString.c_str());
        moveProcessor.ExecuteMoveList(moveString);

        std::cout << "  Done." << std::endl;
    }
    // ! [Using NullObject in C++]

} // end namespace
