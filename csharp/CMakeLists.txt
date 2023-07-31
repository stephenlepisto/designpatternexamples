# This can only be used on Windows, unfortunately, as CMake only supports
# Visual Studio for C# compilation.

if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL Windows)
add_executable(DesignPatternExamples_csharp)

add_dependencies(DesignPatternExamples_csharp Adapter_BackEnd)

target_sources(DesignPatternExamples_csharp
    PRIVATE
        App.config
        Properties/AssemblyInfo.cs
    PRIVATE
        Adapter_BackEndFunctions.cs
        Adapter_Exercise.cs
        Adapter_FrontEndClass.cs
        Bridge_ConsoleLogger.cs
        Bridge_Exercise.cs
        Bridge_FIleLogger.cs
        Bridge_Logger.cs
        Bridge_LoggerHelpers.cs
        Bridge_LoggerInterface.cs
        Bridge_NullLogger.cs
        Command.cs
        Command_Exercise.cs
        Composite_Exercise.cs
        Composite_FileAccess.cs
        Composite_FileDirEntry.cs
        Decorator_Classes.cs
        Decorator_Exercise.cs
        EnableVTModeForWindowsConsole.cs
        Facade_ComplicatedSubSystem.cs
        Facade_Exercise.cs
        Facade_Interfaces.cs
        Flyweight_Class.cs
        Flyweight_Exercise.cs
        HandlerChain_Class.cs
        HandlerChain_Exercise.cs
        HandlerChain_Message_Class.cs
        HandlerChain_MessageWindow_Class.cs
        Interpreter_Class.cs
        Interpreter_Exercise.cs
        Iterator_Exercise.cs
        IteratorContainer_Class.cs
        Mediator_Class.cs
        Mediator_Exercise.cs
        Mediator_Group_Classes.cs
        Mediator_User_Classes.cs
        Memento.cs
        Memento_Exercise.cs
        Null_Object.cs
        NullObject_Exercise.cs
        Observer_Class.cs
        Observer_Exercise.cs
        ObserverSubject_NumberProducer.cs
        Private_Class.cs
        Program.cs
        Proxy_Class.cs
        Proxy_Exercise.cs
        State_Class.cs
        State_Exercise.cs
        Strategy_Exercise.cs
        Strategy_ShowEntries_Class.cs
        Strategy_SortEntries_Classes.cs
        Templates.cs
        Visitor_Element_Classes.cs
        Visitor_Exercise.cs
        Visitor_Village.cs
        Visitor_Visitor_Class.cs
)

set_property(TARGET DesignPatternExamples_csharp
             PROPERTY VS_GLOBAL_ROOTNAMESPACE DesignPatternExamples_csharp
            )

set_property(TARGET DesignPatternExamples_csharp
             PROPERTY VS_DOTNET_REFERENCES
                "Microsoft.CSharp"
                "System"
                "System.Core"
                "System.Data"
                "System.Data.DataSetExtensions"
                "System.Xml"
                "System.Xml.Linq"
             )

# Since TARGET generators are not supported in custom commands, get the needed
# file paths and directories first and pass those in simple variables.
set(ADAPTER_LIBRARY "$<TARGET_FILE:Adapter_BackEnd>")
set(ADAPTER_PDB "$<TARGET_PDB_FILE:Adapter_BackEnd>")
set(CSHARP_OUTPUT_DIR "$<TARGET_FILE_DIR:DesignPatternExamples_csharp>")

add_custom_command(TARGET DesignPatternExamples_csharp POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${ADAPTER_LIBRARY} ${CSHARP_OUTPUT_DIR}
                  )

add_custom_command(TARGET DesignPatternExamples_csharp POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                       "-DFILE_TO_COPY=${ADAPTER_PDB}"
                       "-DDESTINATION=${CSHARP_OUTPUT_DIR}"
                       -P ${CMAKE_SOURCE_DIR}/copyfile_if_exists.cmake
                   COMMENT "Copying ${ADAPTER_PDB} if it exists."
                  )
endif()
