set(target_name ${PROJECT_NAME})

# Core MCU flags, CPU type, instruction set and FPU setup
set(cpu_PARAMS
  # Other parameters
  # -mthumb
  # -mcpu, -mfloat, -mfloat-abi, ...
)

# Sources
file(GLOB_RECURSE sources
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../Startup/*.s
)

set(sources_SRCS ${core_sources} ${sources})

# Include directories for all compilers
set(include_DIRS ${core_include_dirs})

# Include directories for each compiler
set(include_c_DIRS)
set(include_cxx_DIRS)
set(include_asm_DIRS)

# Symbols definition for all compilers
set(symbols_SYMB ${core_defines})

# Symbols definition for each compiler
set(symbols_c_SYMB)
set(symbols_cxx_SYMB)
set(symbols_asm_SYMB)

# Link directories and names of libraries
set(link_DIRS)
set(link_LIBS)

# Linker script
set(linker_script_SRC ${CMAKE_CURRENT_SOURCE_DIR}/../stm32f103c8tx_FLASH.ld)

# Compiler options
set(compiler_OPTS)

# Linker options
set(linker_OPTS)

# Now call generated cmake
# This will add script generated
# information to the project
include("../cmake/vscode_generated.cmake")

# Link directories setup
# Must be before executable is added
link_directories(${target_name} ${link_DIRS})

# Create an executable object type
add_executable(${target_name} ${sources_SRCS})

# Add sources to executable
target_sources(${target_name} PUBLIC ${sources_SRCS})

# Add include paths
target_include_directories(${target_name} PRIVATE
  ${include_DIRS}
  $<$<COMPILE_LANGUAGE:C>: ${include_c_DIRS}>
  $<$<COMPILE_LANGUAGE:CXX>: ${include_cxx_DIRS}>
  $<$<COMPILE_LANGUAGE:ASM>: ${include_asm_DIRS}>
)

# Add project symbols (macros)
target_compile_definitions(${target_name} PRIVATE
  ${symbols_SYMB}
  $<$<COMPILE_LANGUAGE:C>: ${symbols_c_SYMB}>
  $<$<COMPILE_LANGUAGE:CXX>: ${symbols_cxx_SYMB}>
  $<$<COMPILE_LANGUAGE:ASM>: ${symbols_asm_SYMB}>

  # Configuration specific
  $<$<CONFIG:Debug>:DEBUG>
  $<$<CONFIG:Release>: >
)

# Add linked libraries
target_link_libraries(${target_name} PRIVATE
  ${link_LIBS}
)

# Compiler options
target_compile_options(${target_name} PRIVATE
  ${cpu_PARAMS}
  ${compiler_OPTS}
  -Wall
  -Wextra
  -Wpedantic
  -Wno-unused-parameter
  $<$<COMPILE_LANGUAGE:C>: >
  $<$<COMPILE_LANGUAGE:CXX>:

  -fno-exceptions
  -fno-rtti
  -fno-unwind-tables
  -fno-threadsafe-statics
  -fstack-usage
  -fno-math-errno
  -ffunction-sections
  -fdata-sections
  -fno-use-cxa-atexit
  -save-temps

  # -Wno-volatile
  # -Wold-style-cast
  # -Wuseless-cast
  # -Wsuggest-override
  >
  $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp -MMD -MP>
  $<$<CONFIG:Debug>:-Og -g3 -ggdb>
  $<$<NOT:$<CONFIG:Debug>>:-O1>
)

# Linker options
target_link_options(${target_name} PRIVATE
  -T${linker_script_SRC}
  ${cpu_PARAMS}
  ${linker_OPTS}
  -Wl,-Map=${target_name}.map
  -Wl,--gc-sections # Remove unused sections
  -u _printf_float # STDIO float formatting support (remove if not used)
  --specs=nosys.specs
  -Wl,--start-group
  -lc
  -lm
  -lstdc++
  -lsupc++
  -Wl,--end-group
  -Wl,-z,max-page-size=8 # Allow good software remapping across address space (with proper GCC section making)
  -Wl,--print-memory-usage
  -Wl,--wrap=atexit
  -Wl,--wrap=at_quick_exit
  -Wl,--wrap=__cxa_atexit
)

# Execute post-build to print size, generate hex and bin
add_custom_command(TARGET ${target_name} POST_BUILD
  COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${target_name}>
  COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${target_name}> ${target_name}.hex
  COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${target_name}> ${target_name}.bin
)
