using System.Collections.Generic;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents a collection of shops that can be visited.
    /// 
    /// This class works as the container of all objects that can be visited.
    /// All visits start in this container.
    /// </summary>
    public class Village : ISupportVisitors
    {
        /// <summary>
        /// Name of this village
        /// </summary>
        public string Name;

        /// <summary>
        /// List of Visitor_Shop class-derived shops in this village that can be visited.
        /// </summary>
        private List<Visitor_Shop> shops = new List<Visitor_Shop>();

        /// <summary>
        /// Load the village.
        /// </summary>
        public void LoadVillage()
        {
            Name = "Village of Self-Sufficiency";

            shops.Add(new Visitor_Restaurant
            {
                Name = "Joe's Burger Joint",
                Address = "47 Millings Rd.",
                Village = this,
                IngredientsForItems = new Dictionary<string, string[]> {
                    { "hamburger", new string[] { "ground beef", "hamburger buns", "ketchup", "mustard", "mayonnaise", "lettuce", "tomato", "onion", "pickles" } }
                }
            });

            shops.Add(new Visitor_Butcher
            {
                Name = "Amelia's Butcher Shop",
                Address = "12 Klaxon Ave.",
                Village = this,
                IngredientsForItems = new Dictionary<string, string[]> { { "ground beef", new string[] { } } }
            });

            shops.Add(new Visitor_Baker
            {
                Name = "Oxel's Breads and Buns Bakery",
                Address = "131 Worthington Dr.",
                Village = this,
                IngredientsForItems = new Dictionary<string, string[]> { { "hamburger buns", new string[] { } } }
            });

            shops.Add(new Visitor_CondimentGrocer
            {
                Name = "Connie's Condiments",
                Address = "83 Millings Rd.",
                Village = this,
                IngredientsForItems = new Dictionary<string, string[]> {
                    { "ketchup", new string[] { "fresh ketchup" } },
                    { "mustard", new string[] { "fresh mustard" } },
                    { "mayonnaise", new string[] { "fresh mayonnaise" } }
                }
            });

            shops.Add(new Visitor_VegetableGrocer
            {
                Name = "Florence's Vegetables",
                Address = "32 Main St.",
                Village = this,
                IngredientsForItems = new Dictionary<string, string[]> {
                    { "lettuce", new string[] { } },
                    { "tomato", new string[] { } },
                    { "onion", new string[] { } },
                    { "cucumber", new string[] { } },
                    { "mustard seed", new string[] { } }
                }
            });

            shops.Add(new Visitor_PickleGrocer
            {
                Name = "Larry's Pickle Emporium",
                Address = "34 Main St.",
                Village = this,
                IngredientsForItems = new Dictionary<string, string[]> { { "pickles", new string[] { "vinegar", "cucumber", "salt" } } }
            });

            shops.Add(new Visitor_Maker
            {
                Name = "Klyde and Sons Ketchup Makers",
                Address = "800 Overtown Rd.",
                Village = this,
                IngredientsForItems = new Dictionary<string, string[]> { { "fresh ketchup", new string[] { } } }
            });

            shops.Add(new Visitor_Maker
            {
                Name = "Molly's Mustard Mart",
                Address = "810 Overtown Rd.",
                Village = this,
                IngredientsForItems = new Dictionary<string, string[]> { { "fresh mustard", new string[] { "vinegar", "mustard seed" } } }
            });

            shops.Add(new Visitor_Maker
            {
                Name = "Turk's Mayo Supply",
                Address = "820 Overtown Rd.",
                Village = this,
                IngredientsForItems = new Dictionary<string, string[]> { { "fresh mayonnaise", new string[] { } } }
            });

            shops.Add(new Visitor_Maker
            {
                Name = "Vinnies' Sour Flavors",
                Address = "830 Overtown Rd.",
                Village = this,
                IngredientsForItems = new Dictionary<string, string[]> { { "vinegar", new string[] { } } }
            });

            shops.Add(new Visitor_Maker
            {
                Name = "Jessie's Salt Works",
                Address = "920 Overtown Rd.",
                Village = this,
                IngredientsForItems = new Dictionary<string, string[]> { { "salt", new string[] { } } }
            });
        }


        // Implementation of the ISupportVisitors interface.
        public void Accept(Visitor visitor)
        {
            foreach (var shop in shops)
            {
                shop.Accept(visitor);
            }
        }
    }
}
