/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.Visitor "Visitor" base class,
/// the @ref DesignPatternExamples_csharp.Visitor_Shop "Visitor_Shop" base class,
/// and the various "shop" classes used in the @ref visitor_pattern "Visitor pattern".

using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Text;
using System.Xml.Serialization;

namespace DesignPatternExamples_csharp
{

    /// <summary>
    /// All visitors must implement this base class and then override one or
    /// more of the VisitXXX() methods, depending on which shop type the
    /// visitor class is interested in.
    /// 
    /// For every new shop class added, a new VisitXXX() method needs to be
    /// added to this base class and then all visitor classes must be rebuilt.
    /// There is no way around this as the Visitor_Shop and Visitor classes are
    /// closely intertwined -- at least at the interface level.
    /// </summary>
    public class Visitor
    {
        /// <summary>
        /// Let the visitor visit a Visitor_Restaurant shop.
        /// </summary>
        /// <param name="shop">The specific restaurant being visited.</param>
        public virtual void VisitRestaurant(Visitor_Restaurant shop) { }

        /// <summary>
        /// Let the visitor visit a Visitor_Butcher shop.
        /// </summary>
        /// <param name="shop">The specific butcher shop being visited.</param>
        public virtual void VisitButcher(Visitor_Butcher shop) { }

        /// <summary>
        /// Let the visitor visit a Visitor_Baker shop.
        /// </summary>
        /// <param name="shop">The specific baker shop being visited.</param>
        public virtual void VisitBaker(Visitor_Baker shop) { }

        /// <summary>
        /// Let the visitor visit a Visitor_VegetableGrocer shop.
        /// </summary>
        /// <param name="shop">The specific vegetable grocer being visited.</param>
        public virtual void VisitVegetableGrocer(Visitor_VegetableGrocer shop) { }

        /// <summary>
        /// Let the visitor visit a Visitor_CondimentGrocer shop.
        /// </summary>
        /// <param name="shop">The specific condiment grocer being visited.</param>
        public virtual void VisitCondimentGrocer(Visitor_CondimentGrocer shop) { }

        /// <summary>
        /// Let the visitor visit a Visitor_PickleGrocer shop.
        /// </summary>
        /// <param name="shop">The specific pickle grocer being visited.</param>
        public virtual void VisitPickleGrocer(Visitor_PickleGrocer shop) { }

        /// <summary>
        /// Let the visitor visit a Visitor_Maker shop.
        /// </summary>
        /// <param name="shop">The specific maker shop being visited.</param>
        public virtual void VisitMaker(Visitor_Maker shop) { }

    }

    /// <summary>
    /// The interface that all element classes must implement if they are
    /// to participate in the visitor pattern.
    /// </summary>
    public interface ISupportVisitors
    {
        /// <summary>
        /// The visitor will call this method on each element it wants to
        /// visit.
        /// </summary>
        /// <param name="visitor">The visitor.</param>
        void Accept(Visitor visitor);
    }

    /// <summary>
    /// Base class that all shops must implement.
    /// 
    /// Technically, all the work is done in this base class but we still need
    /// to differentiate between different shop types for the visitors.
    /// </summary>
    public abstract class Visitor_Shop
    {
        /// <summary>
        /// Inventory for this shop.
        /// </summary>
        private Dictionary<string, int> Inventory = new Dictionary<string, int>();

        /// <summary>
        /// Name of the shop.
        /// </summary>
        public string Name
        { get; set; }

        /// <summary>
        /// Address of the shop (could be a structure but a simple string is
        /// sufficient for this example).
        /// </summary>
        public string Address
        { get; set; }

        /// <summary>
        /// The Village that contains this shop.
        /// </summary>
        public Village Village
        { get; set; }

        //-------------------------------------------------------------------

        /// <summary>
        /// Specifies the ingredients needed for each item sold by the shop.
        /// Also, the keys are what the shop sells.  The ingredient list could
        /// be empty if this shop is the origin of the item used as the key.
        /// </summary>
        public Dictionary<string, string[]> IngredientsForItems
        { get; set; }


