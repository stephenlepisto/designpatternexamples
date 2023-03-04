/// @file
/// @brief
/// Implementation of the @ref DesignPatternExamples_cpp::IDeviceNetworkHighLevel "IDeviceNetworkHighLevel"
/// interface representing the high-level system used in the @ref facade_pattern "Facade pattern".

#include <memory>
#include "helpers/argumentnull_error.h"
#include "Facade_Interface.h"
#include "FacadeSubsystem_Interface.h"

namespace // Anonymous
{

    /// <summary>
    /// This class wraps the IDeviceNetworkLowLevel interface and implements
    /// the high level IDeviceNetworkHighLevel interface, which is a simpler
    /// interface.  All calls on the high level interface are forwarded to the
    /// appropriate low level interface.
    /// Part of the @ref facade_pattern "Facade pattern" example.
    /// </summary>
    class DeviceNetworkHighLevel : public DesignPatternExamples_cpp::IDeviceNetworkHighLevel
    {
    private:
        /// <summary>
        /// The low level system being wrapped by this class.
        /// </summary>
        DesignPatternExamples_cpp::IDeviceNetworkLowLevel* _lowlevelSystem;

    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="system">The IDeviceNetworkLowLevel object to be
        /// wrapped by this class.</param>
        /// <exception cref="argumentnull_error">The system being wrapped
        /// cannot be null.</exception>
        DeviceNetworkHighLevel(DesignPatternExamples_cpp::IDeviceNetworkLowLevel* system)
            : _lowlevelSystem(system)
        {
            if (system == nullptr)
            {
                throw Helpers::argumentnull_error("system", "The system being wrapped cannot be null.");
            }
        }


        //====================================================================
        // IDeviceNetworkHighLevel methods
        //====================================================================

        /// @copydoc IDeviceNetworkHighLevel::NumChains()
        int NumChains() override
        {
            return _lowlevelSystem->GetNumChains();
        }

        /// @copydoc IDeviceNetworkHighLevel::GetIdcodes()
        std::vector<uint32_t> GetIdcodes(int chainIndex) override
        {
            std::vector<uint32_t> idcodes;

            if (_lowlevelSystem->LockDeviceChain(chainIndex))
            {
                idcodes = _lowlevelSystem->GetIdcodes(chainIndex);
                _lowlevelSystem->UnlockDeviceChain(chainIndex);
            }
            return idcodes;
        }

        /// @copydoc IDeviceNetworkHighLevel::EnableDevicesInDeviceChain()
        void EnableDevicesInDeviceChain(int chainIndex, uint32_t selectMask) override
        {
            if (_lowlevelSystem->LockDeviceChain(chainIndex))
            {
                _lowlevelSystem->EnableDevicesInDeviceChain(chainIndex, selectMask);
                _lowlevelSystem->UnlockDeviceChain(chainIndex);
            }
        }

        /// @copydoc IDeviceNetworkHighLevel::DisableDevicesInDeviceChain()
        void DisableDevicesInDeviceChain(int chainIndex) override
        {
            if (_lowlevelSystem->LockDeviceChain(chainIndex))
            {
                _lowlevelSystem->ResetDeviceChain(chainIndex);
                _lowlevelSystem->UnlockDeviceChain(chainIndex);
            }
        }
    };

    static std::unique_ptr<DeviceNetworkHighLevel> _instance;

} // end anonymous namespace


//########################################################################
//########################################################################


namespace DesignPatternExamples_cpp
{

    /////////////////////////////////////////////////////////////////////////
    // Function: CreateHighLevelInstance
    /////////////////////////////////////////////////////////////////////////
    IDeviceNetworkHighLevel* CreateHighLevelInstance()
    {
        if (!_instance)
        {
            IDeviceNetworkLowLevel* lowlevelSystem;
            lowlevelSystem = CreateLowLevelInstance();
            _instance = std::make_unique<DeviceNetworkHighLevel>(lowlevelSystem);
        }
        return _instance.get();
    }

} // end namespace
