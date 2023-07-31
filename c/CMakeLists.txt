add_library(c_compiler_flags INTERFACE)
target_compile_features(c_compiler_flags INTERFACE c_std_17)

if(MSVC)
target_compile_definitions(c_compiler_flags INTERFACE _CRT_SECURE_NO_WARNINGS)
endif()

# add compiler warning flags just when building this project via
# the BUILD_INTERFACE genex
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:C,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:C,MSVC>")
target_compile_options(c_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W4;-w34255;-WX>>"
)

add_executable(DesignPatternExamples_c)

target_link_libraries(DesignPatternExamples_c
                      PUBLIC Adapter_BackEnd
                      PUBLIC c_compiler_flags
                      )

target_sources(DesignPatternExamples_c
    PRIVATE
        Adapter_Exercise.h
        Adapter_Functions.h
        Bridge_ConsoleLogger.h
        Bridge_Exercise.h
        Bridge_FileLogger.h
        Bridge_ILogger.h
        Bridge_LogHelper.h
        Bridge_NullLogger.h
        Command_Command.h
        Command_Exercise.h
        Command_TextObject.h
        Composite_Exercise.h
        Composite_FileAccess.h
        Composite_FileDirEntry.h
        Decorator_Exercise.h
        Facade_ComplexSystem.h
        Facade_Exercise.h
        Facade_Interface.h
        Flyweight_BigResource.h
        Flyweight_BigResourceManager.h
        Flyweight_Context.h
        Flyweight_Display.h
        Flyweight_Exercise.h
        Flyweight_Image.h
        HandlerChain_Exercise.h
        HandlerChain_HandlerFunctions.h
        HandlerChain_Message.h
        HandlerChain_MessageWindow.h
        HandlerChain_WindowRectangle.h
        Interpreter_Exercise.h
        Interpreter_Interpreter.h
        Iterator_Exercise.h
        Iterator_Iterators.h
        Mediator_Exercise.h
        Mediator_Functions.h
        Mediator_Group.h
        Mediator_GroupList.h
        Mediator_Groups.h
        Mediator_User.h
        Mediator_UserList.h
        Mediator_Users.h
        Memento_Exercise.h
        Memento_Memento.h
        Memento_TextObject.h
        NullObject_Exercise.h
        NullObject_MoveCommand.h
        NullObject_MoveCommandList.h
        Observer_Exercise.h
        Observer_NumberChangedFunctionList.h
        Observer_NumberProducer.h
        Proxy_Exercise.h
        Proxy_IWorkByProxy.h
        Proxy_ProxyService.h
        Proxy_RealService.h
        State_Exercise.h
        State_RemoveComments.h
        Strategy_Exercise.h
        Strategy_SortStrategy.h
        Visitor_Exercise.h
        Visitor_OrderVisitor.h
        Visitor_Shop.h
        Visitor_Village.h
    PRIVATE
        Adapter_Exercise.c
        Adapter_Functions.c
        Bridge_ConsoleLogger.c
        Bridge_Exercise.c
        Bridge_FileLogger.c
        Bridge_ILogger.c
        Bridge_LogHelper.c
        Bridge_NullLogger.c
        Command_Command.c
        Command_Exercise.c
        Command_TextObject.c
        Composite_Exercise.c
        Composite_FileAccess.c
        Composite_FileDirEntry.c
        Decorator_Exercise.c
        Facade_ComplexSystem.c
        Facade_Exercise.c
        Facade_Interface.c
        Flyweight_BigResource.c
        Flyweight_BigResourceManager.c
        Flyweight_Display.c
        Flyweight_Exercise.c
        Flyweight_Image.c
        HandlerChain_Exercise.c
        HandlerChain_HandlerFunctions.c
        HandlerChain_Message.c
        HandlerChain_MessageWindow.c
        HandlerChain_WindowRectangle.c
        Interpreter_Exercise.c
        Interpreter_Interpreter.c
        Iterator_Exercise.c
        Iterator_Iterators.c
        Mediator_Exercise.c
        Mediator_Functions.c
        Mediator_Group.c
        Mediator_GroupList.c
        Mediator_Groups.c
        Mediator_User.c
        Mediator_UserList.c
        Mediator_Users.c
        Memento_Exercise.c
        Memento_Memento.c
        Memento_TextObject.c
        NullObject_Exercise.c
        NullObject_MoveCommand.c
        NullObject_MoveCommandList.c
        Observer_Exercise.c
        Observer_NumberChangedFunctionList.c
        Observer_NumberProducer.c
        program.c
        Proxy_Exercise.c
        Proxy_ProxyService.c
        Proxy_RealService.c
        State_Exercise.c
        State_RemoveComments.c
        Strategy_Exercise.c
        Strategy_SortStrategy.c
        Visitor_Exercise.c
        Visitor_OrderVisitor.c
        Visitor_Shop.c
        Visitor_Village.c
    PRIVATE
        helpers/checkforkey.h
        helpers/conststringlist.h
        helpers/cursor.h
        helpers/datetime.h
        helpers/dynamicstring.h
        helpers/enablevtmode.h
        helpers/formatstring.h
        helpers/makelocaltime.h
        helpers/mapofint.h
        helpers/mapofstrings.h
        helpers/mutex.h
        helpers/readkey.h
        helpers/replace.h
        helpers/sleep.h
        helpers/split.h
        helpers/stack.h
        helpers/stringlist.h
        helpers/strstri.h
        helpers/titlecase.h
        helpers/uint32_to_binary.h
        helpers/uintarray.h
    PRIVATE
        helpers/checkforkey.c
        helpers/conststringlist.c
        helpers/cursor.c
        helpers/datetime.c
        helpers/dynamicstring.c
        helpers/enablevtmode.c
        helpers/formatstring.c
        helpers/makelocaltime.c
        helpers/mapofint.c
        helpers/mapofstrings.c
        helpers/mutex.c
        helpers/readkey.c
        helpers/replace.c
        helpers/sleep.c
        helpers/split.c
        helpers/stack.c
        helpers/stringlist.c
        helpers/strstri.c
        helpers/titlecase.c
        helpers/uint32_to_binary.c
        helpers/uintarray.c
        )

# Group all helper/ files in the project group "Helper Files"
source_group("Helper Files" REGULAR_EXPRESSION helpers/.*)

add_custom_command(TARGET DesignPatternExamples_c POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy -t
    $<TARGET_FILE_DIR:DesignPatternExamples_c>
    $<TARGET_RUNTIME_DLLS:DesignPatternExamples_c>
  COMMAND_EXPAND_LISTS
)
