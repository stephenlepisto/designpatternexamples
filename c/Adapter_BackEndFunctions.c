/// @file
/// @brief
/// Implementation of the DataReadWriteFunctions
/// namespace functions as used in the @ref adapter_pattern "Adapter pattern".

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "Adapter_BackEndFunctions.h"

/// <summary>
/// Error code returned by the Data Read/Write functions. 
/// </summary>
/// <remarks>The caller would consult a reference manual for these
/// error codes or get them from a header file.  These are defined here
/// for this example to make it clear error codes are being returned.
/// The caller can use GetLastErrorMessage() to translate the error
/// code to a human-readable string.
/// </remarks>
typedef enum _ErrorCodes
{
    ErrorCode_NoError = 0,
    ErrorCode_InvalidParameter = 1,
    ErrorCode_AlreadyShutDown = 2,
    ErrorCode_AlreadyStarted = 3,
    ErrorCode_InvalidDataHandle = 4,
    ErrorCode_OutOfMemory = 5
} ErrorCodes;

typedef struct _DataBlock
{
    char* initdata;
    uint8_t* data;
    size_t dataCount;
} DataBlock;

typedef struct _DataBlockList
{
    DataBlock** datablocks;
    size_t datablocksCount;
} DataBlockList;

typedef struct _HandleToString
{
    char* string;
    int handle;
} HandleToString;

typedef struct _HandleToStringList
{
    HandleToString** items;
    size_t itemsCount;
} HandleToStringList;

/// <summary>
/// A list of DataBlock objects.  Each DataBlock object contains a string that
/// identifies the block.
/// </summary>
DataBlockList _localData;

/// <summary>
/// A list of HandleToString objects.  Each HandleToString associates a unique
/// handle with a string, where the string is a key to a DataBlock in the _localData
/// list.  The handle is the token returned to the caller.
/// </summary>
HandleToStringList _handleToKey;


/// <summary>
/// The next token to allocate.
/// </summary>
static int _nextKey = 0;

/// <summary>
/// The last error code set by a function.
/// </summary>
static ErrorCodes _lastErrorCode;


static DataBlock* DataBlock_Create(const char* initdata, uint8_t* data, size_t dataCount)
{
    DataBlock* block = (DataBlock*)malloc(sizeof(DataBlock));
    if (block != NULL)
    {
        if (initdata != NULL && data != NULL)
        {
            block->initdata = _strdup(initdata);
            block->data = data; // NOTE: we take ownership of the data!
            block->dataCount = dataCount;
        }
        else
        {
            free(block);
            block = NULL;
            _lastErrorCode = ErrorCode_OutOfMemory;
        }
    }
    return block;
}

static void DataBlock_Destroy(DataBlock* block)
{
    if (block != NULL)
    {
        free(block->initdata);
        block->initdata = NULL;
        free(block->data);
        block->data = NULL;
        block->dataCount = 0;
        free(block);
    }
}

static bool DataBlock_Grow(DataBlock* block, size_t newSize)
{
    bool blockResized = true;

    if (block != NULL)
    {
        if (block->data != NULL)
        {
            if (newSize > block->dataCount)
            {
                uint8_t* newblock = (uint8_t*)realloc(block->data, newSize);
                if (newblock != NULL)
                {
                    block->data = newblock;
                }
                else
                {
                    blockResized = false;
                }
            }
        }
    }
    return blockResized;
}

static void DataBlockList_Initialize(DataBlockList* blockList)
{
    if (blockList != NULL)
    {
        blockList->datablocks = NULL;
        blockList->datablocksCount = 0;
    }
}


static void DataBlockList_Destroy(DataBlockList* blockList)
{
    if (blockList != NULL && blockList->datablocks != NULL)
    {
        for (size_t index = 0; index < blockList->datablocksCount; index++)
        {
            DataBlock_Destroy(blockList->datablocks[index]);
        }
        free(blockList->datablocks);
        blockList->datablocks = NULL;
        blockList->datablocksCount = 0;
    }
}


