# Adapter_BackEnd cmake

add_library(adapter_compiler_flags INTERFACE)
target_compile_features(adapter_compiler_flags INTERFACE c_std_17)
if(MSVC)
target_compile_definitions(adapter_compiler_flags INTERFACE _CRT_SECURE_NO_WARNINGS)
endif()

add_library(Adapter_BackEnd SHARED)

configure_file(version.h.in version.h)
target_include_directories(Adapter_BackEnd PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

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
        resource.h
        version.h.in)

source_group("Resource Files" FILES Adapter_BackEnd.rc)

target_link_libraries(Adapter_BackEnd PRIVATE adapter_compiler_flags)
target_include_directories(Adapter_BackEnd INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
set_target_properties(Adapter_BackEnd
                      PROPERTIES
                      DEFINE_SYMBOL "ADAPTERBACKEND_EXPORTS"  # Source code uses all uppercase symbol for this
                      )