        /// <summary>
        /// Determine if this shop sells the specified itrem.
        /// </summary>
        /// <param name="item">The item to look for</param>
        /// <returns>Returns true if this shop sells the item; otherwise false.
        /// </returns>
        bool DoesShopSellItem(string item)
        {
            return IngredientsForItems.ContainsKey(item);
        }

        /// <summary>
        /// Determine if this shop has the specified item in stock.
        /// </summary>
        /// <param name="item">The item to look for</param>
        /// <returns>Returns true if the item is in stock; otherwise false.
        /// </returns>
        bool IsItemInStock(string item)
        {
            return Inventory.ContainsKey(item) && Inventory[item] > 0;
        }

        /// <summary>
        /// Add the specified item to this shop's inventory.
        /// </summary>
        /// <param name="item">The item to add</param>
        void AddItemToInventory(string item)
        {
            if (!Inventory.ContainsKey(item))
            {
                Inventory.Add(item, 1);
            }
            else
            {
                Inventory[item]++;
            }
        }

        /// <summary>
        /// Convert a string list to a comma-delimited string.  Useful for
        /// displaying the list.
        /// </summary>
        /// <param name="items">List to be stringized</param>
        /// <returns>Returns a string containing the comma-delimited contents
        /// of the list.</returns>
        string StringizeList(string[] items)
        {
            StringBuilder output = new StringBuilder();

            foreach(string item in items)
            {
                if (output.Length > 0)
                {
                    output.Append(", ");
                }
                output.Append(item);
            }
            return output.ToString();
        }

        /// <summary>
        /// Place an order for the specified items.  If the inventory is empty,
        /// replenish the inventory by visiting other shops for the missing
        /// ingredients.
        /// 
        /// Call PickupOrder() to receive the order and reduce the inventory.
        /// </summary>
        /// <param name="items">List of items to order.</param>
        /// <returns>Returns true if the order was placed; otherwise, returns
        /// false (shop doesn't sell the items).</returns>
        public bool PlaceOrder(string[] items)
        {
            bool orderPlaced = false;
            List<string> outOfStockItems = new List<string>();
            List<string> itemsInThisShop = new List<string>();
            
            foreach (string item in items)
            {
                if (DoesShopSellItem(item))
                {
                    if (!IsItemInStock(item))
                    {
                        outOfStockItems.Add(item);
                    }
                    itemsInThisShop.Add(item);
                }
            }

            if (itemsInThisShop.Count > 0)
            {
                Console.WriteLine("  {0}: Received an order for {1}.", Name, StringizeList(itemsInThisShop.ToArray()));
                orderPlaced = true;
            }
            if (outOfStockItems.Count > 0)
            {
                    foreach (string itemToOrder in outOfStockItems)
                {
                    if (IngredientsForItems[itemToOrder].Length > 0)
                    {
                        Console.WriteLine("  {0}:   {1} out of stock, ordering ingredients to make more...", Name, itemToOrder);
                        OrderVisitor visitor = new OrderVisitor(IngredientsForItems[itemToOrder]);
                        Village.Accept(visitor);
                    }
                    else
                    {
                        // The ordered item has no ingredients so the
                        // ordered item will be magically added to inventory
                        Console.WriteLine("  {0}:   {1} out of stock, making...", Name, itemToOrder);
                    }
                    AddItemToInventory(itemToOrder);
                }
            }
            return orderPlaced;
        }