static bool DataBlockList_AddBlock(DataBlockList* blockList, DataBlock* block)
{
    bool blockAdded = false;

    if (blockList != NULL && block != NULL)
    {
        DataBlock** newList = NULL;
        if (blockList->datablocks == NULL)
        {
            newList = (DataBlock**)malloc(sizeof(DataBlock*));
        }
        else
        {
            size_t emptySlotIndex = -1;
            for (size_t index = 0; index < blockList->datablocksCount; index++)
            {
                if (blockList->datablocks[index]->data == NULL)
                {
                    emptySlotIndex = index;
                    break;
                }
            }
            if (emptySlotIndex != -1)
            {
                // Reuse the empty slot
                blockList->datablocks[emptySlotIndex] = block;
                blockAdded = true;
            }
            else
            {
                size_t newSize = (blockList->datablocksCount + 1) * sizeof(DataBlock*);
                newList = (DataBlock**)realloc(blockList->datablocks, newSize);
            }
        }
        if (newList != NULL)
        {
            blockList->datablocks = newList;
            blockList->datablocks[blockList->datablocksCount] = block; // We take ownership of the block
            blockList->datablocksCount++;
            blockAdded = true;
        }
    }

    return blockAdded;
}

static void DataBlockList_RemoveBlock(DataBlockList* blockList, int blockIndex)
{
    if (blockList != NULL)
    {
        if (blockIndex >= 0 && blockIndex < blockList->datablocksCount)
        {
            DataBlock_Destroy(blockList->datablocks[blockIndex]);
        }
    }
}


static int DataBlockList_FindBlock(DataBlockList* blockList, const char* initdata)
{
    int foundIndex = -1;

    if (blockList != NULL && initdata != NULL)
    {
        for (size_t index = 0; index < blockList->datablocksCount; index++)
        {
            if (blockList->datablocks[index]->initdata != NULL &&
                strcmp(blockList->datablocks[index]->initdata, initdata) == 0)
            {
                foundIndex = (int)index;
                break;
            }
        }
    }

    return foundIndex;
}


static HandleToString* HandleToString_Create(const char* initdata, int handle)
{
    HandleToString* handleToString = NULL;

    if (initdata != NULL)
    {
        handleToString = (HandleToString*)malloc(sizeof(HandleToString));
        if (handleToString != NULL)
        {
            handleToString->handle = handle;
            handleToString->string = _strdup(initdata);
            if (handleToString->string == NULL)
            {
                free(handleToString);
                handleToString = NULL;
            }
        }
    }
    return handleToString;
}

static void HandleToString_Destroy(HandleToString* handleToString)
{
    if (handleToString != NULL)
    {
        free(handleToString->string);
        handleToString->string = NULL;
        free(handleToString);
    }
}

static void HandleToStringList_Initialize(HandleToStringList* list)
{
    if (list != NULL)
    {
        list->items = NULL;
        list->itemsCount = 0;
    }
}

static void HandleToStringList_Destroy(HandleToStringList* list)
{
    if (list != NULL)
    {
        for (size_t index = 0; index < list->itemsCount; index++)
        {
            HandleToString_Destroy(list->items[index]);
        }
        free(list->items);
    }
}

static bool HandleToStringList_AddHandle(HandleToStringList* list, HandleToString* item)
{
    bool handleAdded = false;

    if (list != NULL && item != NULL)
    {
        HandleToString** newList = NULL;
        if (list->items == NULL)
        {
            newList = (HandleToString**)malloc(sizeof(HandleToString*));
        }
        else
        {
            size_t newSize = (list->itemsCount + 1) * sizeof(HandleToString*);
            newList = (HandleToString**)realloc(list->items, newSize);
        }
        if (newList != NULL)
        {
            list->items = newList;
            list->items[list->itemsCount] = item; // We take ownership of the block
            list->itemsCount++;
            handleAdded = true;
        }
    }

    return handleAdded;
}

static void HandleToStringList_RemoveHandle(HandleToStringList* list, int handleIndex)
{
    if (list != NULL)
    {
        if (handleIndex >= 0 && handleIndex < list->itemsCount)
        {
            HandleToString_Destroy(list->items[handleIndex]);
        }
    }
}


