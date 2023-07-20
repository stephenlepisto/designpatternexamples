# Adapter_BackEnd cmake

add_library(adapter_compiler_flags INTERFACE)
target_compile_features(adapter_compiler_flags INTERFACE c_std_17)

add_library(Adapter_BackEnd SHARED)
target_sources(Adapter_BackEnd
    PUBLIC
        Adapter_BackEnd.h
    PRIVATE
        Adapter_BackEnd.c
        dllmain.c
        pch.c
        Adapter_BackEnd.rc
        framework.h
        pch.h
        resource.h)

source_group("Resource Files" FILES Adapter_BackEnd.rc)

target_link_libraries(Adapter_BackEnd PRIVATE adapter_compiler_flags)
target_include_directories(Adapter_BackEnd INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
set_target_properties(Adapter_BackEnd
                      PROPERTIES
                      DEFINE_SYMBOL "ADAPTERBACKEND_EXPORTS"  # Source code uses all uppercase symbol for this
                      )
