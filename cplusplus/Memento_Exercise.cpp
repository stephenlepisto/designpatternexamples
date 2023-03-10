
/// @file
/// @brief
/// Implementation of the Memento_Exercise() function as used in the 
/// @ref memento_pattern "Memento pattern".

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <iostream>
#include <sstream>
#include <vector>

#include "helpers/replace.h"

#include "Memento_Exercise.h"
#include "Memento.h"

namespace // Anonymous
{
    using namespace DesignPatternExamples_cpp;
    
    /// <summary>
    /// The list of memento objects that form a series of snapshots in time
    /// of a Memento_TextObject.
    /// </summary>
    std::vector<IMemento::shared_ptr_t> _mementoUndoList;

    /// <summary>
    /// Take a snapshot of the given text object associated with the name of
    /// given operation.
    /// </summary>
    /// <param name="text">The Memento_TextObject to take a snapshot of.</param>
    /// <param name="operation">A string describing the operation that will
    /// be applied after the snapshot is taken.</param>
    void Memento_SaveForUndo(Memento_TextObject& text, std::string operation)
    {
        IMemento::shared_ptr_t memento = text.GetMemento(operation);
        _mementoUndoList.push_back(memento);
    }


    /// <summary>
    /// An operation to search and replace text in a Memento_TextObject.
    /// </summary>
    /// <param name="source">The Memento_TextObject to affect.</param>
    /// <param name="searchPattern">What to look for in the Memento_TextObject.</param>
    /// <param name="replaceText">What to replace the searchPattern with.</param>
    void Memento_Operation_Replace(Memento_TextObject& source, std::string searchPattern, std::string replaceText)
    {
        source.SetText(Helpers::Replace(source.Text(), searchPattern.c_str(), replaceText.c_str()));
    }

    /// <summary>
    /// An operation to reverse the characters in the given Memento_TextObject.
    /// </summary>
    /// <param name="source">The Memento_TextObject to affect.</param>
    void Memento_Operation_Reverse(Memento_TextObject& source)
    {
        std::ostringstream output;
        std::string text = source.Text();
        for (size_t index = 0; index < text.size(); ++index)
        {
            output << text[text.size() - 1 - index];
        }
        source.SetText(output.str());
    }

    /// <summary>
    /// Perform an undo on the given Command_TextObject, using the mementos in the
    /// "global" undo list.  If the undo list is empty, nothing happens.
    /// </summary>
    /// <param name="text">The Command_TextObject to affect.</param>
    void Memento_Undo(Memento_TextObject& text)
    {
        if (!_mementoUndoList.empty())
        {
            IMemento::shared_ptr_t lastMemento = _mementoUndoList.back();
            _mementoUndoList.pop_back();
            text.RestoreMemento(lastMemento);

            // Show off what we (un)did.
            std::cout
                << std::format("    undoing operation {0:<31}: \"{1}\"", lastMemento->Name(), text.ToString())
                << std::endl;
        }
    }

    /// <summary>
    /// Helper function to replace a pattern with another string in the
    /// given Memento_TextObject after adding a snapshot of the text
    /// object to the undo list.  Finally, it shows off what was done.
    /// </summary>
    /// <param name="text">The Memento_TextObject to affect.</param>
    /// <param name="searchPattern">What to look for in the Memento_TextObject.</param>
    /// <param name="replaceText">What to replace the searchPattern with.</param>
    void Memento_ApplyReplaceOperation(Memento_TextObject& text, std::string searchPattern, std::string replaceText)
    {
        std::string operationName = std::format("Replace '{0}' with '{1}'", searchPattern, replaceText);
        Memento_SaveForUndo(text, operationName);
        Memento_Operation_Replace(text, searchPattern, replaceText);
        std::cout
            << std::format("    operation {0:<31}: \"{1}\"", operationName, text.ToString())
            << std::endl;
    }


    /// <summary>
    /// Helper function to reverse the order of the characters in the
    /// given Memento_TextObject after adding a snapshot of the text
    /// object to an undo list.  Finally, it shows what was done.
    /// </summary>
    /// <param name="text">The Memento_TextObject to affect.</param>
    void Memento_ApplyReverseOperation(Memento_TextObject& text)
    {
        std::string operationName = "Reverse";
        Memento_SaveForUndo(text, operationName);
        Memento_Operation_Reverse(text);
        std::cout
            << std::format("    operation {0:<31}: \"{1}\"", operationName, text.ToString())
            << std::endl;
    }

} // end namespace Anonmyous


namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Example of using the @ref memento_pattern "Memento" design pattern.
    /// 
    /// In this exercise, the Memento pattern is used to take snapshots of
    /// a text object so as to form an undo list of changes to the text
    /// object.  Undoing an operation means restoring a snapshot of the
    /// text object.
    /// 
    /// The undo list is implemented as a stack of memento objects that
    /// each represent a snapshot of the text object taken before each
    /// operation is applied.  After all operations are applied, the
    /// mementos are used to restore the text object in reverse order,
    /// effectively undoing each operation in turn.
    /// 
    /// Compare this to the Command_Exercise() and note that the steps
    /// taken there are identical to here (except for method names, of
    /// course).  The difference lies in how operations are executed
    /// and undone.  Mementos make the undo process much cleaner and
    /// faster since operations do not need to be applied repeatedly to
    /// get the text object into a specific state.  Specifically,
    /// compare Command_Undo() with Memento_Undo().  Also note the
    /// differences in the "Memento_ApplyXXOperation()" methods, which
    /// more cleanly separate the save from the operation.
    /// </summary>
    // ! [Using Memento in C++]
    void Memento_Exercise()
    {
        std::cout << std::endl;
        std::cout << "Memento Exercise" << std::endl;

        // Start with a fresh undo list.
        _mementoUndoList.clear();

        // The base text object to work from.
        Memento_TextObject text("This is a line of text on which to experiment.");

        std::cout
            << std::format("  Starting text: \"{0}\"", text.ToString())
            << std::endl;

        // Apply four operations to the text.
        Memento_ApplyReplaceOperation(text, "text", "painting");
        Memento_ApplyReplaceOperation(text, "on", "off");
        Memento_ApplyReverseOperation(text);
        Memento_ApplyReplaceOperation(text, "i", "!");

        std::cout << "  Now perform undo until back to original" << std::endl;

        // Now undo the four operations.
        Memento_Undo(text);
        Memento_Undo(text);
        Memento_Undo(text);
        Memento_Undo(text);

        std::cout
            << std::format("  Final text   : \"{0}\"", text.ToString())
            << std::endl;

        std::cout << "  Done." << std::endl;
    }
    // ! [Using Memento in C++]

} // end namespace