static int HandleToStringList_FindByHandle(HandleToStringList* list, int handle)
{
    int foundIndex = -1;
    
    if (list != NULL)
    {
        for (size_t index = 0; index < list->itemsCount; index++)
        {
            if (list->items[index]->handle == handle)
            {
                foundIndex = (int)index;
                break;
            }
        }
    }
    return foundIndex;
}

static int HandleToStringList_FindByString(HandleToStringList* list, const char* string)
{
    int foundIndex = -1;

    if (list != NULL)
    {
        for (size_t index = 0; index < list->itemsCount; index++)
        {
            if (strcmp(list->items[index]->string, string) == 0)
            {
                foundIndex = (int)index;
                break;
            }
        }
    }
    return foundIndex;
}


///////////////////////////////////////////////////////////////////////
// Initialize the data reader/writer.
///////////////////////////////////////////////////////////////////////
int DDR_Startup(const char* initData, int* dataHandle)
{
    _lastErrorCode = ErrorCode_InvalidParameter;
    if (dataHandle != NULL)
    {
        _lastErrorCode = ErrorCode_AlreadyStarted;
        *dataHandle = -1;
        int foundIndex = DataBlockList_FindBlock(&_localData, initData);
        if (foundIndex == -1)
        {
            // Generate a buffer of integers to use as the initial data
            // that in turn is associated with the initData name.
            size_t dataSize = 128;
            uint8_t* data = (uint8_t*)malloc(dataSize);
            _lastErrorCode = ErrorCode_OutOfMemory;
            if (data != NULL)
            {
                for (size_t index = 0; index < dataSize; ++index)
                {
                    // Reverse order of numbers.
                    data[index] = (uint8_t)(dataSize - index);
                }
                HandleToString* handleToString = NULL;
                DataBlock* block = DataBlock_Create(initData, data, dataSize);
                if (block != NULL)
                {
                    if (DataBlockList_AddBlock(&_localData, block))
                    {
                        // Use the next token (a handle) for the initData buffer.
                        handleToString = HandleToString_Create(initData, _nextKey);
                        if (handleToString != NULL)
                        {
                            if (HandleToStringList_AddHandle(&_handleToKey, handleToString))
                            {
                                // Return the token and generate a new one for next time.
                                *dataHandle = _nextKey;
                                ++_nextKey;
                                _lastErrorCode = ErrorCode_NoError;
                            }
                        }
                        
                        if (_lastErrorCode == ErrorCode_OutOfMemory)
                        {
                            // We failed to create a HandleToString or failed to add that
                            // to the HandleToStringList, so undo the add block operation
                            // so as to unwind the state to before we added anything.
                            // We will delete all the stuff that was allocated to this point
                            // before exiting.
                            int foundDataBlock = DataBlockList_FindBlock(&_localData, block->initdata);
                            if (foundDataBlock != -1)
                            {
                                DataBlockList_RemoveBlock(&_localData, foundDataBlock);
                            }
                            // DataBlockList took ownership of the block when added so we
                            // just need to make sure we don't delete it again below.
                            block = NULL;
                        }
                    }
                }

                if (_lastErrorCode == ErrorCode_OutOfMemory)
                {
                    HandleToString_Destroy(handleToString);
                    handleToString = NULL;
                    DataBlock_Destroy(block);
                    block = NULL;
                    free(data);
                    data = NULL;
                }
            }
        }
    }
    return (int)_lastErrorCode;
}


///////////////////////////////////////////////////////////////////////
// Shut down the data reader/writer.
///////////////////////////////////////////////////////////////////////
int DDR_Shutdown(int dataHandle)
{
    _lastErrorCode = ErrorCode_AlreadyShutDown;

    int foundHandleIndex = HandleToStringList_FindByHandle(&_handleToKey, dataHandle);
    if (foundHandleIndex != -1)
    {
        int foundDataIndex = DataBlockList_FindBlock(&_localData, _handleToKey.items[foundHandleIndex]->string);
        if (foundDataIndex != -1)
        {
            DataBlockList_RemoveBlock(&_localData, foundDataIndex);
        }
        HandleToStringList_RemoveHandle(&_handleToKey, foundHandleIndex);
        _lastErrorCode = ErrorCode_NoError;
    }

    return (int)_lastErrorCode;
}


