# This can only be used on Windows, unfortunately, as CMake only supports
# Visual Studio for C# compilation.


configure_file(DesignPatternExamples_csharp.csproj.in DesignPatternExamples_csharp.csproj)

add_custom_target(DesignPatternExamples_csharp ALL
    DEPENDS csharp_project)

set(ADAPTER_LIBRARY "$<TARGET_FILE:Adapter_BackEnd>")

if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL Windows)
  set(ADAPTER_PDB "$<TARGET_PDB_FILE:Adapter_BackEnd>")
else()
  set(ADAPTER_PDB "")
endif()

if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL Windows)
  set(CSHARP_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/$<IF:$<CONFIG:Release>,Release,Debug>)
else()
  set(CSHARP_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
endif()

add_custom_command(OUTPUT csharp_project
    COMMAND ${CMAKE_COMMAND} -E env
        dotnet build -a x64 ${CMAKE_BINARY_DIR}/csharp/DesignPatternExamples_csharp.csproj
        -o ${CSHARP_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${ADAPTER_LIBRARY} ${CSHARP_BINARY_DIR}
        VERBATIM
    COMMAND ${CMAKE_COMMAND}
        "-DFILE_TO_COPY=${ADAPTER_PDB}"
        "-DDESTINATION=${CSHARP_OUTPUT_DIR}"
        -P ${CMAKE_SOURCE_DIR}/copyfile_if_exists.cmake
)

set_source_files_properties(csharp_project PROPERTIES SYMBOLIC true)

add_dependencies(DesignPatternExamples_csharp Adapter_BackEnd)


# The following are used only when using add_executable() or add_library() for
# a C# project.  Keeping these for now; not sure if they will be needed in the
# future.
# target_sources(DesignPatternExamples_csharp
#     PRIVATE
#         App.config
#         Properties/AssemblyInfo.cs
#     PRIVATE
#         Adapter_BackEndFunctions.cs
#         Adapter_Exercise.cs
#         Adapter_FrontEndClass.cs
#         Bridge_ConsoleLogger.cs
#         Bridge_Exercise.cs
#         Bridge_FIleLogger.cs
#         Bridge_Logger.cs
#         Bridge_LoggerHelpers.cs
#         Bridge_LoggerInterface.cs
#         Bridge_NullLogger.cs
#         Command.cs
#         Command_Exercise.cs
#         Composite_Exercise.cs
#         Composite_FileAccess.cs
#         Composite_FileDirEntry.cs
#         Decorator_Classes.cs
#         Decorator_Exercise.cs
#         EnableVTModeForWindowsConsole.cs
#         Facade_ComplicatedSubSystem.cs
#         Facade_Exercise.cs
#         Facade_Interfaces.cs
#         Flyweight_Class.cs
#         Flyweight_Exercise.cs
#         HandlerChain_Class.cs
#         HandlerChain_Exercise.cs
#         HandlerChain_Message_Class.cs
#         HandlerChain_MessageWindow_Class.cs
#         Interpreter_Class.cs
#         Interpreter_Exercise.cs
#         Iterator_Exercise.cs
#         IteratorContainer_Class.cs
#         Mediator_Class.cs
#         Mediator_Exercise.cs
#         Mediator_Group_Classes.cs
#         Mediator_User_Classes.cs
#         Memento.cs
#         Memento_Exercise.cs
#         Null_Object.cs
#         NullObject_Exercise.cs
#         Observer_Class.cs
#         Observer_Exercise.cs
#         ObserverSubject_NumberProducer.cs
#         Private_Class.cs
#         Program.cs
#         Proxy_Class.cs
#         Proxy_Exercise.cs
#         State_Class.cs
#         State_Exercise.cs
#         Strategy_Exercise.cs
#         Strategy_ShowEntries_Class.cs
#         Strategy_SortEntries_Classes.cs
#         Templates.cs
#         Visitor_Element_Classes.cs
#         Visitor_Exercise.cs
#         Visitor_Village.cs
#         Visitor_Visitor_Class.cs
# )


# set_property(TARGET DesignPatternExamples_csharp
#              PROPERTY VS_GLOBAL_ROOTNAMESPACE DesignPatternExamples_csharp
#             )

# set_property(TARGET DesignPatternExamples_csharp
#              PROPERTY VS_DOTNET_REFERENCES
#                 "Microsoft.CSharp"
#                 "System"
#                 "System.Core"
#                 "System.Data"
#                 "System.Data.DataSetExtensions"
#                 "System.Xml"
#                 "System.Xml.Linq"
#              )
