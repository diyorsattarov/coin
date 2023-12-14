cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME cpp-cmake-template)

project(${PROJECT_NAME})
add_subdirectory(src)

add_executable(tests
    # ... other test files ...
    tests/coin/test_coin.cpp
    tests/game/test_game.cpp
)

find_package(GTest REQUIRED)

target_include_directories(tests PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(tests PRIVATE
    ${GTEST_BOTH_LIBRARIES} 
    pthread 
    coin
    game
    utilities
    # ... other libraries ...
)

add_custom_target(run_tests COMMAND tests)
