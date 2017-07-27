# CMake entry point
cmake_minimum_required (VERSION 3.0.2)

project (polar_decoder_gen)

# Set the path to the CMake modules
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set (CMAKE_MACOSX_RPATH 1)

# Enable C++11
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    set (CMAKE_CXX_STANDARD 14)
else ()
    set (CMAKE_CXX_STANDARD 11)
endif()

# Specify bin path
set (EXECUTABLE_OUTPUT_PATH bin/)

# Generate the source files list
file (GLOB_RECURSE source_files src/*)

# Object
add_library (polar_decoder_gen-obj OBJECT ${source_files})

# Binary
add_executable        (polar_decoder_gen-bin $<TARGET_OBJECTS:polar_decoder_gen-obj>)
set_target_properties (polar_decoder_gen-bin PROPERTIES OUTPUT_NAME polar_decoder_gen)

# Add AFF3CT as a library
add_definitions (-DMULTI_PREC)
set(ENABLE_STATIC_LIB ON  CACHE BOOL "Enable to compile AFF3CT static library" FORCE)
set(ENABLE_EXEC       OFF CACHE BOOL "Enable to compile AFF3CT executable"     FORCE)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/aff3ct/CMakeLists.txt")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/aff3ct/")
    target_link_libraries (polar_decoder_gen-bin aff3ct-static-lib)
    include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/lib/aff3ct/src/")
    message(STATUS "AFF3CT found")
else ()
    message(FATAL_ERROR "AFF3CT can't be found, try to init the submodules with the following cmd:\n"
                        "$ git submodule update --init --recursive")
endif ()

# Add MIPP wrapper includes
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/aff3ct/lib/MIPP/src/mipp.h")
    include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/lib/aff3ct/lib/MIPP/src/")
else ()
    message(FATAL_ERROR "MIPP can't be found, try to init the submodules with the following cmd:\n"
                        "$ git submodule update --init --recursive")
endif ()

# Enable pthread
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    add_definitions (-Wno-overloaded-virtual)
    target_link_libraries (polar_decoder_gen-bin -lpthread)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_definitions (-pthread)
    target_link_libraries (polar_decoder_gen-bin -lpthread)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    add_definitions (-pthread)
    target_link_libraries (polar_decoder_gen-bin -pthread)
endif()
