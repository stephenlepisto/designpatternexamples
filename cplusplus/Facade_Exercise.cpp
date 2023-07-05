
/// @file
/// @brief
/// Implementation of the Facade_Exercise() function as used in the 
/// @ref facade_pattern.

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <iostream>

#include "Facade_Exercise.h"
#include "FacadeSubsystem_Interface.h"
#include "Facade_Interface.h"

namespace // Anonymous
{
    using namespace DesignPatternExamples_cpp;
    
    /// <summary>
    /// Helper method to present a formatted list of idcodes for a particular
    /// device chain.  The output is on a single line.
    /// </summary>
    /// <param name="chainIndex">Index of the device chain being displayed.</param>
    /// <param name="idcodes">Array of 32-bit idcodes to be printed in hex.</param>
    void _Facade_ShowIdCodes(int chainIndex, const std::vector<uint32_t>& idcodes)
    {
        std::cout << std::format("    On chain {0}, idcodes = [ ", chainIndex);
        for (uint32_t idcode : idcodes)
        {
            std::cout << std::format("0x{0:X} ", idcode);
        }
        std::cout << "]" << std::endl;
    }

} // end namespace Anonmyous


namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Example of using the @ref facade_pattern "Facade" design pattern.
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
    // ! [Using Facade in C++]
    void Facade_Exercise()
    {
        std::cout << std::endl;
        std::cout << "Facade Exercise" << std::endl;

        IDeviceNetworkHighLevel* deviceChainFacade = CreateHighLevelInstance();
        int numChains = deviceChainFacade->NumChains();
        std::cout
            << "  Showing idcodes of devices after a device reset (expect one device on each chain)..."
            << std::endl;
        for (int chainIndex = 0; chainIndex < numChains; ++chainIndex)
        {
            deviceChainFacade->DisableDevicesInDeviceChain(chainIndex);
            std::vector<uint32_t> idcodes = deviceChainFacade->GetIdcodes(chainIndex);
            _Facade_ShowIdCodes(chainIndex, idcodes);
        }

        std::cout << "  Showing idcodes of devices after selecting all devices..."
            << std::endl;
        for (int chainIndex = 0; chainIndex < numChains; ++chainIndex)
        {
            deviceChainFacade->EnableDevicesInDeviceChain(chainIndex, 0xffffffff);
            std::vector<uint32_t> idcodes = deviceChainFacade->GetIdcodes(chainIndex);
            _Facade_ShowIdCodes(chainIndex, idcodes);
        }

        std::cout << "  Done." << std::endl;
    }
    // ! [Using Facade in C++]

} // end namespace
