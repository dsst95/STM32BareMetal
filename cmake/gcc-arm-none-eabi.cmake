set(CMAKE_CROSSCOMPILING            TRUE)
set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          arm)

# Some default GCC settings
# arm-none-eabi- must be part of path environment
set(TOOLCHAIN_PREFIX                arm-none-eabi-)
set(FLAGS                           "-fdata-sections -ffunction-sections -Wl,--gc-sections")
set(CPP_FLAGS                       "${FLAGS} -fno-rtti -fno-exceptions -fno-threadsafe-statics")

set(CMAKE_C_FLAGS                   ${FLAGS})
set(CMAKE_CXX_FLAGS                 ${CPP_FLAGS})

set(CMAKE_C_COMPILER                ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER              ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER              ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_OBJCOPY                   ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE                      ${TOOLCHAIN_PREFIX}size)

set(CMAKE_EXECUTABLE_SUFFIX_ASM     ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C       ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX     ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Configure clang-tidy with includes from GNU ARM toolchain
# Get list of include paths (https://stackoverflow.com/a/59068162/5840652)
execute_process(
  COMMAND ${CMAKE_CXX_COMPILER} -Wp,-v -x c++ - -fsyntax-only
  TIMEOUT 1
  ERROR_VARIABLE ARM_NONE_EABI_INC_DIRS
  OUTPUT_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

# Add include paths
separate_arguments(ARM_NONE_EABI_INC_DIRS_LIST NATIVE_COMMAND
                   ${ARM_NONE_EABI_INC_DIRS})
foreach(DIR ${ARM_NONE_EABI_INC_DIRS_LIST})
  string(REGEX MATCH "([0-9]+)\\.([0-9]+)\\.([0-9]+)" CONTAINS_VERSION ${DIR})
  if(NOT ${CONTAINS_VERSION} STREQUAL "")
    list(APPEND CXX_CLANG_EXTRA_INCLUDES -extra-arg=-isystem${DIR})
  endif()
endforeach()

execute_process(
  COMMAND ${CMAKE_C_COMPILER} -Wp,-v - -fsyntax-only
  TIMEOUT 1
  ERROR_VARIABLE ARM_NONE_EABI_INC_DIRS
  OUTPUT_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

# Add include paths
separate_arguments(ARM_NONE_EABI_INC_DIRS_LIST NATIVE_COMMAND
                   ${ARM_NONE_EABI_INC_DIRS})
foreach(DIR ${ARM_NONE_EABI_INC_DIRS_LIST})
  string(REGEX MATCH "([0-9]+)\\.([0-9]+)\\.([0-9]+)" CONTAINS_VERSION ${DIR})
  if(NOT ${CONTAINS_VERSION} STREQUAL "")
    list(APPEND CLANG_EXTRA_INCLUDES -extra-arg=-isystem${DIR})
  endif()
endforeach()

set(CMAKE_C_CLANG_TIDY clang-tidy --allow-no-checks -extra-arg=--target=arm-none-eabi ${CLANG_EXTRA_INCLUDES})
set(CMAKE_CXX_CLANG_TIDY clang-tidy --allow-no-checks -extra-arg=--target=arm-none-eabi ${CXX_CLANG_EXTRA_INCLUDES})
