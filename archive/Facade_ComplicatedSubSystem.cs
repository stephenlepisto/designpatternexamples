// The Facade design pattern.  See Facade_Class.cs for details.
//
// This is a "complicated" sub-system for which a facade will be provided to
// simplify the use of the sub-system.
//
// For this example, there are only three classes.  In a larger sub-system,
// there could be a dozen or more classes and interfaces representing a truly
// dizzying array of functionality.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DesignPatternExamples
{
    /// <summary>
    /// Identifies the type of TAPs that can appear in a TAP chain.
    /// </summary>
    public enum TAPTypes
    {
        /// <summary>
        /// TAP controller.  This is always visible.
        /// </summary>
        CLTAP,
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


    /// <summary>
    /// Represents a single TAP.
    /// </summary>
    public class TAPNode
    {
        /// <summary>
        /// Whether the TAP is visible in the TAP chain.
        /// </summary>
        public bool Visible;
        
        /// <summary>
        /// Name of this TAP.
        /// </summary>
        public string Name;

        /// <summary>
        /// The idcode for this TAP.
        /// </summary>
        public uint Idcode;

        /// <summary>
        /// A value from the TAPTypes enumeration identifying the type of the
        /// TAP.
        /// </summary>
        public TAPTypes TAPType;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="name">Name to use.</param>
        /// <param name="idcode">idcode for the TAP.</param>
        /// <param name="tapType">Value from the TAPTypes enumeration.</param>
        /// <param name="initiallyVisible">true if initially visible; otherwise false.</param>
        public TAPNode(string name, uint idcode, TAPTypes tapType, bool initiallyVisible)
        {
            Name = name;
            Idcode = idcode;
            TAPType = tapType;
            Visible = initiallyVisible;
        }
    }


    /// <summary>
    /// Represents a TAP chain, which is a collection of TAPNode objects.
    /// </summary>
    public class TAPChain
    {
        /// <summary>
        /// The list of TAPNodes on this TAP chain.
        /// </summary>
        private List<TAPNode> _nodes = new List<TAPNode>();

        /// <summary>
        /// The Name of this TAP chain.
        /// </summary>
        public string Name;

        /// <summary>
        /// Whether this TAP chain is locked for access.
        /// </summary>
        public bool IsLocked;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="name">Name of this TAP chain.</param>
        public TAPChain(string name)
        {
            Name = name;
        }

        /// <summary>
        /// Helper method to show or hide TAPs on the TAP chain.
        /// </summary>
        /// <param name="nodeSelectMask">A bit mask where the position of each bit
        /// corresponds to a device in the TAP chain, with bit 0 being the first TAP,
        /// bit 1 being the second TAP, and so on.</param>
        /// <param name="makeVisible">true if the TAP is to be made visible on the
        /// TAP chain; otherwise false, the TAP cannot be seen on the TAP chain.</param>
        private void _ShowHideNodes(uint nodeSelectMask, bool makeVisible)
        {
            uint bitMask = 0x2; // bit 0 is always the CLTAP and is always selected
            int numNodes = _nodes.Count;

            // Start at the device after the CLTAP
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
        /// Helper method to add a TAPNode to the TAP chain.  TAPNode objects
        /// that are of TapTypes.CLTAP are always inserted as the first TAP in
        /// the TAP chain, with the assumption there is only one CLTAP in a
        /// given TAP chain (this is not actually enforced, though).
        /// </summary>
        /// <param name="node">A TAPNode object to add to the tap chain.</param>
        internal void AddNode(TAPNode node)
        {
            if (_nodes.Count > 0 && node.TAPType == TAPTypes.CLTAP)
            {
                // CLTAP always goes at the start of the list.
                _nodes.Insert(0, node);
            }
            else
            {
                _nodes.Add(node);
            }
        }


        /// <summary>
        /// Resets the TAP chain so that all TAPs that are not CLTAPs are no
        /// longer visible in the TAP chain.
        /// </summary>
        public void ResetVisibility()
        {
            foreach (TAPNode node in _nodes)
            {
                if (node.TAPType != TAPTypes.CLTAP)
                {
                    node.Visible = false;
                }
            }
        }

        /// <summary>
        /// Make visible one or more TAPs in the TAP chain.
        /// </summary>
        /// <param name="nodeSelectMask">a bit mask specifying which TAP or TAPs
        /// to make visible, where bit 0 is the first TAP, bit 1 is the second, etc.
        /// Bit 0 is ignored as the first TAP is always visible.</param>
        public void SelectNodes(uint nodeSelectMask)
        {
            _ShowHideNodes(nodeSelectMask, true);
        }

        /// <summary>
        /// Make invisible one or more TAPs in the TAP chain.
        /// </summary>
        /// <param name="nodeSelectMask">a bit mask specifying which TAP or TAPs
        /// to hide, where bit 0 is the first TAP, bit 1 is the second, etc.
        /// Bit 0 is ignored as the first TAP is always visible.</param>
        public void DeselectNodes(uint nodeSelectMask)
        {
            _ShowHideNodes(nodeSelectMask, false);
        }


        /// <summary>
        /// Retrieve a list of idcodes for all TAPs that are visible in
        /// the TAP chain.
        /// </summary>
        /// <returns>Returns an array of uints corresponding to the idcodes of
        /// each visible TAP.  The first idcode corresponds to the first visible
        /// TAP.</returns>
        public uint[] GetIdCodesForVisibleNodes()
        {
            List<uint> idcodes = new List<uint>();

            foreach(TAPNode node in _nodes)
            {
                if (node.Visible)
                {
                    idcodes.Add(node.Idcode);
                }
            }

            return idcodes.ToArray();
        }
    }


    /// <summary>
    /// Represents some kind of system that contains multiple TAP chains.
    /// </summary>
    /// <remarks>
    /// The following operations are available:
    ///  - GetNumChains()
    ///  - LockTAPs()
    ///  - UnlockTAPs()
    ///  - ResetTAPs()
    ///  - SelectTAPs()
    ///  - DeselectTAPs()
    ///  - GetIdcodes()
    /// </remarks>
    public class Facade_ComplicatedSubSystem : ITAPNetwork
    {
        /// <summary>
        /// The list of TAP chains.  In this case, there are two.
        /// </summary>
        private TAPChain[] _tapChains = { new TAPChain("CHAIN0"), new TAPChain("CHAIN1") };

        /// <summary>
        /// Class factory for the sub-system class.
        /// </summary>
        /// <returns>Returns a new instance of the class.</returns>
        public static ITAPNetwork CreateInstance()
        {
            return new Facade_ComplicatedSubSystem();
        }

        /// <summary>
        /// (private) Constructor.  Sets up the TAP chains.
        /// </summary>
        private Facade_ComplicatedSubSystem()
        {
            _tapChains[0].AddNode(new TAPNode("DDD_CLTAPC0", 0x10101010, TAPTypes.CLTAP, true));
            _tapChains[0].AddNode(new TAPNode("DDD_CORE0", 0x20202020, TAPTypes.CORE, false));
            _tapChains[0].AddNode(new TAPNode("DDD_GTE0", 0x30303030, TAPTypes.GTE, false));
            
            _tapChains[1].AddNode(new TAPNode("DDD_CLTAPC1", 0x10101011, TAPTypes.CLTAP, true));
            _tapChains[1].AddNode(new TAPNode("DDD_PCH0", 0x40404040, TAPTypes.PCH, false));
            _tapChains[1].AddNode(new TAPNode("DDD_PMC0", 0x50505050, TAPTypes.PMC, false));
        }

        #region ITapNetwork methods
        /// <summary>
        /// Retrieve the number of TAP chains.
        /// </summary>
        /// <returns>Returns the number of TAP chains</returns>
        public int GetNumChains()
        {
            return _tapChains.Length;
        }

        /// <summary>
        /// Lock the specified TAP chain to indicate exclusive access is
        /// desired.
        /// </summary>
        /// <param name="chainIndex">The index of the TAP chain to access (0..n-1).</param>
        /// <returns>Returns true if the TAP chain was successfully locked; otherwise,
        /// returns false (chain index out of range or the TAP chain is already locked)</returns>
        public bool LockTAPs(int chainIndex)
        {
            bool locked = false;

            if (chainIndex >= 0 && chainIndex < _tapChains.Length)
            {
                if (!_tapChains[chainIndex].IsLocked)
                {
                    _tapChains[chainIndex].IsLocked = true;
                    locked = true;
                }
            }

            return locked;
        }

        /// <summary>
        /// Unlock the specified TAP chain to indicate exclusive access is no
        /// longer desired.
        /// </summary>
        /// <param name="chainIndex">The index of the TAP chain to access (0..n-1).</param>
        /// <returns>Returns true if the TAP chain was successfully unlocked; otherwise,
        /// returns false (chain index out of range or the TAP chain is already unlocked)</returns>
        public bool UnlockTAPs(int chainIndex)
        {
            bool unlocked = false;

            if (chainIndex >= 0 && chainIndex < _tapChains.Length)
            {
                if (_tapChains[chainIndex].IsLocked)
                {
                    _tapChains[chainIndex].IsLocked = false;
                    unlocked = true;
                }
            }

            return unlocked;
        }

        /// <summary>
        /// Reset the visibility of all TAPs on the given TAP chain so that
        /// all TAPs except the first are not visible.
        /// </summary>
        /// <param name="chainIndex">The index of the TAP chain to access (0..n-1).</param>
        public void ResetTAPs(int chainIndex)
        {
            if (chainIndex >= 0 && chainIndex < _tapChains.Length)
            {
                _tapChains[chainIndex].ResetVisibility();
            }
        }

        /// <summary>
        /// Select one or more TAPs in the given TAP chain so those TAPs are
        /// visible.
        /// </summary>
        /// <param name="chainIndex">The index of the TAP chain to access (0..n-1).</param>
        /// <param name="tapSelectMask">A bit mask indicating which TAPs to make
        /// visible, with bit 0 corresponding to the first TAP, bit 1 corresponding
        /// to the second TAP, etc.  Bit 0 is ignored as the first TAP is always
        /// visible.</param>
        public void SelectTAPs(int chainIndex, uint tapSelectMask)
        {
            if (chainIndex >= 0 && chainIndex < _tapChains.Length)
            {
                _tapChains[chainIndex].SelectNodes(tapSelectMask);
            }
        }

        /// <summary>
        /// Deselect one or more TAPs in the given TAP chain so those TAPs are
        /// no longer visible.
        /// </summary>
        /// <param name="chainIndex">The index of the TAP chain to access (0..n-1).</param>
        /// <param name="tapSelectMask">A bit mask indicating which TAPs to make
        /// invisible, with bit 0 corresponding to the first TAP, bit 1 corresponding
        /// to the second TAP, etc.  Bit 0 is ignored as the first TAP is always
        /// visible.</param>
        public void DeselectTAPs(int chainIndex, uint tapSelectMask)
        {
            if (chainIndex >= 0 && chainIndex < _tapChains.Length)
            {
                _tapChains[chainIndex].DeselectNodes(tapSelectMask);
            }
        }

        /// <summary>
        /// Retrieve a list of idcodes for each TAP in the given TAP chain
        /// that is visible.
        /// </summary>
        /// <param name="chainIndex">The index of the TAP chain to access (0..n-1).</param>
        /// <returns>An array of uints holding the idcodes for each TAP, with the
        /// first idcode corresponding to the first visible TAP.</returns>
        public uint[] GetIdcodes(int chainIndex)
        {
            uint[] idcodes = null;

            if (chainIndex >= 0 && chainIndex < _tapChains.Length)
            {
                idcodes = _tapChains[chainIndex].GetIdCodesForVisibleNodes();
            }
            return idcodes;
        }
        #endregion
    }


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
        static ITAPNetwork _instance;


        /// <summary>
        /// Class factory for a singleton instance of the sub-system class.
        /// </summary>
        /// <returns>Returns a singleton instance of the class.</returns>
        public static ITAPNetwork CreateInstance()
        {
            if (_instance == null)
            {
                _instance = Facade_ComplicatedSubSystem.CreateInstance();
            }
            return _instance;
        }
    }
}
