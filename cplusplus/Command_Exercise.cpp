
/// @file
/// @brief
/// Implementation of the Command_Exercise() function as used in the 
/// @ref command_pattern.

#include <iostream>
#include <sstream>
#include <vector>

#include "Command_Exercise.h"
#include "Command_Classes.h"

#include "helpers/formatstring.h"
#include "helpers/replace.h"

namespace // Anonymous
{
    using namespace DesignPatternExamples_cpp;

    /// <summary>
    /// The list of commands applied.
    /// </summary>
    std::vector<Command> _commandUndoList;

    /// <summary>
    /// Save the given command on the undo list then execute the command on
    /// the given text object.
    /// </summary>
    /// <param name="command">The Command object to apply to the text object.</param>
    void Command_Save_And_Execute(Command command)
    {
        _commandUndoList.push_back(command);
        command.Execute();
    }

    /// <summary>
    /// An operation to search and replace text in a Command_TextObject.
    /// </summary>
    /// <param name="source">The Command_TextObject to affect.</param>
    /// <param name="searchPattern">What to look for in the Command_TextObject.</param>
    /// <param name="replaceText">What to replace the searchPattern with.</param>
    static void Command_Operation_Replace(Command_TextObject::shared_ptr_t source, std::string searchPattern, std::string replaceText)
    {
        std::string newText = Helpers::Replace(source->Text(), searchPattern.c_str(), replaceText.c_str());
        source->SetText(newText);
    }

    /// <summary>
    /// An operation to reverse the characters in the given Command_TextObject.
    /// </summary>
    /// <param name="source">The Command_TextObject to affect.</param>
    static void Command_Operation_Reverse(Command_TextObject::shared_ptr_t source)
    {
        std::ostringstream output;
        std::string text = source->Text();
        for (size_t index = 0; index < text.size(); ++index)
        {
            output << text[text.size() - 1 - index];
        }
        source->SetText(output.str());
    }

    /// <summary>
    /// Perform an undo on the given Command_TextObject, using the commands in the
    /// "global" undo list.  If the undo list is empty, nothing happens.
    /// </summary>
    /// <param name="text">The Command_TextObject to affect.</param>
    void Command_Undo(Command_TextObject::shared_ptr_t text)
    {
        if (!_commandUndoList.empty())
        {
            // Reset the text to the starting point.
            text->Reset();

            // Get rid of the last command applied and remember it.
            Command lastCommand = _commandUndoList.back();
            _commandUndoList.pop_back();

            // Now apply all remaining commands to the text in order
            // (oldest to newest).
            std::vector<Command>::iterator commandIter = std::begin(_commandUndoList);
            while (commandIter != std::end(_commandUndoList))
            {
                (*commandIter).Execute();
                commandIter++;
            }

            // Show off what we (un)did.
            std::cout << Helpers::formatstring("    undoing command %-31s==> \"%s\"",
                lastCommand.ToString().c_str(), text->ToString().c_str()) << std::endl;
        }
    }

    /// <summary>
    /// Helper function to create a Command object that replaces text in the given
    /// Command_TextObject, adds the command to the undo list and then applies the command
    /// to the Command_TextObject.  Finally, it shows off what was done.
    /// </summary>
    /// <param name="text">The Command_TextObject to affect.</param>
    /// <param name="searchPattern">What to look for in the Command_TextObject.</param>
    /// <param name="replaceText">What to replace the searchPattern with.</param>
    void Command_ApplyReplaceCommand(Command_TextObject::shared_ptr_t text, std::string searchPattern, std::string replaceText)
    {
        Command command(text, "Replace", Command_Operation_Replace, searchPattern, replaceText);
        Command_Save_And_Execute(command);
        std::cout << Helpers::formatstring("    command %-31s==> \"%s\"",
            command.ToString().c_str(), text->ToString().c_str()) << std::endl;
    }


    /// <summary>
    /// Helper function to create a Command object that reverses the order of
    /// the characters in the given Command_TextObject, adds the command to the undo
    /// list and then applies the command to the Command_TextObject.  Finally, it shows
    /// what was done.
    /// </summary>
    /// <param name="text">The Command_TextObject to affect.</param>
    void Command_ApplyReverseCommand(Command_TextObject::shared_ptr_t text)
    {
        Command command(text, "Reverse", Command_Operation_Reverse);
        Command_Save_And_Execute(command);
        std::cout << Helpers::formatstring("    command %-31s==> \"%s\"",
            command.ToString().c_str(), text->ToString().c_str()) << std::endl;
    }

} // end anonymous namespace

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Example of using the @ref command_pattern "Command" design pattern.
    /// 
    /// The Command pattern is used to encapsulate an operation or command
    /// associated with an object so that the command can be applied to
    /// the object at a later time.
    /// 
    /// In this exercise, an undo list is implemented using Commands that
    /// associate commands defined in this file with a text object.  The
    /// commands are applied to the text object in succession then
    /// effectively undone.
    /// </summary>
    // ! [Using Command in C++]
    void Command_Exercise()
    {
        std::cout << std::endl;
        std::cout << "Command Exercise" << std::endl;

        // The base text object to work from.
        Command_TextObject::shared_ptr_t text = std::make_shared<Command_TextObject>("This is a line of text on which to experiment.");

        std::cout << Helpers::formatstring("  Starting text: \"%s\"", text->ToString().c_str()) << std::endl;

        // Apply four operations to the text.
        Command_ApplyReplaceCommand(text, "text", "painting");
        Command_ApplyReplaceCommand(text, "on", "off");
        Command_ApplyReverseCommand(text);
        Command_ApplyReplaceCommand(text, "i", "!");

        std::cout << "  Now perform undo until back to original" << std::endl;

        // Now undo the four operations.
        Command_Undo(text);
        Command_Undo(text);
        Command_Undo(text);
        Command_Undo(text);

        std::cout << Helpers::formatstring("  Final text   : \"%s\"", text->ToString().c_str()) << std::endl;

        std::cout << "  Done." << std::endl;
    }
    // ! [Using Command in C++]


} // end namespace
