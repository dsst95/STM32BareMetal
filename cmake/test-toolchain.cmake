set(CMAKE_SYSTEM_NAME               Linux)

set(FLAGS                           "-fdata-sections -ffunction-sections")
set(CPP_FLAGS                       "${FLAGS} -fno-rtti -fno-exceptions -fno-threadsafe-statics")

set(CMAKE_C_FLAGS                   ${FLAGS})
set(CMAKE_CXX_FLAGS                 ${CPP_FLAGS})

set(CMAKE_C_COMPILER                clang-20)
set(CMAKE_ASM_COMPILER              clang-20)
set(CMAKE_CXX_COMPILER              clang++-20)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_CLANG_TIDY clang-tidy --allow-no-checks)
set(CMAKE_CXX_CLANG_TIDY clang-tidy --allow-no-checks)
