/// @file
/// @brief
/// Implementation of the Memento structure's support functions,
/// Memento_Create() and Memento_Destroy(),
/// as used in the @ref memento_pattern.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>

#include "helpers/strdup.h"

#include "Memento_Memento.h"

///////////////////////////////////////////////////////////////////////////////
// Memento_Create()
///////////////////////////////////////////////////////////////////////////////
Memento* Memento_Create(const char* text, const char* name)
{
    Memento* memento = NULL;

    if (text != NULL && name != NULL)
    {
        memento = calloc(1, sizeof(Memento));
        if (memento != NULL)
        {
            memento->text = NULL;
            memento->name = STRDUP(name);
            if (memento->name != NULL)
            {

                memento->text = STRDUP(text);
                if (memento->text == NULL)
                {
                    printf("  Error! Out of memory preserving text in the Memento!\n");
                    free((char*)memento->name);
                    free(memento);
                    memento = NULL;
                }
            }
            else
            {
                printf("  Error!  Out of memory duplicating the Memento's name.\n");
                free(memento);
                memento = NULL;
            }
        }
        else
        {
            printf("  Error!  Out of memory creating a Memento.\n");
        }
    }

    return memento;
}

///////////////////////////////////////////////////////////////////////////////
// Memento_Destroy()
///////////////////////////////////////////////////////////////////////////////
void Memento_Destroy(Memento* memento)
{
    if (memento != NULL)
    {
        free(memento->text);
        memento->text = NULL;
        free((char*)memento->name);
        memento->name = NULL;
        free(memento);
    }
}
