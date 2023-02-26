#include <memory>
#include <string>

#include "FacadeSubsystem_Interface.h"
#include "Facade_Interface.h"


namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Represents a single device.
    /// </summary>
    struct DeviceNode
    {
        /// <summary>
        /// Whether the device is visible in the device chain.
        /// </summary>
        bool Visible;

        /// <summary>
        /// Name of this device.
        /// </summary>
        std::string Name;

        /// <summary>
        /// The idcode for this device.
        /// </summary>
        uint32_t Idcode;

        /// <summary>
        /// A value from the DeviceTypes enumeration identifying the type of the
        /// device.
        /// </summary>
        DeviceTypes DeviceType;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="name">Name to use.</param>
        /// <param name="idcode">idcode for the device.</param>
        /// <param name="tapType">Value from the DeviceTypes enumeration.</param>
        /// <param name="initiallyVisible">true if initially visible; otherwise false.</param>
        DeviceNode(std::string name, uint32_t idcode, DeviceTypes tapType, bool initiallyVisible)
            : Name(name)
            , Idcode(idcode)
            , DeviceType(tapType)
            , Visible(initiallyVisible)
        {
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents a device chain, which is a collection of DeviceNode objects.
    /// </summary>
    class DeviceChain
    {
    private:
        /// <summary>
        /// The list of TAPNodes on this device chain.
        /// </summary>
        std::vector<DeviceNode> _nodes;

    public:
        /// <summary>
        /// The Name of this device chain.
        /// </summary>
        std::string Name;

        /// <summary>
        /// Whether this device chain is locked for access.
        /// </summary>
        bool IsLocked;

    private:

        /// <summary>
        /// Helper method to show or hide devices on the device chain.
        /// </summary>
        /// <param name="nodeSelectMask">A bit mask where the position of each bit
        /// corresponds to a device in the device chain, with bit 0 being the first device,
        /// bit 1 being the second device, and so on.</param>
        /// <param name="makeVisible">true if the device is to be made visible on the
        /// device chain; otherwise false, the device cannot be seen on the device chain.</param>
        void _ShowHideNodes(uint32_t nodeSelectMask, bool makeVisible)
        {
            uint32_t bitMask = 0x2; // bit 0 is always the DEVICECONTROLLER and is always selected
            size_t numNodes = _nodes.size();

            // Start at the device after the DEVICECONTROLLER
            for (size_t index = 1; index < numNodes; ++index)
            {
                if ((bitMask & nodeSelectMask) != 0)
                {
                    _nodes[index].Visible = makeVisible;
                }
                bitMask <<= 1;
                if (bitMask == 0)
                {
                    // We don't allow more than 32 devices
                    break;
                }
            }
        }

    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="name">Name of this device chain.</param>
        DeviceChain(std::string name)
            : Name(name)
            , IsLocked(false)
        {
        }


        /// <summary>
        /// Helper method to add a DeviceNode to the device chain.  DeviceNode
        /// objects that are of DeviceTypes::DEVICECONTROLLER are always
        /// inserted as the first device in the device chain, with the
        /// assumption there is only one DEVICECONTROLLER in a given device
        /// chain (this is not actually enforced, though).
        /// </summary>
        /// <param name="node">A DeviceNode object to add to the device chain.</param>
        void AddNode(DeviceNode node)
        {
            if (_nodes.size() > 0 && node.DeviceType == DeviceTypes::DEVICECONTROLLER)
            {
                // DEVICECONTROLLER always goes at the start of the list.
                _nodes.insert(std::begin(_nodes), node);
            }
            else
            {
                _nodes.push_back(node);
            }
        }


        /// <summary>
        /// Resets the device chain so that all devices that are not CLdevices are no
        /// longer visible in the device chain.
        /// </summary>
        void ResetVisibility()
        {
            for(DeviceNode node : _nodes)
            {
                if (node.DeviceType != DeviceTypes::DEVICECONTROLLER)
                {
                    node.Visible = false;
                }
            }
        }

        /// <summary>
        /// Make visible one or more devices in the device chain.
        /// </summary>
        /// <param name="nodeSelectMask">a bit mask specifying which device or devices
        /// to make visible, where bit 0 is the first device, bit 1 is the second, etc.
        /// Bit 0 is ignored as the first device is always visible.</param>
        void SelectNodes(uint32_t nodeSelectMask)
        {
            _ShowHideNodes(nodeSelectMask, true);
        }

        /// <summary>
        /// Make invisible one or more devices in the device chain.
        /// </summary>
        /// <param name="nodeSelectMask">a bit mask specifying which device or devices
        /// to hide, where bit 0 is the first device, bit 1 is the second, etc.
        /// Bit 0 is ignored as the first device is always visible.</param>
        void DeselectNodes(uint32_t nodeSelectMask)
        {
            _ShowHideNodes(nodeSelectMask, false);
        }


        /// <summary>
        /// Retrieve a list of idcodes for all devices that are visible in
        /// the device chain.
        /// </summary>
        /// <returns>Returns an array of uints corresponding to the idcodes of
        /// each visible device.  The first idcode corresponds to the first visible
        /// device.</returns>
        std::vector<uint32_t> GetIdCodesForVisibleNodes()
        {
            std::vector<uint32_t> idcodes;

            for(DeviceNode node : _nodes)
            {
                if (node.Visible)
                {
                    idcodes.push_back(node.Idcode);
                }
            }

            return idcodes;
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents some kind of system that contains multiple device chains.
    /// </summary>
    /// <remarks>
    /// The following operations are available:
    ///  - GetNumChains()
    ///  - LockDevices()
    ///  - UnlockDevices()
    ///  - ResetDevices()
    ///  - SelectDevices()
    ///  - DeselectDevices()
    ///  - GetIdcodes()
    /// </remarks>
    class Facade_ComplicatedSubSystem : public IDeviceNetworkLowLevel
    {
    public:
        /// <summary>
        /// The list of device chains.  In this case, there are two.
        /// </summary>
        std::vector<DeviceChain> _deviceChains { DeviceChain("CHAIN0"), DeviceChain("CHAIN1") };

        /// <summary>
        /// (private) Constructor.  Sets up the device chains.
        /// </summary>
        Facade_ComplicatedSubSystem()
        {
            _deviceChains[0].AddNode(DeviceNode("DDD_DEVCTRL0", 0x10101010, DeviceTypes::DEVICECONTROLLER, true));
            _deviceChains[0].AddNode(DeviceNode("DDD_CORE0", 0x20202020, DeviceTypes::CORE, false));
            _deviceChains[0].AddNode(DeviceNode("DDD_GTE0", 0x30303030, DeviceTypes::GTE, false));

            _deviceChains[1].AddNode(DeviceNode("DDD_DEVCTRL1", 0x10101011, DeviceTypes::DEVICECONTROLLER, true));
            _deviceChains[1].AddNode(DeviceNode("DDD_PCH0", 0x40404040, DeviceTypes::PCH, false));
            _deviceChains[1].AddNode(DeviceNode("DDD_PMC0", 0x50505050, DeviceTypes::PMC, false));
        }

    private:
        //====================================================================
        // IDeviceNetworkLowLevel methods
        //====================================================================
        /// <summary>
        /// Retrieve the number of device chains.
        /// </summary>
        /// <returns>Returns the number of device chains</returns>
        int GetNumChains()
        {
            return static_cast<int>(_deviceChains.size());
        }

        /// <summary>
        /// Lock the specified device chain to indicate exclusive access is
        /// desired.
        /// </summary>
        /// <param name="chainIndex">The index of the device chain to access (0..n-1).</param>
        /// <returns>Returns true if the device chain was successfully locked; otherwise,
        /// returns false (chain index out of range or the device chain is already locked)</returns>
        bool LockDeviceChain(int chainIndex) override
        {
            bool locked = false;

            if (chainIndex >= 0 && chainIndex < _deviceChains.size())
            {
                if (!_deviceChains[chainIndex].IsLocked)
                {
                    _deviceChains[chainIndex].IsLocked = true;
                    locked = true;
                }
            }

            return locked;
        }

        /// <summary>
        /// Unlock the specified device chain to indicate exclusive access is no
        /// longer desired.
        /// </summary>
        /// <param name="chainIndex">The index of the device chain to access (0..n-1).</param>
        /// <returns>Returns true if the device chain was successfully unlocked; otherwise,
        /// returns false (chain index out of range or the device chain is already unlocked)</returns>
        bool UnlockDeviceChain(int chainIndex) override
        {
            bool unlocked = false;

            if (chainIndex >= 0 && chainIndex < _deviceChains.size())
            {
                if (_deviceChains[chainIndex].IsLocked)
                {
                    _deviceChains[chainIndex].IsLocked = false;
                    unlocked = true;
                }
            }

            return unlocked;
        }

        /// <summary>
        /// Reset the visibility of all devices on the given device chain so that
        /// all devices except the first are not visible.
        /// </summary>
        /// <param name="chainIndex">The index of the device chain to access (0..n-1).</param>
        void ResetDeviceChain(int chainIndex) override
        {
            if (chainIndex >= 0 && chainIndex < _deviceChains.size())
            {
                _deviceChains[chainIndex].ResetVisibility();
            }
        }

        /// <summary>
        /// Select one or more devices in the given device chain so those devices are
        /// visible.
        /// </summary>
        /// <param name="chainIndex">The index of the device chain to access (0..n-1).</param>
        /// <param name="deviceselectMask">A bit mask indicating which devices to make
        /// visible, with bit 0 corresponding to the first device, bit 1 corresponding
        /// to the second device, etc.  Bit 0 is ignored as the first device is always
        /// visible.</param>
        void EnableDevicesInDeviceChain(int chainIndex, uint32_t deviceselectMask) override
        {
            if (chainIndex >= 0 && chainIndex < _deviceChains.size())
            {
                _deviceChains[chainIndex].SelectNodes(deviceselectMask);
            }
        }

        /// <summary>
        /// Deselect one or more devices in the given device chain so those devices are
        /// no longer visible.
        /// </summary>
        /// <param name="chainIndex">The index of the device chain to access (0..n-1).</param>
        /// <param name="deviceselectMask">A bit mask indicating which devices to make
        /// invisible, with bit 0 corresponding to the first device, bit 1 corresponding
        /// to the second device, etc.  Bit 0 is ignored as the first device is always
        /// visible.</param>
        void DisableDevicesInDeviceChain(int chainIndex, uint32_t deviceselectMask) override
        {
            if (chainIndex >= 0 && chainIndex < _deviceChains.size())
            {
                _deviceChains[chainIndex].DeselectNodes(deviceselectMask);
            }
        }

        /// <summary>
        /// Retrieve a list of idcodes for each device in the given device chain
        /// that is visible.
        /// </summary>
        /// <param name="chainIndex">The index of the device chain to access (0..n-1).</param>
        /// <returns>An array of uints holding the idcodes for each device, with the
        /// first idcode corresponding to the first visible device.</returns>
        std::vector<uint32_t> GetIdcodes(int chainIndex) override
        {
            std::vector<uint32_t> idcodes;

            if (chainIndex >= 0 && chainIndex < _deviceChains.size())
            {
                idcodes = _deviceChains[chainIndex].GetIdCodesForVisibleNodes();
            }
            return idcodes;
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// A singleton instance of the sub-system.
    /// </summary>
    static std::unique_ptr<Facade_ComplicatedSubSystem> _instance;

    /// <summary>
    /// Class factory for a singleton instance of the sub-system class.
    /// </summary>
    /// <returns>Returns a singleton instance of the class.</returns>
    IDeviceNetworkLowLevel* CreateLowLevelInstance()
    {
        if (!_instance)
        {
            _instance = std::make_unique<Facade_ComplicatedSubSystem>();
        }
        return _instance.get();
    }

} // end namespace
