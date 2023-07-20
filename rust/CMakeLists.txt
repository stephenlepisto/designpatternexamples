find_program(CARGO cargo)

set(_RUST_ROOT "${CMAKE_SOURCE_DIR}/rust/design_pattern_examples_rust")
set(_RUST_SRC "${_RUST_ROOT}/src")

# Rust is not supported directly in cmake so create a custom target and
# link it to a custom command that does the actual building.
add_custom_target(DesignPatternExamples_rust ALL
    DEPENDS $<CONFIG>/design_pattern_examples_rust.exe
    VERBATIM
)

add_dependencies(DesignPatternExamples_rust Adapter_BackEnd)

# The TARGET generators don't work in custom commands so use the generator
# to create a simple variable outside the custom command and pass the variable
# into the custom command.
set(ADAPTER_BINARY_DIR "$<TARGET_FILE_DIR:Adapter_BackEnd>")

# Set up the args for cargo build based on the current configuration.  The
# generator expression here will not work in the custom command as it inserts
# an empty string in the command line, which is picked up by cargo and flagged
# as an error (in my opinion, a bug on cargo's part, where it should ignore
# empty arguments).
#
# For some reason, the same expansion done directly in the custom command
# when the generator expression is false (and therefore an empty string)
# cause that empty string to seen as an argument to cargo build, which is
# flagged as an error by cargo.
set(CARGO_ARGS build $<$<CONFIG:Release>:--release>)

# 7/16/2023
# This custom command builds the rust example.  We are using environment
# variables to override the default rust output directory because passing
# "cargo build --target-dir ${CMAKE_BINARY_DIR}/rust" does not set the
# target_directory property in the cargo metadata, which build.rs is using in
# the rust example.
#
# Of course, since I need to pass in a second environment variable for the
# location of the Adapter_BackEnd, I could just as easily use the environment
# variable directly for the rust output directory.
#
# Rust still has some growing to do to play nicely with other tools such as
# cmake.
add_custom_command(OUTPUT $<CONFIG>/design_pattern_examples_rust.exe
    COMMAND ${CMAKE_COMMAND} -E env
                "CARGO_BUILD_TARGET_DIR=${CMAKE_BINARY_DIR}/rust"
                "ADAPTER_BINARY_DIR=${ADAPTER_BINARY_DIR}"
                ${CARGO} ${CARGO_ARGS}
    WORKING_DIRECTORY ${_RUST_ROOT}
    COMMAND_EXPAND_LISTS
    VERBATIM
)