///////////////////////////////////////////////////////////////////////
// Retrieve the message related to the last error reported as a string.
///////////////////////////////////////////////////////////////////////
const char* DDR_GetLastErrorMessage()
{
    const char* errorMessage = "";
    switch (_lastErrorCode)
    {
    case ErrorCode_NoError:
        break;

    case ErrorCode_InvalidParameter:
        errorMessage = "Invalid parameter";
        break;

    case ErrorCode_AlreadyShutDown:
        errorMessage = "Data reader/writer already shut down.";
        break;

    case ErrorCode_AlreadyStarted:
        errorMessage = "Data reader/writer already started.";
        break;

    case ErrorCode_InvalidDataHandle:
        errorMessage = "Invalid data handle";
        break;

    case ErrorCode_OutOfMemory:
        errorMessage = "Out of memory";
        break;

    default:
        errorMessage = "Unknown error";
        break;
    }
    return errorMessage;
}


///////////////////////////////////////////////////////////////////////
// Write a block of bytes to the target.
///////////////////////////////////////////////////////////////////////
int DDR_WriteData(int dataHandle, const uint8_t* data, uint32_t dataLength)
{
    _lastErrorCode = ErrorCode_InvalidParameter;

    if (data != NULL)
    {
        _lastErrorCode = ErrorCode_InvalidDataHandle;
        int foundHandleIndex = HandleToStringList_FindByHandle(&_handleToKey, dataHandle);
        if (foundHandleIndex != -1)
        {
            int foundDataIndex = DataBlockList_FindBlock(&_localData, _handleToKey.items[foundHandleIndex]->string);
            if (foundDataIndex != -1)
            {
                _lastErrorCode = ErrorCode_OutOfMemory;
                DataBlock* block = _localData.datablocks[foundDataIndex];
                if (DataBlock_Grow(block, dataLength))
                {
                    for (uint32_t index = 0; index < dataLength; ++index)
                    {
                        block->data[index] = data[index];
                    }
                }
                _lastErrorCode = ErrorCode_NoError;
            }
        }
    }

    return (int)_lastErrorCode;
}


///////////////////////////////////////////////////////////////////////
// Read a block of bytes from the target.
///////////////////////////////////////////////////////////////////////
int DDR_ReadData(int dataHandle, uint32_t maxDataLength, uint8_t* data,
    uint32_t* availableDataLength)
{
    _lastErrorCode = ErrorCode_InvalidParameter;

    if (availableDataLength != NULL)
    {
        *availableDataLength = 0;
        _lastErrorCode = ErrorCode_InvalidDataHandle;
        int foundHandleIndex = HandleToStringList_FindByHandle(&_handleToKey, dataHandle);
        if (foundHandleIndex != -1)
        {
            int foundDataIndex = DataBlockList_FindBlock(&_localData, _handleToKey.items[foundHandleIndex]->string);
            if (foundDataIndex != -1)
            {
                DataBlock* block = _localData.datablocks[foundDataIndex];
                *availableDataLength = (uint32_t)block->dataCount;

                // Note: data parameter is allowed to be null
                _lastErrorCode = ErrorCode_NoError;
                if (data != NULL)
                {
                    _lastErrorCode = ErrorCode_InvalidParameter;
                    // If buffer is large enough to contain the requested
                    // data then
                    if (*availableDataLength >= maxDataLength)
                    {
                        // Read only up to the amount available
                        uint32_t byteCount = maxDataLength > block->dataCount
                            ? (uint32_t)block->dataCount : maxDataLength;
                        for (uint32_t index = 0; index < byteCount; ++index)
                        {
                            data[index] = block->data[index];
                        }
                        _lastErrorCode = ErrorCode_NoError;
                    }
                }
            }
        }
    }
    return (int)_lastErrorCode;
}
