// The Facade design pattern.  See Facade_Class.cs for details.
//
// This module defines the full interface for the complicated sub-system
// being modeled in this example.  The Facade_Class uses an instance of this
// interface to make calls into the sub-system.

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents a network of TAP chains.
    /// </summary>
    /// <remarks>
    /// This interface makes it easier to see what is actually exposed from the
    /// complicated sub-system.
    /// </remarks>
    public interface ITAPNetwork
    {
        /// <summary>
        /// Retrieve the number of TAP chains available in the network.
        /// </summary>
        /// <returns>Returns the number of TAP chains available.</returns>
        int GetNumChains();

        /// <summary>
        /// Lock the specified TAP chain for exclusive access.
        /// </summary>
        /// <param name="chainIndex">Index of the TAP chain (0..n-1).</param>
        /// <returns>Returns true if the TAP chain was successfully locked.</returns>
        bool LockTAPs(int chainIndex);

        /// <summary>
        /// Unlock the specified TAP chain to release exclusive access.
        /// </summary>
        /// <param name="chainIndex">Index of the TAP chain (0..n-1).</param>
        /// <returns>Returns true if the TAP chain was successfully unlocked.</returns>
        bool UnlockTAPs(int chainIndex);

        /// <summary>
        /// Reset the visibility of all TAPs on the specified TAP chain.
        /// </summary>
        /// <param name="chainIndex">Index of the TAP chain (0..n-1).</param>
        void ResetTAPs(int chainIndex);

        /// <summary>
        /// Make visible the specified TAPs on the specified TAP chain.
        /// </summary>
        /// <param name="chainIndex">Index of the TAP chain (0..n-1).</param>
        /// <param name="tapSelectMask">Bit mask where each bit set indicates the
        /// corresponding TAP should be made visible.  Bit 0 corresponds to the first
        /// TAP, bit 1 to the second TAP, etc.  CLTAP devices are always visible.</param>
        void SelectTAPs(int chainIndex, uint tapSelectMask);

        /// <summary>
        /// Make invisible the specified TAPs on the specified TAP chain.
        /// </summary>
        /// <param name="chainIndex">Index of the TAP chain (0..n-1).</param>
        /// <param name="tapSelectMask">Bit mask where each bit set indicates the
        /// corresponding TAP should be made invisible.  Bit 0 corresponds to the first
        /// TAP, bit 1 to the second TAP, etc.  CLTAP devices are always visible.</param>
        void DeselectTAPs(int chainIndex, uint tapSelectMask);

        /// <summary>
        /// Retrieve a list of idcodes of all visible TAPs in the given TAP chain.
        /// </summary>
        /// <param name="chainIndex">Index of the TAP chain (0..n-1).</param>
        /// <returns>Returns an array of idcodes for each visible TAP, with the first
        /// TAP being at index 0.</returns>
        uint[] GetIdcodes(int chainIndex);
    }
}