target_sources(DesignPatternExamples_rust
    PRIVATE
        ${_RUST_SRC}/adapter.rs
        ${_RUST_SRC}/bridge.rs
        ${_RUST_SRC}/command.rs
        ${_RUST_SRC}/composite.rs
        ${_RUST_SRC}/decorator.rs
        ${_RUST_SRC}/facade.rs
        ${_RUST_SRC}/flyweight.rs
        ${_RUST_SRC}/handlerchain.rs
        ${_RUST_SRC}/helpers.rs
        ${_RUST_SRC}/interpreter.rs
        ${_RUST_SRC}/iterator.rs
        ${_RUST_SRC}/main.rs
        ${_RUST_SRC}/mediator.rs
        ${_RUST_SRC}/memento.rs
        ${_RUST_SRC}/nullobject.rs
        ${_RUST_SRC}/observer.rs
        ${_RUST_SRC}/proxy.rs
        ${_RUST_SRC}/state.rs
        ${_RUST_SRC}/strategy.rs
        ${_RUST_SRC}/visitor.rs
        ${_RUST_SRC}/adapter/adapter_backend.rs
        ${_RUST_SRC}/adapter/adapter_functions.rs
        ${_RUST_SRC}/bridge/bridge_consolelogger.rs
        ${_RUST_SRC}/bridge/bridge_filelogger.rs
        ${_RUST_SRC}/bridge/bridge_ilogger_trait.rs
        ${_RUST_SRC}/bridge/bridge_logger.rs
        ${_RUST_SRC}/bridge/bridge_loghelper.rs
        ${_RUST_SRC}/bridge/bridge_nulllogger.rs
        ${_RUST_SRC}/command/command_commands.rs
        ${_RUST_SRC}/command/command_icommand_trait.rs
        ${_RUST_SRC}/command/command_textobject.rs
        ${_RUST_SRC}/composite/composite_direntry.rs
        ${_RUST_SRC}/composite/composite_fileaccess.rs
        ${_RUST_SRC}/composite/composite_filedirentry_trait.rs
        ${_RUST_SRC}/composite/composite_fileentry.rs
        ${_RUST_SRC}/decorator/decorator_irenderelement_trait.rs
        ${_RUST_SRC}/decorator/decorator_redforeground.rs
        ${_RUST_SRC}/decorator/decorator_textelement.rs
        ${_RUST_SRC}/decorator/decorator_underline.rs
        ${_RUST_SRC}/decorator/decorator_whitebackground.rs
        ${_RUST_SRC}/facade/facade_complicatedsubsystem.rs
        ${_RUST_SRC}/facade/facade_devicenetworkhighlevel.rs
        ${_RUST_SRC}/facade/facade_idevicenetworkhighlevel_trait.rs
        ${_RUST_SRC}/facade/facade_idevicenetworklowlevel_trait.rs
        ${_RUST_SRC}/flyweight/flyweight_bigresource.rs
        ${_RUST_SRC}/flyweight/flyweight_bigresource_manager.rs
        ${_RUST_SRC}/flyweight/flyweight_context.rs
        ${_RUST_SRC}/flyweight/flyweight_display.rs
        ${_RUST_SRC}/flyweight/flyweight_image.rs
        ${_RUST_SRC}/handlerchain/handlerchain_handlerchain.rs
        ${_RUST_SRC}/handlerchain/handlerchain_imessagehandler_trait.rs
        ${_RUST_SRC}/handlerchain/handlerchain_message.rs
        ${_RUST_SRC}/handlerchain/handlerchain_messagewindow.rs
        ${_RUST_SRC}/helpers/cursor.rs
        ${_RUST_SRC}/helpers/key_input.rs
        ${_RUST_SRC}/helpers/random.rs
        ${_RUST_SRC}/helpers/titlecase.rs
        ${_RUST_SRC}/interpreter/interpreter_interpreter.rs
        ${_RUST_SRC}/iterator/iterator_iiterator_trait.rs
        ${_RUST_SRC}/iterator/iterator_iterators.rs
        ${_RUST_SRC}/mediator/mediator_grouplist.rs
        ${_RUST_SRC}/mediator/mediator_usergroupmediator.rs
        ${_RUST_SRC}/mediator/mediator_userlist.rs
        ${_RUST_SRC}/memento/memento_textobject.rs
        ${_RUST_SRC}/nullobject/nullobject_imovecommand_trait.rs
        ${_RUST_SRC}/nullobject/nullobject_movecommands.rs
        ${_RUST_SRC}/nullobject/nullobject_moveprocessor.rs
        ${_RUST_SRC}/observer/observer_inumberchanged_trait.rs
        ${_RUST_SRC}/observer/observer_numberproducer.rs
        ${_RUST_SRC}/observer/observer_observers.rs
        ${_RUST_SRC}/proxy/proxy_iworkbyproxy_trait.rs
        ${_RUST_SRC}/proxy/proxy_proxy.rs
        ${_RUST_SRC}/proxy/proxy_real.rs
        ${_RUST_SRC}/state/state_context.rs
        ${_RUST_SRC}/state/state_istatebehavior_trait.rs
        ${_RUST_SRC}/state/state_istatecontext_trait.rs
        ${_RUST_SRC}/strategy/strategy_entryinformation.rs
        ${_RUST_SRC}/strategy/strategy_isortentries_trait.rs
        ${_RUST_SRC}/strategy/strategy_showentries.rs
        ${_RUST_SRC}/strategy/strategy_sortentries.rs
        ${_RUST_SRC}/visitor/visitor_ordervisitor.rs
        ${_RUST_SRC}/visitor/visitor_shop.rs
        ${_RUST_SRC}/visitor/visitor_village.rs
)

