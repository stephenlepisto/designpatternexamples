/// @file
/// @brief
/// Implementation of the Command_TextObject structure and associated functions
/// as used in the @ref command_pattern.


#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include "Command_TextObject.h"

///////////////////////////////////////////////////////////////////////////////
// Command_TextObject_Initialize()
///////////////////////////////////////////////////////////////////////////////
bool Command_TextObject_Initialize(Command_TextObject* textObject, const char* startingText)
{
    bool initialized = false;

    Command_TextObject_Clear(textObject);
    if (textObject != NULL && startingText != NULL)
    {
        textObject->startingText = startingText;
        textObject->text = _strdup(textObject->startingText);
        initialized = true;
    }
    return initialized;
}

///////////////////////////////////////////////////////////////////////////////
// Command_TextObject_Clear()
///////////////////////////////////////////////////////////////////////////////
void Command_TextObject_Clear(Command_TextObject* textObject)
{
    if (textObject != NULL)
    {
        free(textObject->text);
        textObject->startingText = NULL;
        textObject->text = NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Command_TextObject_Reset()
///////////////////////////////////////////////////////////////////////////////
void Command_TextObject_Reset(Command_TextObject* textObject)
{
    if (textObject != NULL)
    {
        free(textObject->text);
        textObject->text = _strdup(textObject->startingText);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Command_TextObject_GetText()
///////////////////////////////////////////////////////////////////////////////
char* Command_TextObject_GetText(Command_TextObject* textObject)
{
    char* text = NULL;

    if (textObject != NULL)
    {
        text = textObject->text;
    }

    return text;
}

///////////////////////////////////////////////////////////////////////////////
// Command_TextObject_SetText()
///////////////////////////////////////////////////////////////////////////////
void Command_TextObject_SetText(Command_TextObject* textObject, const char* newText)
{
    if (textObject != NULL && newText != NULL)
    {
        free(textObject->text);
        textObject->text = _strdup(newText);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Command_TextObject_ToString()
///////////////////////////////////////////////////////////////////////////////
const char* Command_TextObject_ToString(Command_TextObject* textObject)
{
    const char* text = NULL;

    if (textObject != NULL)
    {
        text = textObject->text;
    }

    return text;
}
