//! Contains the OrderVisitor struct that represents the visitor going around
//! and visiting the shops of the village.

//-----------------------------------------------------------------------------

use super::visitor_shop::VisitorShop;
//-----------------------------------------------------------------------------

/// Represents a visitor used for ordering items from various shops.  The user
/// starts with an instance of this struct and a list of what they want to
/// order.
/// 
/// Later, a shop will use this visitor to order ingredients to make a
/// requested item.
pub struct OrderVisitor {
    /// Items to be ordered from any shop that sells the item.
    pub items_to_order: Vec<String>,
    /// List of items received from an order/pickup process.
    pub items_received: Vec<String>,
    /// Name of the shop that provided the item(s).
    pub shop_name_received_from: String,
}

impl OrderVisitor {
    /// Constructor
    ///
    /// # Returns
    /// Returns a new instance of the OrderVisitor struct.
    pub fn new(items_to_order: &Vec<String>) -> OrderVisitor {
        OrderVisitor {
            items_to_order: items_to_order.clone(),
            items_received: vec![],
            shop_name_received_from: String::new(),
        }
    }

    /// Represents a visit to the specified VisitorShop with the specified
    /// order.  The visit might or might not result in an order being placed
    /// and subsequently picked up.
    ///
    /// # Parameters
    /// - shop
    ///
    ///   The VisitorShop object to visit.
    pub fn visit_shop(&mut self, shop: &mut VisitorShop) {
        let order_placed = shop.place_order(self);
        if order_placed {
            shop.pickup_order(self);
            self.shop_name_received_from = shop.name.clone();
        }
    }
}