        /// <summary>
        /// Pick up the items sold by this shop (assumes the items were ordered
        /// already).  Basically, this reduces the inventory for the given items
        /// that are sold by this shop.
        /// </summary>
        /// <param name="items">Items that were ordered, some of which may be
        /// sold by this shop.</param>
        /// <param name="itemsToBePickedUp">List to be filled in with the
        /// item names that were picked up.</param>
        public void PickupOrder(string[] items, List<string> itemsToBePickedUp)
        {
            itemsToBePickedUp.Clear();
            foreach (string item in items)
            {
                // If this shop sells the item and the item is in stock then
                if (DoesShopSellItem(item))
                {
                    if (IsItemInStock(item))
                    {
                        itemsToBePickedUp.Add(item);
                    }
                    else
                    {
                        Console.WriteLine("  Error!  {0}: Item {1} is not in the inventory when it should be.", Name, item);
                    }
                }
            }

            if (itemsToBePickedUp.Count > 0)
            {
                // Reduce inventory for the ordered items
                StringBuilder output = new StringBuilder();
                foreach (string itemToBePickedUp in itemsToBePickedUp)
                {
                    if (output.Length > 0)
                    {
                        output.Append(", ");
                    }
                    output.Append(itemToBePickedUp);
                    Inventory[itemToBePickedUp]--;
                }
                Console.WriteLine("  {0}: Order picked up for {1}.", Name, output.ToString());
            }
        }

        /// <summary>
        /// The visitor will call this method on each element it wants to
        /// visit.
        /// </summary>
        /// <param name="visitor">The visitor.</param>
        public abstract void Accept(Visitor visitor);
    }


    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------


    /// <summary>
    /// Represent a restaurant shop.
    /// </summary>
    public class Visitor_Restaurant : Visitor_Shop
    {
        /// <summary>
        /// Handle visitors to this class.
        /// </summary>
        /// <param name="visitor">The visitor</param>
        public override void Accept(Visitor visitor)
        {
            visitor.VisitRestaurant(this);
        }
    }


    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------


    /// <summary>
    /// Represent a butcher shop.
    /// </summary>
    public class Visitor_Butcher : Visitor_Shop
    {
        /// <summary>
        /// Handle visitors to this class.
        /// </summary>
        /// <param name="visitor">The visitor</param>
        public override void Accept(Visitor visitor)
        {
            visitor.VisitButcher(this);
        }
    }


    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------


    /// <summary>
    /// Represent a baker shop.
    /// </summary>
    public class Visitor_Baker : Visitor_Shop
    {
        /// <summary>
        /// Handle visitors to this class.
        /// </summary>
        /// <param name="visitor">The visitor</param>
        public override void Accept(Visitor visitor)
        {
            visitor.VisitBaker(this);
        }
    }


    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------


    /// <summary>
    /// Represent a vegetable grocer.
    /// </summary>
    public class Visitor_VegetableGrocer : Visitor_Shop
    {
        /// <summary>
        /// Handle visitors to this class.
        /// </summary>
        /// <param name="visitor">The visitor</param>
        public override void Accept(Visitor visitor)
        {
            visitor.VisitVegetableGrocer(this);
        }
    }


    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------


    /// <summary>
    /// Represent a condiment grocer.
    /// </summary>
    public class Visitor_CondimentGrocer : Visitor_Shop
    {
        /// <summary>
        /// Handle visitors to this class.
        /// </summary>
        /// <param name="visitor">The visitor</param>
        public override void Accept(Visitor visitor)
        {
            visitor.VisitCondimentGrocer(this);
        }
    }


    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------


    /// <summary>
    /// Represent a pickle grocer.
    /// </summary>
    public class Visitor_PickleGrocer : Visitor_Shop
    {
        /// <summary>
        /// Handle visitors to this class.
        /// </summary>
        /// <param name="visitor">The visitor</param>
        public override void Accept(Visitor visitor)
        {
            visitor.VisitPickleGrocer(this);
        }
    }


    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------


    /// <summary>
    /// Represent a maker (of things).
    /// </summary>
    public class Visitor_Maker : Visitor_Shop
    {
        /// <summary>
        /// Handle visitors to this class.
        /// </summary>
        /// <param name="visitor">The visitor</param>
        public override void Accept(Visitor visitor)
        {
            visitor.VisitMaker(this);
        }
    }
}
