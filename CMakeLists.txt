cmake_minimum_required(VERSION 3.10)
if (NOT DEFINED PROJECT_NAME)
    set (SUBPROJECT OFF)
    message(STATUS "Submodule loading not detected; compiling Nova")
else()
    set (SUBPROJECT ON)
    message(STATUS "Submodule loading detected; disabling compilation")
endif()

project(Nova)


if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory and run CMake from there, or use the -B argument." )
endif()

if (NOT CMAKE_BUILD_TYPE)
    # Prevent explicit flags.
    set(CMAKE_BUILD_TYPE Release)
endif()

# TODO: figure out how to also support C++20 where supported
# Probably need to configure shit or something.
set (CMAKE_CXX_STANDARD 17)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
#include(conan.cmake)

conan_cmake_configure (REQUIRES nlohmann_json/3.9.1
                        GENERATORS cmake_find_package cmake)
conan_cmake_autodetect (settings)
conan_cmake_install (PATH_OR_REFERENCE . BUILD missing REMOTE conan-center SETTINGS ${settings})
if (NOT SUBPROJECT)

if (NOT WIN32)
    # Enable rdynamic outside windows.
    # All compilers should at this point be modern enough to support it,
    # so we can drop the extra check.
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -rdynamic")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Wno-c++11-narrowing")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -fsanitize=undefined")
    set (CMAKE_CXX_FLAGS_RELEASE "-O3")
else()
    # I _think_ CMAKE should be able to figure out windows flags wrt. frameworks
    set (CMAKE_CXX_FLAGS_DEBUG "/Zi")
endif()

include_directories("include/")
include_directories("TermUtils/include/")
#find_package(nlohmann_json)
add_subdirectory(src)
add_subdirectory(Catch2)
add_subdirectory(test)

add_custom_target(test
    COMMAND test/tests
    DEPENDS tests Catch2::Catch2
    COMMENT "Runs testing")

endif()
