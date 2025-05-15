set(test_target_name ${PROJECT_NAME}Tests)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${test_target_name} ${core_sources} ${sources})
target_include_directories(${test_target_name} PRIVATE ${core_include_dirs})
target_link_libraries(${test_target_name} GTest::gtest_main)
target_compile_definitions(${test_target_name} PRIVATE ${core_defines})

include(GoogleTest)
gtest_discover_tests(${test_target_name})
