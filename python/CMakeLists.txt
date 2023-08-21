set(PYTHON_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/DesignPatternExamples_python)
set(PYTHON_OUTPUT_DIR ${CMAKE_BINARY_DIR}/python/DesignPatternExamples_python)

add_custom_target(DesignPatternExamples_python ALL
                  DEPENDS python_files
                 )

add_dependencies(DesignPatternExamples_python Adapter_BackEnd)


configure_file(${PYTHON_SOURCE_DIR}/version.py.in ${PYTHON_OUTPUT_DIR}/version.py)

add_custom_command(OUTPUT python_files
                    COMMAND ${CMAKE_COMMAND} -E echo "Copying python files over..."
                    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
                        ${PYTHON_SOURCE_DIR} ${PYTHON_OUTPUT_DIR}
                    COMMAND ${CMAKE_COMMAND} -E rm ${PYTHON_OUTPUT_DIR}/version.py.in
                    VERBATIM
                    COMMAND_EXPAND_LISTS
                  )

set_source_files_properties(python_files PROPERTIES SYMBOLIC true)

target_sources(DesignPatternExamples_python
    PRIVATE
        ${PYTHON_SOURCE_DIR}/__init__.py
        ${PYTHON_SOURCE_DIR}/__main__.py
        ${PYTHON_SOURCE_DIR}/enablevtmode.py
        ${PYTHON_SOURCE_DIR}/program.py
        ${PYTHON_SOURCE_DIR}/version.py.in
    PRIVATE
        ${PYTHON_SOURCE_DIR}/adapter/adapter_backendfunctions.py
        ${PYTHON_SOURCE_DIR}/adapter/adapter_exercise.py
        ${PYTHON_SOURCE_DIR}/adapter/adapter_frontendclass.py
        ${PYTHON_SOURCE_DIR}/adapter/__init__.py
        ${PYTHON_SOURCE_DIR}/bridge/bridge_consolelogger.py
        ${PYTHON_SOURCE_DIR}/bridge/bridge_exercise.py
        ${PYTHON_SOURCE_DIR}/bridge/bridge_filelogger.py
        ${PYTHON_SOURCE_DIR}/bridge/bridge_logger.py
        ${PYTHON_SOURCE_DIR}/bridge/bridge_loggerhelpers.py
        ${PYTHON_SOURCE_DIR}/bridge/bridge_loggerinterface.py
        ${PYTHON_SOURCE_DIR}/bridge/bridge_nulllogger.py
        ${PYTHON_SOURCE_DIR}/bridge/__init__.py
        ${PYTHON_SOURCE_DIR}/command/command_classes.py
        ${PYTHON_SOURCE_DIR}/command/command_exercise.py
        ${PYTHON_SOURCE_DIR}/command/__init__.py
        ${PYTHON_SOURCE_DIR}/composite/composite_exercise.py
        ${PYTHON_SOURCE_DIR}/composite/composite_fileaccess.py
        ${PYTHON_SOURCE_DIR}/composite/composite_filedirentry.py
        ${PYTHON_SOURCE_DIR}/composite/__init__.py
        ${PYTHON_SOURCE_DIR}/decorator/decorator_classes.py
        ${PYTHON_SOURCE_DIR}/decorator/decorator_exercise.py
        ${PYTHON_SOURCE_DIR}/decorator/__init__.py
        ${PYTHON_SOURCE_DIR}/facade/facadesubsystem_interface.py
        ${PYTHON_SOURCE_DIR}/facade/facade_complicatedsubsystem.py
        ${PYTHON_SOURCE_DIR}/facade/facade_exercise.py
        ${PYTHON_SOURCE_DIR}/facade/facade_highlevelsystem.py
        ${PYTHON_SOURCE_DIR}/facade/facade_interface.py
        ${PYTHON_SOURCE_DIR}/facade/__init__.py
        ${PYTHON_SOURCE_DIR}/flyweight/flyweight_classes.py
        ${PYTHON_SOURCE_DIR}/flyweight/flyweight_exercise.py
        ${PYTHON_SOURCE_DIR}/flyweight/flyweight_helpers.py
        ${PYTHON_SOURCE_DIR}/flyweight/__init__.py
        ${PYTHON_SOURCE_DIR}/handlerchain/handlerchain_class.py
        ${PYTHON_SOURCE_DIR}/handlerchain/handlerchain_exercise.py
        ${PYTHON_SOURCE_DIR}/handlerchain/handlerchain_messagewindow_class.py
        ${PYTHON_SOURCE_DIR}/handlerchain/handlerchain_message_class.py
        ${PYTHON_SOURCE_DIR}/handlerchain/__init__.py
        ${PYTHON_SOURCE_DIR}/interpreter/interpreter_class.py
        ${PYTHON_SOURCE_DIR}/interpreter/interpreter_exercise.py
        ${PYTHON_SOURCE_DIR}/interpreter/__init__.py
        ${PYTHON_SOURCE_DIR}/iterator/iterator_class.py
        ${PYTHON_SOURCE_DIR}/iterator/iterator_exercise.py
        ${PYTHON_SOURCE_DIR}/iterator/__init__.py
        ${PYTHON_SOURCE_DIR}/mediator/mediator_class.py
        ${PYTHON_SOURCE_DIR}/mediator/mediator_exercise.py
        ${PYTHON_SOURCE_DIR}/mediator/mediator_group_classes.py
        ${PYTHON_SOURCE_DIR}/mediator/mediator_user_classes.py
        ${PYTHON_SOURCE_DIR}/mediator/__init__.py
        ${PYTHON_SOURCE_DIR}/memento/memento.py
        ${PYTHON_SOURCE_DIR}/memento/memento_exercise.py
        ${PYTHON_SOURCE_DIR}/memento/__init__.py
        ${PYTHON_SOURCE_DIR}/nullobject/nullobject_exercise.py
        ${PYTHON_SOURCE_DIR}/nullobject/null_object.py
        ${PYTHON_SOURCE_DIR}/nullobject/__init__.py
        ${PYTHON_SOURCE_DIR}/observer/observersubject_numberproducer.py
        ${PYTHON_SOURCE_DIR}/observer/observer_class.py
        ${PYTHON_SOURCE_DIR}/observer/observer_exercise.py
        ${PYTHON_SOURCE_DIR}/observer/__init__.py
        ${PYTHON_SOURCE_DIR}/proxy/proxy_class.py
        ${PYTHON_SOURCE_DIR}/proxy/proxy_class_real.py
        ${PYTHON_SOURCE_DIR}/proxy/proxy_exercise.py
        ${PYTHON_SOURCE_DIR}/proxy/proxy_interface.py
        ${PYTHON_SOURCE_DIR}/proxy/__init__.py
        ${PYTHON_SOURCE_DIR}/state/state_class.py
        ${PYTHON_SOURCE_DIR}/state/state_exercise.py
        ${PYTHON_SOURCE_DIR}/state/state_interface.py
        ${PYTHON_SOURCE_DIR}/state/_state_class_private.py
        ${PYTHON_SOURCE_DIR}/state/__init__.py
        ${PYTHON_SOURCE_DIR}/strategy/strategy_entryinformation.py
        ${PYTHON_SOURCE_DIR}/strategy/strategy_exercise.py
        ${PYTHON_SOURCE_DIR}/strategy/strategy_isortentries.py
        ${PYTHON_SOURCE_DIR}/strategy/strategy_showentries_class.py
        ${PYTHON_SOURCE_DIR}/strategy/strategy_sortentries_class.py
        ${PYTHON_SOURCE_DIR}/strategy/__init__.py
        ${PYTHON_SOURCE_DIR}/visitor/visitor_class.py
        ${PYTHON_SOURCE_DIR}/visitor/visitor_element_classes.py
        ${PYTHON_SOURCE_DIR}/visitor/visitor_exercise.py
        ${PYTHON_SOURCE_DIR}/visitor/visitor_ordervisitor.py
        ${PYTHON_SOURCE_DIR}/visitor/visitor_village.py
        ${PYTHON_SOURCE_DIR}/visitor/visitor_visitor_shop.py
        ${PYTHON_SOURCE_DIR}/visitor/__init__.py
)

