# Rust uses cargo for most of its build needs so all we need here is the cargo
# program.  If cargo is not found, rust is most likely not installed.
find_program(CARGO cargo REQUIRED)

set(RUST_ROOT "${CMAKE_SOURCE_DIR}/rust/design_pattern_examples_rust")
set(RUST_SRC "${RUST_ROOT}/src")
set(RUST_BINARY_DIR "${CMAKE_BINARY_DIR}/rust")

# Rust is not supported directly in cmake so create a custom target and
# link it to a custom command that does the actual building.
add_custom_target(DesignPatternExamples_rust ALL
    DEPENDS rust_files
    VERBATIM
)

add_dependencies(DesignPatternExamples_rust Adapter_BackEnd)

# The TARGET_* generators don't seem to work in custom commands so use the
# generator to create a simple variable outside the custom command and pass
# the variable into the custom command.
set(ADAPTER_BINARY_DIR "$<TARGET_FILE_DIR:Adapter_BackEnd>")

# This custom command builds the rust example, sending the output to the cmake
# build directory.
#
# The ADAPTER_BINARY_DIR environment variable is used in the build.rs build
# script to set the location of the import library provided by
# Adapter_BackEnd dynamic library.
add_custom_command(OUTPUT rust_files
    COMMAND ${CMAKE_COMMAND} -E env
                "ADAPTER_BINARY_DIR=${ADAPTER_BINARY_DIR}"
                ${CARGO} build $<$<CONFIG:Release>:--release> --target-dir ${RUST_BINARY_DIR}
    WORKING_DIRECTORY ${RUST_ROOT}
    COMMAND_EXPAND_LISTS
    VERBATIM
)

set_source_files_properties(rust_files PROPERTIES SYMBOLIC true)

target_sources(DesignPatternExamples_rust
    PRIVATE
        ${RUST_SRC}/adapter.rs
        ${RUST_SRC}/bridge.rs
        ${RUST_SRC}/command.rs
        ${RUST_SRC}/composite.rs
        ${RUST_SRC}/decorator.rs
        ${RUST_SRC}/facade.rs
        ${RUST_SRC}/flyweight.rs
        ${RUST_SRC}/handlerchain.rs
        ${RUST_SRC}/helpers.rs
        ${RUST_SRC}/interpreter.rs
        ${RUST_SRC}/iterator.rs
        ${RUST_SRC}/main.rs
        ${RUST_SRC}/mediator.rs
        ${RUST_SRC}/memento.rs
        ${RUST_SRC}/nullobject.rs
        ${RUST_SRC}/observer.rs
        ${RUST_SRC}/proxy.rs
        ${RUST_SRC}/state.rs
        ${RUST_SRC}/strategy.rs
        ${RUST_SRC}/visitor.rs
        ${RUST_SRC}/adapter/adapter_backend.rs
        ${RUST_SRC}/adapter/adapter_functions.rs
        ${RUST_SRC}/bridge/bridge_consolelogger.rs
        ${RUST_SRC}/bridge/bridge_filelogger.rs
        ${RUST_SRC}/bridge/bridge_ilogger_trait.rs
        ${RUST_SRC}/bridge/bridge_logger.rs
        ${RUST_SRC}/bridge/bridge_loghelper.rs
        ${RUST_SRC}/bridge/bridge_nulllogger.rs
        ${RUST_SRC}/command/command_commands.rs
        ${RUST_SRC}/command/command_icommand_trait.rs
        ${RUST_SRC}/command/command_textobject.rs
        ${RUST_SRC}/composite/composite_direntry.rs
        ${RUST_SRC}/composite/composite_fileaccess.rs
        ${RUST_SRC}/composite/composite_filedirentry_trait.rs
        ${RUST_SRC}/composite/composite_fileentry.rs
        ${RUST_SRC}/decorator/decorator_irenderelement_trait.rs
        ${RUST_SRC}/decorator/decorator_redforeground.rs
        ${RUST_SRC}/decorator/decorator_textelement.rs
        ${RUST_SRC}/decorator/decorator_underline.rs
        ${RUST_SRC}/decorator/decorator_whitebackground.rs
        ${RUST_SRC}/facade/facade_complicatedsubsystem.rs
        ${RUST_SRC}/facade/facade_devicenetworkhighlevel.rs
        ${RUST_SRC}/facade/facade_idevicenetworkhighlevel_trait.rs
        ${RUST_SRC}/facade/facade_idevicenetworklowlevel_trait.rs
        ${RUST_SRC}/flyweight/flyweight_bigresource.rs
        ${RUST_SRC}/flyweight/flyweight_bigresource_manager.rs
        ${RUST_SRC}/flyweight/flyweight_context.rs
        ${RUST_SRC}/flyweight/flyweight_display.rs
        ${RUST_SRC}/flyweight/flyweight_image.rs
        ${RUST_SRC}/handlerchain/handlerchain_handlerchain.rs
        ${RUST_SRC}/handlerchain/handlerchain_imessagehandler_trait.rs
        ${RUST_SRC}/handlerchain/handlerchain_message.rs
        ${RUST_SRC}/handlerchain/handlerchain_messagewindow.rs
        ${RUST_SRC}/helpers/cursor.rs
        ${RUST_SRC}/helpers/key_input.rs
        ${RUST_SRC}/helpers/random.rs
        ${RUST_SRC}/helpers/titlecase.rs
        ${RUST_SRC}/interpreter/interpreter_interpreter.rs
        ${RUST_SRC}/iterator/iterator_iiterator_trait.rs
        ${RUST_SRC}/iterator/iterator_iterators.rs
        ${RUST_SRC}/mediator/mediator_grouplist.rs
        ${RUST_SRC}/mediator/mediator_usergroupmediator.rs
        ${RUST_SRC}/mediator/mediator_userlist.rs
        ${RUST_SRC}/memento/memento_textobject.rs
        ${RUST_SRC}/nullobject/nullobject_imovecommand_trait.rs
        ${RUST_SRC}/nullobject/nullobject_movecommands.rs
        ${RUST_SRC}/nullobject/nullobject_moveprocessor.rs
        ${RUST_SRC}/observer/observer_inumberchanged_trait.rs
        ${RUST_SRC}/observer/observer_numberproducer.rs
        ${RUST_SRC}/observer/observer_observers.rs
        ${RUST_SRC}/proxy/proxy_iworkbyproxy_trait.rs
        ${RUST_SRC}/proxy/proxy_proxy.rs
        ${RUST_SRC}/proxy/proxy_real.rs
        ${RUST_SRC}/state/state_context.rs
        ${RUST_SRC}/state/state_istatebehavior_trait.rs
        ${RUST_SRC}/state/state_istatecontext_trait.rs
        ${RUST_SRC}/strategy/strategy_entryinformation.rs
        ${RUST_SRC}/strategy/strategy_isortentries_trait.rs
        ${RUST_SRC}/strategy/strategy_showentries.rs
        ${RUST_SRC}/strategy/strategy_sortentries.rs
        ${RUST_SRC}/visitor/visitor_ordervisitor.rs
        ${RUST_SRC}/visitor/visitor_shop.rs
        ${RUST_SRC}/visitor/visitor_village.rs
)

