//! Contains the Village struct that holds all the shops that can be visited.

//-----------------------------------------------------------------------------
use std::collections::HashMap;

use super::visitor_shop::VisitorShop;
use super::visitor_ordervisitor::OrderVisitor;

//-----------------------------------------------------------------------------

/// Represents a collection of shops that can be visited.
pub struct Village {
    /// Name of this village.
    pub name: String,
    /// List of shops in this village.
    shops: Vec<VisitorShop>,
}

impl Village {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the Village struct.  Call load() to load
    /// the particulars of this instance.
    pub fn new() -> Village {
        Village {
            name: String::new(),
            shops: vec![],
        }
    }

    /// Set up the specified Village object with all the shops that can be
    /// visited.
    pub fn load(&mut self) {
        self.name = String::from("Village of Self-Sufficiency");

        let mut shop_ingredients: HashMap<String, Vec<String>> = HashMap::new();
        shop_ingredients.insert("hamburger".to_string(), vec!["ground beef", "hamburger buns", "ketchup", "mustard", "mayonnaise", "lettuce", "tomato", "onion", "pickles"].iter().map(|x|{x.to_string()}).collect());
        let mut shop = VisitorShop::new(
            "Joe's Burger Joint",
            "47 Millings Rd.",
            shop_ingredients
            );
        self.shops.push(shop);

        shop_ingredients = HashMap::new();
        shop_ingredients.insert("ground beef".to_string(), vec![]);
        shop = VisitorShop::new(
            "Amelia's Butcher Shop",
            "12 Klaxon Ave.",
            shop_ingredients,
        );
        self.shops.push(shop);

        shop_ingredients = HashMap::new();
        shop_ingredients.insert("hamburger buns".to_string(), vec![]);
        shop = VisitorShop::new(
            "Oxel's Breads and Buns Bakery",
            "131 Worthington Dr.",
            shop_ingredients,
        );
        self.shops.push(shop);

        shop_ingredients = HashMap::new();
        shop_ingredients.insert("ketchup".to_string(), vec!["fresh ketchup"].iter().map(|x|{x.to_string()}).collect());
        shop_ingredients.insert("mustard".to_string(), vec!["fresh mustard"].iter().map(|x|{x.to_string()}).collect());
        shop_ingredients.insert("mayonnaise".to_string(), vec!["fresh mayonnaise"].iter().map(|x|{x.to_string()}).collect());
        shop = VisitorShop::new(
            "Connie's Condiments",
            "83 Millings Rd.",
            shop_ingredients,
        );
        self.shops.push(shop);

        shop_ingredients = HashMap::new();
        shop_ingredients.insert("lettuce".to_string(), vec![]);
        shop_ingredients.insert("tomato".to_string(), vec![]);
        shop_ingredients.insert("onion".to_string(), vec![]);
        shop_ingredients.insert("cucumber".to_string(), vec![]);
        shop_ingredients.insert("mustard seed".to_string(), vec![]);
        shop = VisitorShop::new(
            "Florence's Vegetables",
            "32 Main St.",
            shop_ingredients,
        );
        self.shops.push(shop);

        shop_ingredients = HashMap::new();
        shop_ingredients.insert("pickles".to_string(), vec!["vinegar", "cucumber", "salt"].iter().map(|x|{x.to_string()}).collect());
        shop = VisitorShop::new(
            "Larry's Pickle Emporium",
            "34 Main St.",
            shop_ingredients,
        );
        self.shops.push(shop);

        shop_ingredients = HashMap::new();
        shop_ingredients.insert("fresh ketchup".to_string(), vec![]);
        shop = VisitorShop::new(
            "Klyde and Sons Ketchup Makers",
            "800 Overtown Rd.",
            shop_ingredients,
        );
        self.shops.push(shop);

        shop_ingredients = HashMap::new();
        shop_ingredients.insert("fresh mustard".to_string(), vec!["vinegar", "mustard seed"].iter().map(|x|{x.to_string()}).collect());
        shop = VisitorShop::new(
            "Molly's Mustard Mart",
            "810 Overtown Rd.",
            shop_ingredients,
        );
        self.shops.push(shop);

        shop_ingredients = HashMap::new();
        shop_ingredients.insert("fresh mayonnaise".to_string(), vec![]);
        shop = VisitorShop::new(
            "Turk's Mayo Supply",
            "820 Overtown Rd.",
            shop_ingredients,
        );
        self.shops.push(shop);

        shop_ingredients = HashMap::new();
        shop_ingredients.insert("vinegar".to_string(), vec![]);
        shop = VisitorShop::new(
            "Vinnies' Sour Flavors",
            "830 Overtown Rd.",
            shop_ingredients,
        );
        self.shops.push(shop);

        shop_ingredients = HashMap::new();
        shop_ingredients.insert("salt".to_string(), vec![]);
        shop = VisitorShop::new(
            "Jessie's Salt Works",
            "920 Overtown Rd.",
            shop_ingredients,
        );
        self.shops.push(shop);
    }

    /// Visit all shops in the given Village object to find the ingredients
    /// specified in the OrderVisitor object.  Can set off a nested chain of
    /// calls.
    ///
    /// # Parameters
    /// - order
    ///
    ///   An OrderVisitor object that contains a list of items to order and
    ///   a list of items received after the visit is complete.
    pub fn visit(&mut self, order: &mut OrderVisitor) {
        // Clone the shop list from the village to get around an error
        // involving two mutable references to the village: The first is in
        // the for loop and the second is when passing the village to the
        // visit_shop() method.  Cloning the shop is kind of expensive,
        // especially since this method can be recursively called by shops as
        // needed.  But I could not find another way to get around the double
        // mutable error.
        let mut shops = self.shops.clone();

        for shop in shops.iter_mut() {
            order.visit_shop(shop, self);
        }
    }
}
