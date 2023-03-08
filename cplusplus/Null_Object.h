/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_csharp.MoveProcessor "MoveProcessor" class
/// and the various MoveXX classes used in the
/// @ref nullobject_pattern "Null Object pattern".

#pragma once
#ifndef __NULL_OBJECT_H__
#define __NULL_OBJECT_H__

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <iostream>
#include <memory>
#include <string>
#include <vector>


namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Base class that represents a move command.  A move command has a name
    /// and the command character that represents the command in the initial
    /// string of movement commands.
    /// 
    /// Yes, this is a variation of the Command pattern.
    /// 
    /// In this example, a move command, when executed, prints "move xxx" on
    /// the current line.  When displayed, the move command shows the command
    /// character followed by the name of the command.
    /// </summary>
    class MoveCommand
    {
    public:
        /// <summary>
        /// Alias to make it easier to work with a shared pointer.
        /// </summary>
        using shared_ptr_t = std::shared_ptr<MoveCommand>;

    private:
        /// <summary>
        /// Name of the command.
        /// </summary>
        std::string _name;

        /// <summary>
        /// The command for controlling movement.
        /// </summary>
        std::string _command;

    public:
        /// <summary>
        /// Virtual destructor required for interfaces/base classes
        /// </summary>
        virtual ~MoveCommand() { }

        /// <summary>
        /// Name of the command (assigned in the class constructor).
        /// </summary>
        std::string Name()
        {
            return _name;
        }

        /// <summary>
        /// The command character from the original list of commands.
        /// Used when displaying the commands as opposed to when executing
        /// the commands (assigned in the class constructor).
        /// </summary>
        std::string Command()
        {
            return _command;
        }


        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="command">The character that represents the command in the original move list.</param>
        /// <param name="commandName">The name of the command (for display purposes).</param>
        MoveCommand(std::string command, std::string commandName)
            : _name(commandName)
            , _command(command)
        {
        }


        /// <summary>
        /// Display the move command and its name followed by a newline.
        /// </summary>
        virtual void Show()
        {
            std::cout
                << std::format("    '{0}' -> {1}", _command, _name)
                << std::endl;
        }


        /// <summary>
        /// Execute the command.  Derived classes must implement this.
        /// </summary>
        virtual void Execute() = 0;
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the Move Left command.
    /// </summary>
    class MoveCommandLeft : public MoveCommand
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="command">The character representing the move in the
        /// original move list.</param>
        MoveCommandLeft(std::string command) : MoveCommand(command, "Left")
        {
        }


        /// <summary>
        /// Executes the move left command.
        /// </summary>
        void Execute() override
        {
            std::cout << "move left";
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the Move Right command.
    /// </summary>
    class MoveCommandRight : public MoveCommand
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="command">The character representing the move in the
        /// original move list.</param>
        MoveCommandRight(std::string command) : MoveCommand(command, "Right")
        {
        }


        /// <summary>
        /// Executes the move right command.
        /// </summary>
        void Execute() override
        {
            std::cout << "move right";
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the Move Up command.
    /// </summary>
    class MoveCommandUp : public MoveCommand
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="command">The character representing the move in the
        /// original move list.</param>
        MoveCommandUp(std::string command) : MoveCommand(command, "Up")
        {
        }


        /// <summary>
        /// Executes the move up command.
        /// </summary>
        void Execute() override
        {
            std::cout << "move up";
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the Move Down command.
    /// </summary>
    class MoveCommandDown : public MoveCommand
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="command">The character representing the move in the
        /// original move list.</param>
        MoveCommandDown(std::string command) : MoveCommand(command, "Down")
        {
        }


        /// <summary>
        /// Executes the move down command.
        /// </summary>
        void Execute() override
        {
            std::cout << "move down";
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the Do Nothing command.  This is the Null Object for this
    /// exercise.
    /// </summary>
    class MoveCommandNone : public MoveCommand
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="command">The character representing the move in the
        /// original move list.</param>
        MoveCommandNone(std::string command) : MoveCommand(command, "None")
        {
        }


        /// <summary>
        /// Does nothing when executed (this is the Null Object, after all).
        /// </summary>
        void Execute() override
        {
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents the processor that translates the move list into a list of
    /// MoveCommand objects then either displays them or executes them.
    /// 
    /// This classes uses a parser to convert the single letter characters in
    /// a string into a list of actions (instances of the MoveCommand).  This
    /// list of actions is then executed to perform the operations.
    /// 
    /// This process of executing the list of operations is an example of the
    /// Command pattern.  However, this can also be considered an example of
    /// the Interpreter pattern, where the actions are the tokens to be
    /// interpreted.
    /// </summary>
    class MoveProcessor
    {
    private:
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Private methods.

        /// <summary>
        /// Helper method to convert a list of single letter commands into a
        /// list of MoveCommand objects.
        /// 
        /// This method recognizes 'L', 'R', 'U', and 'D' (case-insensitive).
        /// All other characters default to the "Do Nothing" (Null Object) command.
        /// </summary>
        /// <param name="moveList">A string containing a list of single letter
        /// commands to be parsed.</param>
        /// <returns>Returns a list of MoveCommand objects.</returns>
        std::vector<MoveCommand::shared_ptr_t> _ParseMoves(std::string moveList)
        {
            std::vector<MoveCommand::shared_ptr_t> commands;
            for (size_t index = 0; index < moveList.size(); index++)
            {
                char commandChar = static_cast<char>(std::toupper(moveList[index]));
                std::string command(1, commandChar);
                MoveCommand::shared_ptr_t moveCommand;

                switch (commandChar)
                {
                    case 'U':
                        moveCommand = std::make_shared<MoveCommandUp>(command);
                        break;

                    case 'D':
                        moveCommand = std::make_shared<MoveCommandDown>(command);
                        break;

                    case 'L':
                        moveCommand = std::make_shared<MoveCommandLeft>(command);
                        break;

                    case 'R':
                        moveCommand = std::make_shared<MoveCommandRight>(command);
                        break;

                    default:
                        // Everything else is a "do nothing" command.
                        moveCommand = std::make_shared<MoveCommandNone>(command);
                        break;
                }
                commands.push_back(moveCommand);
            }

            return commands;
        }


        /// <summary>
        /// Helper method to execute all the given commands.
        /// </summary>
        /// <param name="commands">A list of MoveCommand objects to "execute".</param>
        /// <remarks>
        /// In this implementation, the MoveCommand prints the command as
        /// "<move xxx> " on the current line.  When all commands have
        /// been printed, a new line is printed to move to the next line.
        /// The "Do Nothing" command doesn't print anything, leaving only the
        /// empty <>.
        /// </remarks>
        void _ExecuteMoves(const std::vector<MoveCommand::shared_ptr_t>& commands)
        {
            for(MoveCommand::shared_ptr_t command : commands)
            {
                std::cout << "<";
                command->Execute();
                std::cout << "> ";
            }
            std::cout << std::endl;
        }


        /// <summary>
        /// Display the command character and name of the command for each
        /// command in the given list of commands.
        /// </summary>
        /// <param name="commands">The list of MoveCommand objects to display.</param>
        void _ShowMoves(const std::vector<MoveCommand::shared_ptr_t>& commands)
        {
            for (MoveCommand::shared_ptr_t command : commands)
            {
                command->Show();
            }
        }

    public:
        //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Public methods.

        /// <summary>
        /// Parse and execute the given list of move commands, where each
        /// command is represents by a single character.
        /// 
        /// Recognizes 'U', 'D', 'L', and 'R' (case-insensitive).  All other
        /// characters are assigned a "Do Nothing" (Null Object) command.
        /// </summary>
        /// <param name="moveList">A string of characters to parse and execute.</param>
        void ExecuteMoveList(std::string moveList)
        {
            std::vector<MoveCommand::shared_ptr_t> commands = _ParseMoves(moveList);
            _ExecuteMoves(commands);
        }


        /// <summary>
        /// Parse and display the given list of move commands, where each
        /// command is represents by a single character.
        /// 
        /// Recognizes 'U', 'D', 'L', and 'R' (case-insensitive).  All other
        /// characters are assigned a "Do Nothing" (Null Object) command.
        /// </summary>
        /// <param name="moveList">A string of characters to parse and display.</param>
        void ShowMoveList(std::string moveList)
        {
            std::vector<MoveCommand::shared_ptr_t> commands = _ParseMoves(moveList);
            _ShowMoves(commands);
        }
    };

} // end namespace

#endif // __NULL_OBJECT_H__