source_group("adapter" REGULAR_EXPRESSION ${RUST_SRC}/adapter/.*\.rs)
source_group("bridge" REGULAR_EXPRESSION ${RUST_SRC}/bridge/.*\.rs)
source_group("command" REGULAR_EXPRESSION ${RUST_SRC}/command/.*\.rs)
source_group("composite" REGULAR_EXPRESSION ${RUST_SRC}/composite/.*\.rs)
source_group("decorator" REGULAR_EXPRESSION ${RUST_SRC}/decorator/.*\.rs)
source_group("facade" REGULAR_EXPRESSION ${RUST_SRC}/facade/.*\.rs)
source_group("flyweight" REGULAR_EXPRESSION ${RUST_SRC}/flyweight/.*\.rs)
source_group("handlerchain" REGULAR_EXPRESSION ${RUST_SRC}/handlerchain/.*\.rs)
source_group("helpers" REGULAR_EXPRESSION ${RUST_SRC}/helpers/.*\.rs)
source_group("interpreter" REGULAR_EXPRESSION ${RUST_SRC}/interpreter/.*\.rs)
source_group("iterator" REGULAR_EXPRESSION ${RUST_SRC}/iterator/.*\.rs)
source_group("mediator" REGULAR_EXPRESSION ${RUST_SRC}/mediator/.*\.rs)
source_group("memento" REGULAR_EXPRESSION ${RUST_SRC}/memento/.*\.rs)
source_group("nullobject" REGULAR_EXPRESSION ${RUST_SRC}/nullobject/.*\.rs)
source_group("observer" REGULAR_EXPRESSION ${RUST_SRC}/observer/.*\.rs)
source_group("proxy" REGULAR_EXPRESSION ${RUST_SRC}/proxy/.*\.rs)
source_group("state" REGULAR_EXPRESSION ${RUST_SRC}/state/.*\.rs)
source_group("strategy" REGULAR_EXPRESSION ${RUST_SRC}/strategy/.*\.rs)
source_group("visitor" REGULAR_EXPRESSION ${RUST_SRC}/visitor/.*\.rs)

# Since TARGET generators are not supported in custom commands, get the needed
# file paths and directories first and pass those in simple variables.
set(IS_WINDOWS $<STREQUAL:${CMAKE_HOST_SYSTEM_NAME},Windows>)
set(ADAPTER_LIBRARY "$<TARGET_FILE:Adapter_BackEnd>")
set(ADAPTER_PDB "$<${IS_WINDOWS}:$<TARGET_PDB_FILE:Adapter_BackEnd>>")
# Note: Rust prefers lowercase for the configuration directory
set(RUST_OUTPUT_DIR "${RUST_BINARY_DIR}/$<LOWER_CASE:$<CONFIG>>/")

# Copy the Adapter_BackEnd dynamic library to the rust output directory so
# the rust program can be run from there.
add_custom_command(TARGET DesignPatternExamples_rust POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${ADAPTER_LIBRARY} ${RUST_OUTPUT_DIR}
                  )

# Copy the Adapter_BackEnd dynamic library debug symbol file, if it exists, to
# the rust output directory so the rust program can be run from there.
add_custom_command(TARGET DesignPatternExamples_rust POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                       "-DFILE_TO_COPY=${ADAPTER_PDB}"
                       "-DDESTINATION=${RUST_OUTPUT_DIR}"
                       -P ${CMAKE_SOURCE_DIR}/copyfile_if_exists.cmake
                   COMMENT "Copying ${ADAPTER_PDB} if it exists."
                  )

#==============================================================================

# Generate Rust documentation.
add_custom_target(RustDocs ALL
        DEPENDS rust_docs
)

add_custom_command(OUTPUT rust_docs
    COMMAND ${CMAKE_COMMAND} -E env
                ${CARGO} doc --target-dir=${RUST_BINARY_DIR}
    WORKING_DIRECTORY ${RUST_ROOT}
    COMMAND_EXPAND_LISTS
    VERBATIM
)

set_source_files_properties(rust_docs PROPERTIES SYMBOLIC true)
