add_library(cxx_compiler_flags INTERFACE)
target_compile_features(cxx_compiler_flags INTERFACE cxx_std_20)
# Need to tell Microsoft compiler to enable the __cplusplus macro to match
# the C++ standard we are compiling against.
target_compile_options(cxx_compiler_flags INTERFACE "/Zc:__cplusplus")

add_executable(DesignPatternExamples_cpp)

target_link_libraries(DesignPatternExamples_cpp
                      PUBLIC Adapter_BackEnd
                      PUBLIC cxx_compiler_flags
                      )

target_sources(DesignPatternExamples_cpp
    PRIVATE
        Adapter_Exercise.h
        Adapter_FrontEndClass.h
        Bridge_ConsoleLogger.h
        Bridge_Exercise.h
        Bridge_FileLogger.h
        Bridge_Logger.h
        Bridge_LoggerHelpers.h
        Bridge_LoggerInterface.h
        Bridge_NullLogger.h
        Command_Classes.h
        Command_Exercise.h
        Composite_Exercise.h
        Composite_FileAccess.h
        Composite_FileDirEntry.h
        Decorator_Classes.h
        Decorator_Exercise.h
        Facade_Exercise.h
        Facade_Interface.h
        FacadeSubsystem_Interface.h
        Flyweight_Classes.h
        Flyweight_Exercise.h
        HandlerChain_Class.h
        HandlerChain_Exercise.h
        HandlerChain_Message_Class.h
        HandlerChain_MessageWindow_Class.h
        Interpreter_Class.h
        Interpreter_Exercise.h
        Iterator_Class.h
        Iterator_Exercise.h
        Mediator_Class.h
        Mediator_Exercise.h
        Mediator_Group_Classes.h
        Mediator_User_Classes.h
        Memento.h
        Memento_Exercise.h
        Null_Object.h
        NullObject_Exercise.h
        Observer_Class.h
        Observer_Exercise.h
        ObserverSubject_NumberProducer.h
        Proxy_Class.h
        Proxy_Exercise.h
        State_Class.h
        State_Exercise.h
        Strategy_EntryInformation.h
        Strategy_Exercise.h
        Strategy_ISortEntries.h
        Strategy_ShowEntries_Class.h
        Strategy_SortEntries_Classes.h
        Visitor_Element_Classes.h
        Visitor_Exercise.h
        Visitor_Shop.h
        Visitor_Village.h
        Visitor_Visitor_Class.h
    PRIVATE
        Adapter_Exercise.cpp
        Adapter_FrontEndClass.cpp
        Bridge_ConsoleLogger.cpp
        Bridge_Exercise.cpp
        Bridge_FileLogger.cpp
        Bridge_Logger.cpp
        Bridge_LoggerHelpers.cpp
        Bridge_NullLogger.cpp
        Command_Exercise.cpp
        Composite_Exercise.cpp
        Composite_FileAccess.cpp
        Decorator_Exercise.cpp
        Facade_ComplicatedSubSystem.cpp
        Facade_Exercise.cpp
        Facade_Interface.cpp
        Flyweight_Classes.cpp
        Flyweight_Exercise.cpp
        HandlerChain_Exercise.cpp
        HandlerChain_MessageWindow_Class.cpp
        Interpreter_Class.cpp
        Interpreter_Exercise.cpp
        Iterator_Class.cpp
        Iterator_Exercise.cpp
        Mediator_Exercise.cpp
        Memento_Exercise.cpp
        NullObject_Exercise.cpp
        Observer_Exercise.cpp
        program.cpp
        Proxy_Class.cpp
        Proxy_Exercise.cpp
        State_Class.cpp
        State_Exercise.cpp
        Strategy_Exercise.cpp
        Strategy_SortEntries_Classes.cpp
        Visitor_Element_Classes.cpp
        Visitor_Exercise.cpp
        Visitor_Village.cpp
    PRIVATE
        helpers/argumentinvalid_error.h
        helpers/argumentnull_error.h
        helpers/checkforkey.h
        helpers/cursor.h
        helpers/DateTime.h
        helpers/enablevtmode.h
        helpers/makelocaltime.h
        helpers/mapofstrings.h
        helpers/readkey.h
        helpers/replace.h
        helpers/sleep.h
        helpers/split.h
        helpers/stricmp.h
        helpers/stringlist.h
        helpers/strstri.h
        helpers/titlecase.h
        helpers/wcsstri.h
    PRIVATE
        helpers/checkforkey.cpp
        helpers/cursor.cpp
        helpers/DateTime.cpp
        helpers/enablevtmode.cpp
        helpers/makelocaltime.cpp
        helpers/readkey.cpp
        helpers/replace.cpp
        helpers/replacew.cpp
        helpers/sleep.cpp
        helpers/split.cpp
        helpers/splitw.cpp
        helpers/stricmp.cpp
        helpers/strstri.cpp
        helpers/titlecase.cpp
        helpers/wcsstri.cpp
    )

    # Group all helper/ files in the project group "Helper Files"
source_group("Helper Files" REGULAR_EXPRESSION helpers/.*)

add_custom_command(TARGET DesignPatternExamples_cpp POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy -t
    $<TARGET_FILE_DIR:DesignPatternExamples_cpp>
    $<TARGET_RUNTIME_DLLS:DesignPatternExamples_cpp>
  COMMAND_EXPAND_LISTS
)
