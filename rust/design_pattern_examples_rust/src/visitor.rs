//! The Visitor design pattern example module
//! 
//! The Visitor pattern is used to add functionality to a list of otherwise
//! unchanging element objects by passing a visitor object to each element
//! object.  Each element object calls the visitor object, passing itself as an
//! argument.  The visitor object then does something based on the type of the
//! element.
//! 
//! In this exercise, a collection of shop objects is initialized then an order
//! visitor is created to retrieve an item from one of the shop objects.  Along
//! the way, shops that don't have the necessary ingredients use another order
//! visitor to order ingredients from other shops.  This approach assumes no
//! two shops sell the same thing.
//!
//! Accessed through the visitor_exercise() function.

//-----------------------------------------------------------------------------

pub mod visitor_ordervisitor;
pub mod visitor_village;
pub mod visitor_shop;

//-----------------------------------------------------------------------------

use visitor_village::Village;
use visitor_ordervisitor::OrderVisitor;

//-----------------------------------------------------------------------------

/// Example of using the "Visitor" design pattern.
/// 
/// The Visitor pattern is used to add functionality to a list of otherwise
/// unchanging element objects by passing a visitor object to each element
/// object.  Each element object calls the visitor object, passing itself as an
/// argument.  The visitor object then does something based on the type of the
/// element.
/// 
/// In this exercise, a collection of shop objects is initialized then an order
/// visitor is created to retrieve an item from one of the shop objects.  Along
/// the way, shops that don't have the necessary ingredients use another order
/// visitor to order ingredients from other shops.  This approach assumes no
/// two shops sell the same thing.
// ! [Using Visitor in Rust]
pub fn visitor_exercise() -> Result<(), String> {
    println!("");
    println!("Visitor Exercise");

    let mut village = Village::new();
    village.load();

    let mut order = OrderVisitor::new(&vec!["hamburger".to_string()]);
    println!("  Ordering a hamburger from a shop in the {0}", village.name);
    village.visit(&mut order);

    if !order.items_received.is_empty() {
        // We are expecting only a single item
        println!("  We received a {0} from {1}.",
                order.items_received[0], order.shop_name_received_from);
    } else {
        println!("  Failed to receive a hamburger");
    }

    println!("  Done.");

    Ok(())
}
// ! [Using Visitor in Rust]
