add_library(cxx_compiler_flags INTERFACE)
target_compile_features(cxx_compiler_flags INTERFACE cxx_std_20)
if(MSVC)
# Need to tell Microsoft compiler to enable the __cplusplus macro to match
# the C++ standard we are compiling against.
target_compile_options(cxx_compiler_flags INTERFACE "/Zc:__cplusplus")
target_compile_definitions(cxx_compiler_flags INTERFACE _CRT_SECURE_NO_WARNINGS)
endif()

# add compiler warning flags just when building this project via
# the BUILD_INTERFACE genex
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(cxx_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W4;-WX>>"
)

add_executable(DesignPatternExamples_cpp)

configure_file(version.h.in version.h)
target_include_directories(DesignPatternExamples_cpp PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# Set things up so that if the libAdapter_BackEnd.so is in the same library
# as DesignPatternExamples_cpp, then use that library instead.
set_target_properties(DesignPatternExamples_cpp
      PROPERTIES
        BUILD_RPATH_USE_ORIGIN true
        BUILD_RPATH "$ORIGIN"
)

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
        helpers/formatstring.h
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
        helpers/uint32_to_binary.h
        helpers/wcsstri.h
    PRIVATE
        helpers/checkforkey.cpp
        helpers/cursor.cpp
        helpers/DateTime.cpp
        helpers/enablevtmode.cpp
        helpers/formatstring.cpp
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
        helpers/uint32_to_binary.cpp
        helpers/wcsstri.cpp
    PRIVATE
        resource.h
        version.h.in
        resource.rc
    )

    # Group all helper/ files in the project group "Helper Files"
source_group("Helper Files" REGULAR_EXPRESSION helpers/.*)
source_group("Resource Files" FILES resource.h version.h.in resource.rc)


# Since TARGET generators are not supported in custom commands, get the needed
# file paths and directories first and pass those in simple variables.
set(IS_WINDOWS $<STREQUAL:${CMAKE_HOST_SYSTEM_NAME},Windows>)
set(ADAPTER_LIBRARY "$<TARGET_FILE:Adapter_BackEnd>")
set(ADAPTER_PDB "$<${IS_WINDOWS}:$<TARGET_PDB_FILE:Adapter_BackEnd>>")
set(CPP_OUTPUT_DIR "$<TARGET_FILE_DIR:DesignPatternExamples_cpp>/")

# Copy the Adapter_BackEnd dynamic library to the application output directory
# so the application can be run from there.
add_custom_command(TARGET DesignPatternExamples_cpp POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${ADAPTER_LIBRARY} ${CPP_OUTPUT_DIR}
                  )

# Copy the Adapter_BackEnd dynamic library debug symbol file, if it exists, to
# the application output directory so the application can use it from there.
add_custom_command(TARGET DesignPatternExamples_cpp POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                       "-DFILE_TO_COPY=${ADAPTER_PDB}"
                       "-DDESTINATION=${CPP_OUTPUT_DIR}"
                       -P ${CMAKE_SOURCE_DIR}/copyfile_if_exists.cmake
                   COMMENT "Copying ${ADAPTER_PDB} if it exists."
                  )
