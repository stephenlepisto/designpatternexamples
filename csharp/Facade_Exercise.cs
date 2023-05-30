/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Facade_Exercise "Facade_Exercise"
/// class used in the @ref facade_pattern.

using System;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Example of using the @ref facade_pattern in C#.
    /// 
    /// The Facade pattern is used when a simplified version of an
    /// interface on a complicated sub-system is needed in situations
    /// where the whole complicated sub-system does not need to be
    /// exposed.
    /// 
    /// In this example, the complicated subsystem is a representation of
    /// a device network complete with scan chains, device idcodes, and device
    /// devices that can be selected and deselected.  The Facade exposed
    /// by this complex network exposes only the scan chain, getting
    /// device idcodes based on an index into those scan chains, resetting
    /// the scan chains and selecting a device to appear in the scan
    /// chain.
    /// </summary>
    internal class Facade_Exercise
    {
        /// <summary>
        /// Helper method to present a formatted list of idcodes for a particular
        /// device chain.  The output is on a single line.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain being displayed.</param>
        /// <param name="idcodes">Array of 32-bit idcodes to be printed in hex.</param>
        void _Facade_ShowIdCodes(int chainIndex, uint[] idcodes)
        {
            Console.Write("    On chain {0}, idcodes = [ ", chainIndex);
            foreach (uint idcode in idcodes)
            {
                Console.Write("0x{0:X} ", idcode);
            }
            Console.WriteLine("]");
        }

        /// <summary>
        /// Executes the example for the @ref facade_pattern in C#.
        /// </summary>
        // ! [Using Facade in C#]
        public void Run()
        {
            Console.WriteLine();
            Console.WriteLine("Facade Exercise");

            IDeviceNetworkHighLevel deviceChainFacade = Facade_ComplicatedSubSystemFactory.CreateHighLevelInstance();
            int numChains = deviceChainFacade.NumChains;
            Console.WriteLine("  Showing idcodes of devices after a device reset (expect one device on each chain)...");
            for (int chainIndex = 0; chainIndex < numChains; ++chainIndex)
            {
                deviceChainFacade.DisableDevicesInDeviceChain(chainIndex);
                uint[] idcodes = deviceChainFacade.GetIdcodes(chainIndex);
                _Facade_ShowIdCodes(chainIndex, idcodes);
            }

            Console.WriteLine("  Showing idcodes of devices after selecting all devices...");
            for (int chainIndex = 0; chainIndex < numChains; ++chainIndex)
            {
                deviceChainFacade.EnableDevicesInDeviceChain(chainIndex, 0xffffffff);
                uint[] idcodes = deviceChainFacade.GetIdcodes(chainIndex);
                _Facade_ShowIdCodes(chainIndex, idcodes);
            }
            Console.WriteLine("  Done.");
        }
        // ! [Using Facade in C#]
    }
}
