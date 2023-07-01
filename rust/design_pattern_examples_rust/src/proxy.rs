//! The Proxy design pattern example module
//! 
//! The Proxy pattern is used when a large or expensive object cannot be
//! represented directly in the program, typically because the object is in
//! another process or even another system altogether.
//! 
//! In this exercise, a Proxy struct implements the same trait as the
//! Real struct, making the Proxy struct look like the Real struct.  Calls
//! made on the Proxy struct are passed to the Real struct where the work
//! is actually done (in this case, a munged string with the text
//! "Real struct received 'xxxx'".
//!
//! Accessed through the proxy_exercise() function.

//-----------------------------------------------------------------------------

pub mod proxy_real;
pub mod proxy_proxy;
pub mod proxy_iworkbyproxy_trait;

//-----------------------------------------------------------------------------

use proxy_proxy::ProxyEntity;

//-----------------------------------------------------------------------------

/// Example of using the "Proxy" design pattern.
/// 
/// The Proxy pattern is used when a large or expensive object cannot be
/// represented directly in the program, typically because the object is in
/// another process or even another system altogether.
/// 
/// In this exercise, a Proxy struct implements the same trait as the
/// Real struct, making the Proxy struct look like the Real struct.  Calls
/// made on the Proxy struct are passed to the Real struct where the work
/// is actually done (in this case, a munged string with the text
/// "Real struct received 'xxxx'".
/// 
/// The only difference in output here is one additional line for the
/// first call showing the real struct being instantiated.  The subsequent
/// calls into the Proxy struct do not show this line.
// ! [Using Proxy in Rust]
pub fn proxy_exercise() -> Result<(), String> {
    println!("");
    println!("Proxy Exercise");

    println!("  Getting proxy object...");
    let mut proxy = ProxyEntity::new();
    
    println!("  Calling Dowork() on proxy...");
    let mut output = proxy.do_work("Initial call");
    println!("  Output from proxy = \"{0}\"", output);
    
    println!("  Calling Dowork() on proxy...");
    output = proxy.do_work("Second call");
    println!("  Output from proxy = \"{0}\"", output);
    
    println!("  Calling Dowork() on proxy...");
    output = proxy.do_work("Third call");
    println!("  Output from proxy = \"{0}\"", output);

    println!("  Done.");

    Ok(())
}
// ! [Using Proxy in Rust]
