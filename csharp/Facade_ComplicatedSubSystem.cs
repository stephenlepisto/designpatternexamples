// The Facade design pattern.  See Facade_Interface.cs for details.
//
// This is a "complicated" sub-system that exposes a low level interface and
// a high level interface (the facade).  The Facade_ComplicatedSubSystem class
// implements both interfaces.
//
// For this example, there are only three classes.  In a larger sub-system,
// there could be a dozen or more classes and interfaces representing a truly
// dizzying array of functionality.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Identifies the type of devices that can appear in a device chain.
    /// </summary>
    public enum DeviceTypes
    {
        /// <summary>
        /// device controller.  This is always visible.
        /// </summary>
        DEVICECONTROLLER,
        /// <summary>
        /// Core device
        /// </summary>
        CORE, 
        /// <summary>
        /// GTE device
        /// </summary>
        GTE,
        /// <summary>
        /// PCH device
        /// </summary>
        PCH,
        /// <summary>
        /// PMC device
        /// </summary>
        PMC,
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents a single device.
    /// </summary>
    public class DeviceNode
    {
        /// <summary>
        /// Whether the device is visible in the device chain.
        /// </summary>
        public bool Visible;
        
        /// <summary>
        /// Name of this device.
        /// </summary>
        public string Name;

        /// <summary>
        /// The idcode for this device.
        /// </summary>
        public uint Idcode;

        /// <summary>
        /// A value from the DeviceTypes enumeration identifying the type of the
        /// device.
        /// </summary>
        public DeviceTypes DeviceType;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="name">Name to use.</param>
        /// <param name="idcode">idcode for the device.</param>
        /// <param name="tapType">Value from the DeviceTypes enumeration.</param>
        /// <param name="initiallyVisible">true if initially visible; otherwise false.</param>
        public DeviceNode(string name, uint idcode, DeviceTypes tapType, bool initiallyVisible)
        {
            Name = name;
            Idcode = idcode;
            DeviceType = tapType;
            Visible = initiallyVisible;
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents a device chain, which is a collection of DeviceNode objects.
    /// </summary>
    public class DeviceChain
    {
        /// <summary>
        /// The list of TAPNodes on this device chain.
        /// </summary>
        private List<DeviceNode> _nodes = new List<DeviceNode>();

        /// <summary>
        /// The Name of this device chain.
        /// </summary>
        public string Name;

        /// <summary>
        /// Whether this device chain is locked for access.
        /// </summary>
        public bool IsLocked;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="name">Name of this device chain.</param>
        public DeviceChain(string name)
        {
            Name = name;
        }

        /// <summary>
        /// Helper method to show or hide devices on the device chain.
        /// </summary>
        /// <param name="nodeSelectMask">A bit mask where the position of each bit
        /// corresponds to a device in the device chain, with bit 0 being the first device,
        /// bit 1 being the second device, and so on.</param>
        /// <param name="makeVisible">true if the device is to be made visible on the
        /// device chain; otherwise false, the device cannot be seen on the device chain.</param>
        private void _ShowHideNodes(uint nodeSelectMask, bool makeVisible)
        {
            uint bitMask = 0x2; // bit 0 is always the DEVICECONTROLLER and is always selected
            int numNodes = _nodes.Count;

            // Start at the device after the DEVICECONTROLLER
            for (int index = 1; index < numNodes; ++index)
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


        /// <summary>
        /// Helper method to add a DeviceNode to the device chain.  DeviceNode objects
        /// that are of DeviceTypes.DEVICECONTROLLER are always inserted as the first device in
        /// the device chain, with the assumption there is only one DEVICECONTROLLER in a
        /// given device chain (this is not actually enforced, though).
        /// </summary>
        /// <param name="node">A DeviceNode object to add to the device chain.</param>
        internal void AddNode(DeviceNode node)
        {
            if (_nodes.Count > 0 && node.DeviceType == DeviceTypes.DEVICECONTROLLER)
            {
                // DEVICECONTROLLER always goes at the start of the list.
                _nodes.Insert(0, node);
            }
            else
            {
                _nodes.Add(node);
            }
        }


        /// <summary>
        /// Resets the device chain so that all devices that are not CLdevices are no
        /// longer visible in the device chain.
        /// </summary>
        public void ResetVisibility()
        {
            foreach (DeviceNode node in _nodes)
            {
                if (node.DeviceType != DeviceTypes.DEVICECONTROLLER)
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
        public void SelectNodes(uint nodeSelectMask)
        {
            _ShowHideNodes(nodeSelectMask, true);
        }

        /// <summary>
        /// Make invisible one or more devices in the device chain.
        /// </summary>
        /// <param name="nodeSelectMask">a bit mask specifying which device or devices
        /// to hide, where bit 0 is the first device, bit 1 is the second, etc.
        /// Bit 0 is ignored as the first device is always visible.</param>
        public void DeselectNodes(uint nodeSelectMask)
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
        public uint[] GetIdCodesForVisibleNodes()
        {
            List<uint> idcodes = new List<uint>();

            foreach(DeviceNode node in _nodes)
            {
                if (node.Visible)
                {
                    idcodes.Add(node.Idcode);
                }
            }

            return idcodes.ToArray();
        }
    }


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
    public class Facade_ComplicatedSubSystem : IDeviceNetworkLowLevel, IDeviceNetworkHighLevel
    {
        /// <summary>
        /// The list of device chains.  In this case, there are two.
        /// </summary>
        private DeviceChain[] _deviceChains = { new DeviceChain("CHAIN0"), new DeviceChain("CHAIN1") };

        /// <summary>
        /// Class factory for the sub-system class.
        /// </summary>
        /// <returns>Returns a new instance of the class.</returns>
        public static IDeviceNetworkLowLevel CreateInstance()
        {
            return new Facade_ComplicatedSubSystem();
        }

        /// <summary>
        /// (private) Constructor.  Sets up the device chains.
        /// </summary>
        private Facade_ComplicatedSubSystem()
        {
            _deviceChains[0].AddNode(new DeviceNode("DDD_DEVCTRL0", 0x10101010, DeviceTypes.DEVICECONTROLLER, true));
            _deviceChains[0].AddNode(new DeviceNode("DDD_CORE0", 0x20202020, DeviceTypes.CORE, false));
            _deviceChains[0].AddNode(new DeviceNode("DDD_GTE0", 0x30303030, DeviceTypes.GTE, false));
            
            _deviceChains[1].AddNode(new DeviceNode("DDD_DEVCTRL1", 0x10101011, DeviceTypes.DEVICECONTROLLER, true));
            _deviceChains[1].AddNode(new DeviceNode("DDD_PCH0", 0x40404040, DeviceTypes.PCH, false));
            _deviceChains[1].AddNode(new DeviceNode("DDD_PMC0", 0x50505050, DeviceTypes.PMC, false));
        }


        //====================================================================
        // ITAPNetworkLowLevel methods
        //====================================================================
        #region ITAPNetworkLowLevel methods
        /// <summary>
        /// Retrieve the number of device chains.
        /// </summary>
        /// <returns>Returns the number of device chains</returns>
        int IDeviceNetworkLowLevel.GetNumChains()
        {
            return _deviceChains.Length;
        }

        /// <summary>
        /// Lock the specified device chain to indicate exclusive access is
        /// desired.
        /// </summary>
        /// <param name="chainIndex">The index of the device chain to access (0..n-1).</param>
        /// <returns>Returns true if the device chain was successfully locked; otherwise,
        /// returns false (chain index out of range or the device chain is already locked)</returns>
        bool IDeviceNetworkLowLevel.LockDeviceChain(int chainIndex)
        {
            bool locked = false;

            if (chainIndex >= 0 && chainIndex < _deviceChains.Length)
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
        bool IDeviceNetworkLowLevel.UnlockDeviceChain(int chainIndex)
        {
            bool unlocked = false;

            if (chainIndex >= 0 && chainIndex < _deviceChains.Length)
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
        void IDeviceNetworkLowLevel.ResetDeviceChain(int chainIndex)
        {
            if (chainIndex >= 0 && chainIndex < _deviceChains.Length)
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
        void IDeviceNetworkLowLevel.EnableDevicesInDeviceChain(int chainIndex, uint deviceselectMask)
        {
            if (chainIndex >= 0 && chainIndex < _deviceChains.Length)
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
        void IDeviceNetworkLowLevel.DisableDevicesInDeviceChain(int chainIndex, uint deviceselectMask)
        {
            if (chainIndex >= 0 && chainIndex < _deviceChains.Length)
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
        uint[] IDeviceNetworkLowLevel.GetIdcodes(int chainIndex)
        {
            uint[] idcodes = null;

            if (chainIndex >= 0 && chainIndex < _deviceChains.Length)
            {
                idcodes = _deviceChains[chainIndex].GetIdCodesForVisibleNodes();
            }
            return idcodes;
        }
        #endregion


        //====================================================================
        // IDeviceNetworkHighLevel methods
        //====================================================================
        #region ITAPNetworkHighLevel methods

        /// <summary>
        /// The number of device chains available from the sub-system.
        /// </summary>
        int IDeviceNetworkHighLevel.NumChains
        {
            get
            {
                return ((IDeviceNetworkLowLevel)this).GetNumChains();
            }
        }

        /// <summary>
        /// Returns a list of all idcodes from all selected devices in the
        /// given device chain.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain to access (0..NumChains-1).</param>
        /// <returns>An array holding the idcodes of all visible devices in the given
        /// chain.</returns>
        uint[] IDeviceNetworkHighLevel.GetIdcodes(int chainIndex)
        {
            uint[] idcodes = null;

            if (((IDeviceNetworkLowLevel)this).LockDeviceChain(chainIndex))
            {
                idcodes = ((IDeviceNetworkLowLevel)this).GetIdcodes(chainIndex);
                ((IDeviceNetworkLowLevel)this).UnlockDeviceChain(chainIndex);
            }
            return idcodes;
        }

        /// <summary>
        /// Make visible certain devices in the given device chain.  The selectMask value
        /// has a bit set for each device device to make visible.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain to access (0..NumChains-1).</param>
        /// <param name="selectMask">A bit mask where each bit corresponds to a device,
        /// up to the number of devices in the given device chain.  Bit 0 is ignored as the first
        /// device is always visible.</param>
        void IDeviceNetworkHighLevel.EnableDevicesInDeviceChain(int chainIndex, uint selectMask)
        {
            if (((IDeviceNetworkLowLevel)this).LockDeviceChain(chainIndex))
            {
                ((IDeviceNetworkLowLevel)this).EnableDevicesInDeviceChain(chainIndex, selectMask);
                ((IDeviceNetworkLowLevel)this).UnlockDeviceChain(chainIndex);
            }
        }

        /// <summary>
        /// Resets the given device chain so that all devices except the device
        /// controller is no longer visible.
        /// </summary>
        /// <param name="chainIndex">Index of the device chain to access (0..NumChains-1).</param>
        void IDeviceNetworkHighLevel.DisableDevicesInDeviceChain(int chainIndex)
        {
            if (((IDeviceNetworkLowLevel)this).LockDeviceChain(chainIndex))
            {
                ((IDeviceNetworkLowLevel)this).ResetDeviceChain(chainIndex);
                ((IDeviceNetworkLowLevel)this).UnlockDeviceChain(chainIndex);
            }
        }
        #endregion
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Class factory for the complicated sub-system class.
    /// </summary>
    /// <remarks>
    /// Hides the details of constructing the complicated sub-system and
    /// enforces a singleton nature on the instance of the sub-system.
    /// </remarks>
    public static class Facade_ComplicatedSubSystemFactory
    {
        /// <summary>
        /// A singleton instance of the sub-system.
        /// </summary>
        static IDeviceNetworkLowLevel _instance;


        /// <summary>
        /// Class factory for a singleton instance of the sub-system class.
        /// </summary>
        /// <returns>Returns a singleton instance of the class.</returns>
        public static IDeviceNetworkLowLevel CreateLowLevelInstance()
        {
            if (_instance == null)
            {
                _instance = Facade_ComplicatedSubSystem.CreateInstance();
            }
            return _instance;
        }

        /// <summary>
        /// Class factory for a singleton instance of the sub-system class.
        /// </summary>
        /// <returns>Returns a singleton instance of the class.</returns>
        public static IDeviceNetworkHighLevel CreateHighLevelInstance()
        {
            if (_instance == null)
            {
                _instance = Facade_ComplicatedSubSystem.CreateInstance();
            }
            return (IDeviceNetworkHighLevel)_instance;
        }
    }
}
