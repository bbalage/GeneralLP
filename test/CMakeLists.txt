include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES true *.hpp *.h *.cpp)

set(TEST_EXECUTABLE_NAME ${CMAKE_PROJECT_NAME}_test)

add_executable(
  ${TEST_EXECUTABLE_NAME}
  ${TEST_SOURCES}
)

target_link_libraries(
  ${TEST_EXECUTABLE_NAME}
  PRIVATE ${CMAKE_PROJECT_NAME}_lib
  GTest::gtest_main
)

include(GoogleTest)

gtest_add_tests(
  ${TEST_EXECUTABLE_NAME}
  SOURCES ${TEST_SOURCES}
)