source_group("adapter" REGULAR_EXPRESSION ${_RUST_SRC}/adapter/.*\.rs)
source_group("bridge" REGULAR_EXPRESSION ${_RUST_SRC}/bridge/.*\.rs)
source_group("command" REGULAR_EXPRESSION ${_RUST_SRC}/command/.*\.rs)
source_group("composite" REGULAR_EXPRESSION ${_RUST_SRC}/composite/.*\.rs)
source_group("decorator" REGULAR_EXPRESSION ${_RUST_SRC}/decorator/.*\.rs)
source_group("facade" REGULAR_EXPRESSION ${_RUST_SRC}/facade/.*\.rs)
source_group("flyweight" REGULAR_EXPRESSION ${_RUST_SRC}/flyweight/.*\.rs)
source_group("handlerchain" REGULAR_EXPRESSION ${_RUST_SRC}/handlerchain/.*\.rs)
source_group("helpers" REGULAR_EXPRESSION ${_RUST_SRC}/helpers/.*\.rs)
source_group("interpreter" REGULAR_EXPRESSION ${_RUST_SRC}/interpreter/.*\.rs)
source_group("iterator" REGULAR_EXPRESSION ${_RUST_SRC}/iterator/.*\.rs)
source_group("mediator" REGULAR_EXPRESSION ${_RUST_SRC}/mediator/.*\.rs)
source_group("memento" REGULAR_EXPRESSION ${_RUST_SRC}/memento/.*\.rs)
source_group("nullobject" REGULAR_EXPRESSION ${_RUST_SRC}/nullobject/.*\.rs)
source_group("observer" REGULAR_EXPRESSION ${_RUST_SRC}/observer/.*\.rs)
source_group("proxy" REGULAR_EXPRESSION ${_RUST_SRC}/proxy/.*\.rs)
source_group("state" REGULAR_EXPRESSION ${_RUST_SRC}/state/.*\.rs)
source_group("strategy" REGULAR_EXPRESSION ${_RUST_SRC}/strategy/.*\.rs)
source_group("visitor" REGULAR_EXPRESSION ${_RUST_SRC}/visitor/.*\.rs)

# Since TARGET generators are not supported in custom commands, get the needed
# file paths and directories first and pass those in simple variables.
set(ADAPTER_LIBRARY "$<TARGET_FILE:Adapter_BackEnd>")
set(ADAPTER_PDB "$<TARGET_PDB_FILE:Adapter_BackEnd>")
set(RUST_OUTPUT_DIR "${CMAKE_BINARY_DIR}/rust/$<CONFIG>")

add_custom_command(TARGET DesignPatternExamples_rust POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${ADAPTER_LIBRARY} ${RUST_OUTPUT_DIR}
                  )

add_custom_command(TARGET DesignPatternExamples_rust POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                       "-DFILE_TO_COPY=${ADAPTER_PDB}"
                       "-DDESTINATION=${RUST_OUTPUT_DIR}"
                       -P ${CMAKE_SOURCE_DIR}/copyfile_if_exists.cmake
                   COMMENT "Copying ${ADAPTER_PDB} if it exists."
                  )

# Generate Rust documentation.
add_custom_target(RustDocs ALL
        DEPENDS doc/design_pattern_examples_rust/index.html
)

add_custom_command(OUTPUT doc/design_pattern_examples_rust/index.html
    COMMAND ${CMAKE_COMMAND} -E env
                "CARGO_BUILD_TARGET_DIR=${CMAKE_BINARY_DIR}/rust"
                ${CARGO} doc
    WORKING_DIRECTORY ${_RUST_ROOT}
    COMMAND_EXPAND_LISTS
    VERBATIM
)
