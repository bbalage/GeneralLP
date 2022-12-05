enable_testing()

file(GLOB_RECURSE ALL_SOURCES LIST_DIRECTORIES true *.hpp *.h *.cpp)
set(LIB_SOURCES ${ALL_SOURCES})
# file(GLOB_RECURSE LIB_SOURCES LIST_DIRECTORIES true *.hpp *.h *.cpp)
# list(REMOVE_ITEM LIB_SOURCES "main.cpp")
list(FILTER LIB_SOURCES EXCLUDE REGEX ".*main.cpp$")
set(LIB_NAME ${CMAKE_PROJECT_NAME}_lib)

add_library(${LIB_NAME} STATIC ${LIB_SOURCES} )
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

set(MAIN_EXECUTABLE_NAME ${CMAKE_PROJECT_NAME})
add_executable(${MAIN_EXECUTABLE_NAME} "main.cpp")
target_link_libraries(${MAIN_EXECUTABLE_NAME}
    ${LIB_NAME})

set(TTY_MAIN_EXECUTABLE_NAME tty_glp)
add_executable(${TTY_MAIN_EXECUTABLE_NAME} "tty_main.cpp")
target_link_libraries(${TTY_MAIN_EXECUTABLE_NAME}
    ${LIB_NAME})