//! # design_pattern_examples_rust
//!
//! Implementation of the main() entry point and the machinery to call all the
//! design pattern example functions.

use std::env;

mod adapter;
mod bridge;
mod command;
mod composite;
mod decorator;
mod facade;
mod flyweight;
mod handlerchain;
mod interpreter;
mod iterator;
mod mediator;
mod memento;
mod nullobject;
mod observer;
mod proxy;
mod state;
mod strategy;
mod visitor;


/// Alias for a function pointer, using C# as inspiration for the name.
type Action = fn();

/// Represents a single exercise or example for a design pattern.
struct Exercise {
    /// Name of the exercise.
    exercise_name: String,

    /// Function to call to run the exercise.
    exercise_to_run: Action,
}

impl Exercise {
    /// Constructor for the Exercise struct.
    ///
    /// # Parameters
    /// - exercise_name
    ///
    ///     Name of the exercise
    /// - exercise_to_run
    ///
    ///     Pointer to the function to call to run the exercise.
    ///
    /// # Returns
    /// Returns the new Exercise instance.
    fn new(exercise_name: &str, exercise_to_run: Action) -> Exercise {
        Exercise {
            exercise_name: exercise_name.to_string(),
            exercise_to_run,
        }
    }
}


/// Represents the command line options provided to the program, if any.
struct Options {
    /// List of names of exercise to run.  If this list is empty, run all
    /// exercises.
    exercise_names: Vec<String>,
}


/// Helper function to show usage information for this program.
/// 
/// # Parameters
/// - exercises
///
///     List of Exercise objects to display if help is needed.
fn help(exercise_list: &Vec<Exercise>) {
    let usage =
"DesignPatternExamples_c by Stephen P. Lepisto
usage: DesignPatternExamples_c [options] [exercise_name][[ exercise_name][...]]

Runs through a series of exercises showing off design patterns.  If no
exercise_name is given, then run through all exercises.

Options:
--help, -?
        This help text.
"; // End of string.

    println!("{usage}");

    println!("Exercises available:");
    for exercise in exercise_list {
        println!("  {}", exercise.exercise_name);
    }
}

/// Helper function to parse the given options and store the results in
/// the given Options structure.  Displays help if requested and
/// returns false.
///
/// # Parameters
/// - args
///
///     A list of strings containing the command line arguments (should
///     not include the program name normally in the first item)
/// - exercises
///
///     List of Exercise objects to display if help is needed.
///
/// # Returns
/// `Ok<Options>` if successful (the Options structure is filled in by
/// command line parameters.  Returns `Err<&str>` if help was requested.
fn parse_options(args: &[String], exercise_list: &Vec<Exercise>) -> Result<Options, &'static str> {
    let mut exercise_names: Vec<String> = Vec::new();

    for arg in args {
        match arg.as_str() {
            "--help" | "-?" | "/?" => {
                help(exercise_list);
                return Err("");
            },
            _ => exercise_names.push(arg.to_string()),
        }
    }

    Ok(Options { exercise_names })
}


/// Main entry point into this example program.
fn main() {
    let exercise_list = vec!(
        Exercise::new("Adapter", adapter::adapter_exercise),
        Exercise::new("Bridge", bridge::bridge_exercise),
        Exercise::new("Command", command::command_exercise),
        Exercise::new("Composite", composite::composite_exercise),
        Exercise::new("Decorator", decorator::decorator_exercise),
        Exercise::new("Facade", facade::facade_exercise),
        Exercise::new("Flyweight", flyweight::flyweight_exercise),
        Exercise::new("HandlerChain", handlerchain::handlerchain_exercise),
        Exercise::new("Interpreter", interpreter::interpreter_exercise),
        Exercise::new("Iterator", iterator::iterator_exercise),
        Exercise::new("Mediator", mediator::mediator_exercise),
        Exercise::new("Memento", memento::memento_exercise),
        Exercise::new("NullObject", nullobject::nullobject_exercise),
        Exercise::new("Observer", observer::observer_exercise),
        Exercise::new("Proxy", proxy::proxy_exercise),
        Exercise::new("State", state::state_exercise),
        Exercise::new("Strategy", strategy::strategy_exercise),
        Exercise::new("Visitor", visitor::visitor_exercise),
    );

    // skip() first argument as it is the program name.
    let args: Vec<String> = env::args().skip(1).collect();

    let parsed_options = parse_options(&args, &exercise_list);

    if let Ok(options) = parsed_options {
        for exercise in exercise_list {
            if options.exercise_names.is_empty() ||
               options.exercise_names.contains(&exercise.exercise_name) {
                (exercise.exercise_to_run)();
            }
        }
    }
}
