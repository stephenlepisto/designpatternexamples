// The Facade design pattern is basically a simplified interface to a
// complicated sub-system.  Using facades is one more step in creating loose
// coupling between sub-systems while at the same time simplifying the
// functionality exposed from a sub-system.
//
// Facades are sometimes known as facets.
//
// A facade is used in situations where the full power of a sub-system isn't
// needed but the sub-system needs to be kept intact.  In effect, a facade
// provides a "beginner's" interface to a complicated chunk of code whereas
// the API of the complicated chunk of code is for "advanced" users.
//
// A simplification of a complex system could mean providing a high level
// function that uses a number of lower level functions in the complex
// system.  Or the facade could provide only a few of the entry points into
// the complex system so the interface is kept simple.
//
// Another way of thinking about Facades is on a large system that exposes
// many different interfaces, depending on what entity needs to access the
// system.  Each entity sees only the interface exposed to it by the large
// system.  A specific example of this is Visual Studio.
//
// Visual Studio enables plugins through the Component Object Model (COM)
// architecture of Windows.  A COM interface can be obtained from an
// implementation class (COM Class or coclass).  A coclass can implement
// multiple different COM interfaces.  From any interface, any other interface
// on that coclass can be requested.  A Visual Studio plugin is a coclass that
// implements mulitple interfaces exposed to Visual Studio.  Those interfaces
// on the plugin are facades to the plugin.  Visual Studio itself is exposed
// to the plugin through different COM interfaces, which become the facades on
// the Visual Studio system.
//
// In other words, COM is a formalized mechanism to expose facades
// (interfaces) on a particular system to other entities that themselves could
// expose facades in return.
//
// One thing to keep in mind is the Facade does not add any functionality,
// it only simplifies what is available.  This means the Facade interface
// generally does not retain any state of its own, leaving that to the
// complicated sub-system.  The Facade might retain one or more tokens or
// handles from the sub-system to facility access to the sub-system.
//
// The example provided is a complicated sub-system with many different low-
// level functions.  This functionality is exposed through a low level
// interface.  A facade is provided through a second interface that exposes
// a simplified set of functions for most common operations.

namespace DesignPatternExamples
{
    /// <summary>
    /// Represents a network of TAP chains and the low level access to that
    /// network.  In general, the caller should take a lock on a TAP chain
    /// befor accessing it then release the lock when done.
    /// </summary>
    /// <remarks>
    /// This interface makes it easier to contrast with the ITAPNetworkHighLevel
    /// interface.
    /// </remarks>
    public interface ITAPNetworkLowLevel
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


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents a high level view of a complex network of TAP chains.
    /// A TAP chain can be thought of as a list of devices that can be made
    /// visible or hidden in the list but maintain the same relationship to
    /// each other regardless of visibility.
    /// 
    /// The methods on this high level interface may seem the same as on the
    /// ITAPNetworkLowLevel interface.  However, most of the methods on this
    /// high level interface hide the need for taking a lock on a chain before
    /// accessing the chain.
    /// 
    /// This high level interface is a
    /// simplification and thus a facade for the low level interface and the
    /// system underneath.
    /// </summary>
    public interface ITAPNetworkHighLevel
    {
        /// <summary>
        /// The number of TAP chains available from the sub-system.
        /// </summary>
        int NumChains { get; }

        /// <summary>
        /// Returns a list of all idcodes from all selected devices in the
        /// given TAP chain.
        /// </summary>
        /// <param name="chainIndex">Index of the TAP chain to access (0..NumChains-1).</param>
        /// <returns>An array holding the idcodes of all visible TAPs in the given
        /// chain.</returns>
        uint[] GetIdcodes(int chainIndex);

        /// <summary>
        /// Make visible certain TAPs in the given TAP chain.  The selectMask value
        /// has a bit set for each TAP device to make visible.
        /// </summary>
        /// <param name="chainIndex">Index of the TAP chain to access (0..NumChains-1).</param>
        /// <param name="selectMask">A bit mask where each bit corresponds to a TAP,
        /// up to the number of TAPs in the given TAP chain.  Bit 0 is ignored as the first
        /// TAP is always visible.</param>
        void SelectTAPs(int chainIndex, uint selectMask);

        /// <summary>
        /// Resets the given TAP chain so that all devices except the TAP
        /// controller is no longer visible.
        /// </summary>
        /// <param name="chainIndex">Index of the TAP chain to access (0..NumChains-1).</param>
        void ResetTAPs(int chainIndex);
    }
}