source_group("adapter" REGULAR_EXPRESSION ${PYTHON_SOURCE_DIR}/adapter/.*\.py)
source_group("bridge" REGULAR_EXPRESSION ${PYTHON_SOURCE_DIR}/bridge/.*\.py)
source_group("command" REGULAR_EXPRESSION ${PYTHON_SOURCE_DIR}/command/.*\.py)
source_group("composite" REGULAR_EXPRESSION ${PYTHON_SOURCE_DIR}/composite/.*\.py)
source_group("decorator" REGULAR_EXPRESSION ${PYTHON_SOURCE_DIR}/decorator/.*\.py)
source_group("facade" REGULAR_EXPRESSION ${PYTHON_SOURCE_DIR}/facade/.*\.py)
source_group("flyweight" REGULAR_EXPRESSION ${PYTHON_SOURCE_DIR}/flyweight/.*\.py)
source_group("handlerchain" REGULAR_EXPRESSION ${PYTHON_SOURCE_DIR}/handlerchain/.*\.py)
source_group("helpers" REGULAR_EXPRESSION ${PYTHON_SOURCE_DIR}/helpers/.*\.py)
source_group("interpreter" REGULAR_EXPRESSION ${PYTHON_SOURCE_DIR}/interpreter/.*\.py)
source_group("iterator" REGULAR_EXPRESSION ${PYTHON_SOURCE_DIR}/iterator/.*\.py)
source_group("mediator" REGULAR_EXPRESSION ${PYTHON_SOURCE_DIR}/mediator/.*\.py)
source_group("memento" REGULAR_EXPRESSION ${PYTHON_SOURCE_DIR}/memento/.*\.py)
source_group("nullobject" REGULAR_EXPRESSION ${PYTHON_SOURCE_DIR}/nullobject/.*\.py)
source_group("observer" REGULAR_EXPRESSION ${PYTHON_SOURCE_DIR}/observer/.*\.py)
source_group("proxy" REGULAR_EXPRESSION ${PYTHON_SOURCE_DIR}/proxy/.*\.py)
source_group("state" REGULAR_EXPRESSION ${PYTHON_SOURCE_DIR}/state/.*\.py)
source_group("strategy" REGULAR_EXPRESSION ${PYTHON_SOURCE_DIR}/strategy/.*\.py)
source_group("visitor" REGULAR_EXPRESSION ${PYTHON_SOURCE_DIR}/visitor/.*\.py)


# Since TARGET generators are not supported in custom commands, get the needed
# file paths and directories first and pass those in simple variables.
set(IS_WINDOWS $<STREQUAL:${CMAKE_HOST_SYSTEM_NAME},Windows>)
set(ADAPTER_LIBRARY "$<TARGET_FILE:Adapter_BackEnd>")
set(ADAPTER_PDB "$<${IS_WINDOWS}:$<TARGET_PDB_FILE:Adapter_BackEnd>>")
set(PYTHON_OUTPUT_DIR "${CMAKE_BINARY_DIR}/python/DesignPatternExamples_python/adapter")

add_custom_command(TARGET DesignPatternExamples_python POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${ADAPTER_LIBRARY} ${PYTHON_OUTPUT_DIR}
                  )

add_custom_command(TARGET DesignPatternExamples_python POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                       "-DFILE_TO_COPY=${ADAPTER_PDB}"
                       "-DDESTINATION=${PYTHON_OUTPUT_DIR}"
                       -P ${CMAKE_SOURCE_DIR}/copyfile_if_exists.cmake
                   COMMENT "Copying ${ADAPTER_PDB} if it exists."
                  )
