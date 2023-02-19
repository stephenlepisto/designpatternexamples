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
// The example shown here is a complicated sub-system with many different low-
// level functions.  A facade class is created to simplify access to this
// complicated sub-system by exposing a simplified set of functions for most
// common operations.
//
// In some ways, this Facade class is actually a bridge.


namespace DesignPatternExamples
{
    /// <summary>
    /// This class simplifies (to an extent) access to a sub-system that
    /// contains multiple TAP chains with each TAP chain containing multiple
    /// devices.
    /// </summary>
    /// <remarks>
    /// This facade hides the following elements:
    /// 1. Construction and initialization of the sub-system (handled in this
    ///    class's constructor).
    /// 2. The need to lock and unlock a TAP chain for each access.
    /// 3. TAP selection always selects all TAPs in a TAP chain, although
    ///    there is a method that provides finer control if needed.
    /// </remarks>
    class Facade_Class
    {
        /// <summary>
        /// Instance of the sub-system we are hiding.
        /// </summary>
        private ITAPNetwork _subsystem;
        int _numChains;

        /// <summary>
        /// Default constructor.  Handles instantiation of the sub-system.
        /// </summary>
        public Facade_Class()
        {
            _subsystem = Facade_ComplicatedSubSystemFactory.CreateInstance();
            _numChains = _subsystem.GetNumChains();
        }


        /// <summary>
        /// The number of TAP chains available from the sub-system.
        /// </summary>
        public int NumChains
        {
            get
            {
                return _numChains;
            }
        }

        /// <summary>
        /// Returns a list of all idcodes from all selected devices in the
        /// given TAP chain.
        /// </summary>
        /// <param name="chainIndex">Index of the TAP chain to access (0..NumChains-1).</param>
        /// <returns>An array holding the idcodes of all visible TAPs in the given
        /// chain.</returns>
        public uint[] GetIdcodes(int chainIndex)
        {
            uint[] idcodes = null;

            if (_subsystem.LockTAPs(chainIndex))
            {
                idcodes = _subsystem.GetIdcodes(chainIndex);
                _subsystem.UnlockTAPs(chainIndex);
            }
            return idcodes;
        }

        /// <summary>
        /// Make visible all TAPs in the given TAP chain.
        /// 
        /// Use ResetTAPs() to hide all TAPs (except the TAP controller).
        /// </summary>
        /// <param name="chainIndex">Index of the TAP chain to access (0..NumChains-1).</param>
        public void SelectTAPs(int chainIndex)
        {
            SelectTAPs(chainIndex, 0xffffffff);
        }


        /// <summary>
        /// Make visible certain TAPs in the given TAP chain.  The selectMask value
        /// has a bit set for each TAP device to make visible.
        /// </summary>
        /// <param name="chainIndex">Index of the TAP chain to access (0..NumChains-1).</param>
        /// <param name="selectMask">A bit mask where each bit corresponds to a TAP,
        /// up to the number of TAPs in the given TAP chain.  Bit 0 is ignored as the first
        /// TAP is always visible.</param>
        public void SelectTAPs(int chainIndex, uint selectMask)
        {
            if (_subsystem.LockTAPs(chainIndex))
            {
                _subsystem.SelectTAPs(chainIndex, selectMask);
                _subsystem.UnlockTAPs(chainIndex);
            }
        }


        /// <summary>
        /// Resets the given TAP chain so that all devices except the TAP
        /// controller is no longer visible.
        /// </summary>
        /// <param name="chainIndex">Index of the TAP chain to access (0..NumChains-1).</param>
        public void ResetTAPs(int chainIndex)
        {
            if (_subsystem.LockTAPs(chainIndex))
            {
                _subsystem.ResetTAPs(chainIndex);
                _subsystem.UnlockTAPs(chainIndex);
            }
        }
    }
}
