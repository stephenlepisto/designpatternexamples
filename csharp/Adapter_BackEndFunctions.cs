/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.DataReadWriteFunctions "DataReadWriteFunctions"
/// class static functions as used in the @ref adapter_pattern.
/// 
/// For this example, the DataReadWriteFunctions class uses C#'s P/Invoke to
/// call into the Adapter_BackEnd.dll, that not only uses error codes for
/// reporting errors, but the format of the data is very different as well,
/// which also has to be adapted.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents some P/Invoke functions for accessing a named blocks of
    /// memory to read/write data in the Adapter_BackEnd.dll.
    /// </summary>
    internal static class DataReadWriteFunctions
    {
        /// <summary>
        /// All offsets must from 0 to 1 less than this value.
        /// </summary>
        public const int DDR_MAX_OFFSET = 32;        ///< All offsets must from 0 to 1 less than this value.


        /// <summary>
        /// Represents the possible errors that can be returned from the memory block
        /// access functions.  It is not possible to use C#'s P/Invoke to get these
        /// values so the enumeration needs to be duplicated here.
        /// </summary>
        public enum DDR_ErrorCode
        {
            DDR_ErrorCode_Success = 0,               ///< Operation succeeded
            DDR_ErrorCode_Block_Already_Opened = 1,  ///< Memory block is already open and cannot be opened again
            DDR_ErrorCode_Block_Not_Opened = 2,      ///< Memory block is closed and cannot be accessed
            DDR_ErrorCode_Invalid_Block_Name = 3,    ///< The given name is not a recognized memory block name
            DDR_ErrorCode_Invalid_Handle = 4,        ///< The handle argument does not correspond to a valid open memory block
            DDR_ErrorCode_Invalid_Offset = 5,        ///< The given offset is out of bounds
            DDR_ErrorCode_Null_Argument = 6          ///< The block name pointer or return handle pointer argument is NULL
        }

        /// <summary>
        /// Define the name of BLOCK 0 that can be accessed in the
        /// Adapter_BackEnd.dll.  In C#'s P/Invoke, it is not possible to map
        /// a string data through P/Invoke, only methods.
        /// </summary>
        public const string BLOCK_NAME_0 = "gorp";
        /// <summary>
        /// Define the name of BLOCK 1 that can be accessed in the
        /// Adapter_BackEnd.dll.  In C#'s P/Invoke, it is not possible to map
        /// a string data through P/Invoke, only methods.
        /// </summary>
        public const string BLOCK_NAME_1 = "baba";
        /// <summary>
        /// Define the name of BLOCK 2 that can be accessed in the
        /// Adapter_BackEnd.dll.  In C#'s P/Invoke, it is not possible to map
        /// a string data through P/Invoke, only methods.
        /// </summary>
        public const string BLOCK_NAME_2 = "yaga";


        private const string dll = "Adapter_BackEnd";

        /// <summary>
        /// P/Invoke wrapper that opens access to a memory block for exclusive
        /// use, given the name of the memory block.
        /// </summary>
        /// <param name="blockName">Name of the block to access (one of the predefined
        /// names, @p BLOCK_NAME_0, @p BLOCK_NAME_1, or @p BLOCK_NAME_2)</param>
        /// <param name="dataHandle">Returns a handle to be used for accessing the
        /// specific memory block.</param>
        /// <returns>Returns a value from the DDR_ErrorCode enumeration indicating
        /// success or failure.</returns>
        [DllImport(dll, CallingConvention = CallingConvention.Cdecl,
        ExactSpelling = true, CharSet = CharSet.Ansi)]
        internal static extern
        DDR_ErrorCode DDR_OpenMemoryBlock(string blockName, out Int32 dataHandle);

        /// <summary>
        /// P/Invoke wrapper that closes access to a previously opened memory
        /// block, thus releasing it for others to open.
        /// </summary>
        /// <param name="dataHandle">Handle to a previously opened memory block as
        /// obtained from the DDR_OpenMemoryBlock() function.</param>
        /// <returns>Returns a value from the DDR_ErrorCode enumeration indicating
        /// success or failure.</returns>
        [DllImport(dll, CallingConvention = CallingConvention.Cdecl,
        ExactSpelling = true, CharSet = CharSet.Ansi)]
        internal static extern
        DDR_ErrorCode DDR_CloseMemoryBlock(Int32 dataHandle);

        /// <summary>
        /// P/Invoke wrapper that retrieves the number of chunks in the memory
        /// block indicated by the handle to the successfully opened memory
        /// block.
        /// </summary>
        /// <param name="dataHandle">Handle to a previously opened memory block as
        /// obtained from the DDR_OpenMemoryBlock() function.</param>
        /// <param name="memorySizeInChunks">Returns the number of 32-bit chunks in the
        /// memory block.</param>
        /// <returns>Returns a value from the DDR_ErrorCode enumeration indicating
        /// success or failure.</returns>
        [DllImport(dll, CallingConvention = CallingConvention.Cdecl,
        ExactSpelling = true, CharSet = CharSet.Ansi)]
        internal static extern
        DDR_ErrorCode DDR_GetMemorySize(Int32 dataHandle, out Int32 memorySizeInChunks);

        /// <summary>
        /// P/Invoke wrapper that reads a single 32-bit value at the given
        /// offset in the memory block indicated by the specified handle.
        /// </summary>
        /// <param name="dataHandle">Handle to a previously opened memory block as
        /// obtained from the DDR_OpenMemoryBlock() function.</param>
        /// <param name="chunkOffset">Offset into the memory block from which to get
        /// the value (range is 0 to DDR_MAX_OFFSET-1).</param>
        /// <param name="value">Returns the requested valued.</param>
        /// <returns>Returns a value from the DDR_ErrorCode enumeration indicating
        /// success or failure.</returns>
        [DllImport(dll, CallingConvention = CallingConvention.Cdecl,
        ExactSpelling = true, CharSet = CharSet.Ansi)]
        internal static extern
        DDR_ErrorCode DDR_GetDataChunk(Int32 dataHandle, Int32 chunkOffset, out UInt32 value);

        /// <summary>
        /// P/Invoke wrapper that writes a single 32-bit value to the given
        /// offset in the memory block indicated by the specified handle.
        /// </summary>
        /// <param name="dataHandle">Handle to a previously opened memory block as
        /// obtained from the DDR_OpenMemoryBlock() function.</param>
        /// <param name="chunkOffset">Offset into the memory block to which to set
        /// the value (range is 0 to DDR_MAX_OFFSET-1).</param>
        /// <param name="value">The value to write to the memory block</param>
        /// <returns>Returns a value from the DDR_ErrorCode enumeration indicating
        /// success or failure.</returns>
        [DllImport(dll, CallingConvention = CallingConvention.Cdecl,
        ExactSpelling = true, CharSet = CharSet.Ansi)]
        internal static extern
        DDR_ErrorCode DDR_SetDataChunk(Int32 dataHandle, Int32 chunkOffset, UInt32 value);
    }
}
