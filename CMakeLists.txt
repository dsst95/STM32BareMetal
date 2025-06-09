cmake_minimum_required(VERSION 3.28)

#
# User is free to modify the file as much as necessary
#

list(APPEND CMAKE_MODULE_PATH "{{sr:cmake_path}}")
message("Build CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})
include("cmake/gcc-arm-none-eabi.cmake")
message("Build CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})

# Core project settings
project(STM32BareMetalTutorial)
enable_language(C CXX ASM)
message("Build type: " ${CMAKE_BUILD_TYPE})

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

file(GLOB_RECURSE core_sources
  ${CMAKE_CURRENT_SOURCE_DIR}/Libs/STM32/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Modules/*.cpp
)

set(core_include_dirs
  ${CMAKE_CURRENT_SOURCE_DIR}/Modules/Peripherals/Inc
  ${CMAKE_CURRENT_SOURCE_DIR}/Modules/TM1637
  ${CMAKE_CURRENT_SOURCE_DIR}/Modules/Tasks
  ${CMAKE_CURRENT_SOURCE_DIR}/Libs/CMSIS/Inc
  ${CMAKE_CURRENT_SOURCE_DIR}/Libs/STM32/Inc
)

set(core_defines
  STM32F103xB
  _LIBCPP_HAS_NO_THREADS
)

if (CMAKE_BUILD_TYPE STREQUAL "Test")
  add_subdirectory(Tests)
else()
  add_subdirectory(Core)
endif()
