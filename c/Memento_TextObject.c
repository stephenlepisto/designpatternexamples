/// @file
/// @brief
/// Implementation of the Memento_TextObject structure's support functions,
/// Memento_TextObject_Create(), Memento_TextObject_Destroy(),
/// Memento_TextObject_GetText(), Memento_TextObject_SetText(), and
/// Memento_TextObject_ToString(),
/// as used in the @ref memento_pattern.

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>

#include "helpers/strdup.h"

#include "Memento_TextObject.h"

///////////////////////////////////////////////////////////////////////////////
// Memento_TextObject_Create()
///////////////////////////////////////////////////////////////////////////////
Memento_TextObject* Memento_TextObject_Create(const char* text)
{
    Memento_TextObject* textObject = NULL;

    if (text != NULL)
    {
        textObject = calloc(1, sizeof(Memento_TextObject));
        if (textObject != NULL)
        {
            textObject->text = STRDUP(text);
            if (textObject->text == NULL)
            {
                printf("  Error!  Out of memory duplicating text for Memento_TextObject!\n");
                free(textObject);
                textObject = NULL;
            }
        }
        else
        {
            printf("  Error!  Out of memory creating a Memento_TextObject!\n");
        }
    }

    return textObject;
}

///////////////////////////////////////////////////////////////////////////////
// Memento_TextObject_Destroy()
///////////////////////////////////////////////////////////////////////////////
void Memento_TextObject_Destroy(Memento_TextObject* textObject)
{
    if (textObject != NULL)
    {
        free(textObject->text);
        free(textObject);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Memento_TextObject_GetText()
///////////////////////////////////////////////////////////////////////////////
char* Memento_TextObject_GetText(Memento_TextObject* textObject)
{
    char* text = NULL;
    if (textObject != NULL)
    {
        text = textObject->text;
    }

    return text;
}


///////////////////////////////////////////////////////////////////////////////
// Memento_TextObject_SetText()
///////////////////////////////////////////////////////////////////////////////
void Memento_TextObject_SetText(Memento_TextObject* textObject, const char* newText)
{
    if (textObject != NULL && newText != NULL)
    {
        free(textObject->text);
        textObject->text = STRDUP(newText);
        if (textObject->text == NULL)
        {
            printf("  Error!  Out of memory setting text on a Memento_TextObject!\n");
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
// Memento_TextObject_ToString()
///////////////////////////////////////////////////////////////////////////////
const char* Memento_TextObject_ToString(Memento_TextObject* textObject)
{
    const char* text = NULL;

    if (textObject != NULL)
    {
        text = textObject->text;
    }

    return text;
}
