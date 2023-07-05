/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::Command_TextObject "Command_TextObject"
/// and @ref DesignPatternExamples_cpp::Command "Command" classes used in the
/// @ref command_pattern.

#pragma once
#ifndef __COMMAND_CLASSES_H__
#define __COMMAND_CLASSES_H__

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20


#include <memory>
#include <string>


namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Container for a string.  Need to use a class that allows the text to
    /// be changed while the container (this class) remains constant.  This
    /// way, operations can be applied to the text and the container's contents
    /// change but not the container (strings are immutable in C#; this dances
    /// around that problem).
    /// </summary>
    class Command_TextObject
    {
    public:
        using shared_ptr_t = std::shared_ptr<Command_TextObject>;

    private:
        // Starting string text so we can reset the text to a known point.
        std::string _startingText;

        // The text that can change.
        std::string _text;

    public:
        /// <summary>
        /// Constructs a text object with an initial string.
        /// </summary>
        /// <param name="text">The initial string for the text object.</param>
        Command_TextObject(std::string text)
        {
            _text = text;
            _startingText = text;
        }

        /// <summary>
        /// Gets the text in this TextObject.
        /// </summary>
        std::string Text() { return _text; }
        /// <summary>
        /// Sets the text in this TextObject.
        /// </summary>
        void SetText(std::string value) { _text = value; }

        /// <summary>
        /// Resets the TextObject to the starting string.
        /// </summary>
        void Reset()
        {
            _text = _startingText;
        }

        /// <summary>
        /// Converts the TextObject to a string.
        /// </summary>
        /// <returns>Returns the text stored in the text object.</returns>
        std::string ToString()
        {
            return _text;
        }
    };


    /// <summary>
    /// Alias for a function type representing an operation applied to a
    /// TextObject using two parameters.
    /// </summary>
    /// <param name="source">TextObject to affect</param>
    /// <param name="argument1">First argument for the operation.</param>
    /// <param name="argument2">Second argument for the operation.</param>
    using two_parameter_operation = void (*)(Command_TextObject::shared_ptr_t source, std::string argument1, std::string argument2);

    /// <summary>
    /// Alias for a function type representing an operation applied to a
    /// TextObject that uses no additional arguments.
    /// </summary>
    /// <param name="source">TextObject to affect</param>
    using no_parameter_operation = void (*)(Command_TextObject::shared_ptr_t source);


    /// <summary>
    /// Represents an operation that can be applied to a TextObject.
    /// This class can handle two kinds of operations, one that takes no
    /// additional parameters and one that takes two additional string
    /// parameters.
    /// </summary>
    /// <remarks>
    /// In a real program, the commands would be represented by an interface
    /// and concrete classes for each type of operation (based on additional
    /// parameters) would be used.  This requires the calling entity to
    /// instantiate the appropriate concrete class as opposed to letting the
    /// C# compiler figure out the correct constructor based on parameters.
    /// Or the calling entity could use a class factory to create the concrete
    /// classes.
    /// 
    /// It is also conceivable to make this Command class general case in
    /// terms of passing in 0 or more arguments along with a delegate that
    /// takes 0 or more arguments.  This complicates the actual calling of the
    /// delegate and obscures some of the functionality here but it would
    /// reduce the API to a single constructor and delegate.  But then it's up
    /// to the user to get the right number of parameters into the command for
    /// the delegate.
    /// </remarks>
    class Command
    {
    private:
        // The receiver of the command.
        Command_TextObject::shared_ptr_t _receiver;

        // Easy-to-read command name.
        std::string _commandName;

        // Two parameter operation to apply to the receiver.
        two_parameter_operation _two_parameter_operation;

        // No parameter operation to apply to the receiver.
        no_parameter_operation _no_parameter_operation;

        // The first argument to the operation.
        std::string _argument1;

        // The second argument to the operation.
        std::string _argument2;

    public:
        /// <summary>
        /// Constructor for a command that applies an operation to a TextObject, where the
        /// operation takes two parameters.
        /// </summary>
        /// <param name="source">The TextObject to apply the operation to.</param>
        /// <param name="commandName">Easy-to-read name of the command.</param>
        /// <param name="operation">The operation to apply to the TextObject.</param>
        /// <param name="argument1">First argument to the operation (after the TextObject).</param>
        /// <param name="argument2">Second argument to the operation (after the TextObject).</param>
        Command(Command_TextObject::shared_ptr_t source, const std::string& commandName, two_parameter_operation operation, const std::string& argument1, const std::string& argument2)
        {
            _receiver = source;
            _commandName = commandName;
            _two_parameter_operation = operation;
            _argument1 = argument1;
            _argument2 = argument2;
        }

        /// <summary>
        /// Constructor for a command that applies an operation to a TextObject but does
        /// not take any additional parameters.
        /// </summary>
        /// <param name="source">The TextObject to apply the operation to.</param>
        /// <param name="commandName">Easy-to-read name of the command.</param>
        /// <param name="operation">The operation to apply to the TextObject.</param>
        Command(Command_TextObject::shared_ptr_t source, const std::string& commandName, no_parameter_operation operation)
        {
            _receiver = source;
            _commandName = commandName;
            _no_parameter_operation = operation;
        }

        /// <summary>
        /// Execute the command on the TextObject.
        /// </summary>
        void Execute()
        {
            if (_two_parameter_operation != nullptr)
            {
                _two_parameter_operation(_receiver, _argument1, _argument2);
            }
            else // if (_no_parameter_operation != nullptr)
            {
                _no_parameter_operation(_receiver);
            }
        }

        /// <summary>
        /// Convert this command to a string representation.
        /// </summary>
        /// <returns>A string containing the representation of the command.</returns>
        std::string ToString()
        {
            std::string output = "<NO COMMAND>";
            if (_two_parameter_operation != nullptr)
            {
                output = std::format("{0} \"{1}\" with \"{2}\"", _commandName, _argument1, _argument2);
            }
            else if (_no_parameter_operation != nullptr)
            {
                output = std::format("{0}", _commandName);
            }
            return output;
        }
    };

} // end namespace

#endif // __COMMAND_CLASSES_H__

