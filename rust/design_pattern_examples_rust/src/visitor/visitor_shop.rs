//! Contains the VisitorShop struct, which represents each shop in the village
//! that can be visited.

//-----------------------------------------------------------------------------

use std::collections::HashMap;

use super::visitor_ordervisitor::OrderVisitor;


//-----------------------------------------------------------------------------

/// Convert a string list to a comma-delimited string.  Useful for displaying
/// the list.
///
/// # Parameters
/// - items
///
///   List of strings to be formatted into a comma-delimited string.
///
/// # Returns
/// Returns a string containing the formatted list.
fn stringize_list(items: &Vec<String>) -> String {
    items.join(", ")
}
//-----------------------------------------------------------------------------


pub struct VisitorShop {
    /// Name of this shop.
    pub name: String,
    /// Address of this shop.
    pub address: String,
    //struct Village* Village : Can't use circular references!
    /// Maps ingredient to list of items needed to make ingredient.
    pub ingredients_for_items: HashMap<String, Vec<String>>,
    /// Maps ingredient to count of that ingredient currently in the shop.
    pub inventory: HashMap<String, i32>,
}

impl VisitorShop {
    /// Constructor.
    ///
    /// # Parameters
    /// - name
    ///
    ///   Name of the shop.
    /// - address
    ///
    ///   Address of the shop.
    /// - ingredients_for_items
    ///
    ///   Map of items to be sold with a list of ingredients needed to "make"
    ///   each item.  The VisitorShop takes ownership of the map.
    ///
    /// # Returns
    /// Returns a new instance of the VisitorShop struct.
    pub fn new(name: &str, address: &str, ingredients_for_items: HashMap<String, Vec<String>>) -> VisitorShop {
        let mut inventory: HashMap<String, i32> = HashMap::new();
        for item in ingredients_for_items.keys() {
            inventory.insert(item.clone(), 0);
        }
        VisitorShop {
            name: name.to_string(),
            address: address.to_string(),
            ingredients_for_items,
            inventory: inventory,
        }
    }

    /// Determine if this shop sells the specified item.
    ///
    /// # Parameters
    /// - item
    ///
    ///   The name of the item to look for.
    ///
    /// # Returns
    /// Returns true if this shop sells the item; otherwise, returns false.
    fn does_shop_sell_item(&self, item: &str) -> bool {
        self.ingredients_for_items.contains_key(item)
    }

    /// Determine if this shop has the specified item in stock.
    ///
    /// # Parameters
    /// - item
    ///
    ///   The name of the item to look for.
    ///
    /// # Returns
    /// Returns true if the item is in stock; otherwise, returns false.
    fn is_item_in_stock(&self, item: &str) -> bool {
        if self.inventory.contains_key(item) {
            self.inventory[item] > 0
        } else {
            false
        }
    }

    /// Add the specified item to this shop's inventory.
    ///
    /// # Parameters
    /// - item
    ///
    ///   The name of the item to update its inventory count.
    fn add_item_to_inventory(&mut self, item: &str) {
        if !self.inventory.contains_key(item) {
            self.inventory.insert(item.to_string(), 1);
        } else {
            self.inventory.entry(item.to_string()).and_modify(|e| { *e += 1 });
        }
    }

    /// Visit this shop to try to place an order as described in the
    /// OrderVisitor object.
    ///
    /// # Parameters
    /// - order
    ///
    ///   An OrderVisitor object that contains a list of items to order,
    ///   possibly at this shop.
    ///
    /// # Returns
    /// Returns true if the order was successfully placed at this shop;
    /// otherwise, returns false, try another shop.
    pub fn place_order(&mut self, order: &mut OrderVisitor) -> bool {
        let mut order_placed = false;
        
        let mut out_of_stock_items: Vec<String> = vec![];
        let mut items_in_this_shop: Vec<String> = vec![];
        
        for item in order.items_to_order.iter() {
            if self.does_shop_sell_item(&item) {
                if !self.is_item_in_stock(&item) {
                    out_of_stock_items.push(item.clone());
                }
                items_in_this_shop.push(item.clone());
            }
        }

        if !items_in_this_shop.is_empty() {
            println!("  {0}: Received an order for {1}.",
                    self.name, stringize_list(&items_in_this_shop));
            order_placed = true;
        }

        if !out_of_stock_items.is_empty() {
            for item in out_of_stock_items.iter() {
                let ingredients = self.ingredients_for_items.get(item);
                if let Some(items) = ingredients {
                    if !items.is_empty() {
                        println!("  {0}:   {1} out of stock, ordering ingredients to make more...",
                            self.name, item);
                        let reorder_visitor = OrderVisitor::new(&items);
                        //village.visit(&reorder_visitor);
                    } else {
                        // The ordered item has no ingredients so the
                        // ordered item will be magically added to inventory
                        println!("  {0}:   {1} out of stock, making...",
                                self.name, item);
                        self.add_item_to_inventory(item);
                    }
                }
            }
        }

        order_placed
    }


    /// Pick up the items sold by this shop (assumes the items were ordered
    /// already).  Basically, this reduces the inventory for the given items
    /// that are sold by this shop.  This method should be called only if
    /// place_order() returns true.
    ///
    /// # Parameters
    /// - order
    ///
    ///   An OrderVisitor object that receives the requested items.
    pub fn pickup_order(&mut self, order: &mut OrderVisitor) {
        order.items_received.clear();
        for item in order.items_to_order.iter() {
            if self.does_shop_sell_item(&item) {
                if self.is_item_in_stock(&item) {
                    order.items_received.push(item.clone());
                } else {
                    println!("  Error!  {0}: Item {1} is not in the inventory when it should be.",
                            self.name, item);
                }
            }
        }
        if !order.items_received.is_empty() {
            // Reduce inventory for the ordered items
            let items_as_string = stringize_list(&order.items_received);
            for item in order.items_received.iter() {
                self.inventory.entry(item.clone()).and_modify(|e| { *e -= 1 });
            }
            println!("  {0}: Order picked up for {1}.", self.name, items_as_string);
        }
    }
}
