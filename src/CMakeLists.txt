find_package(spdlog REQUIRED)
add_library(utilities
    utilities/utilities.cpp
)
target_include_directories(utilities PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(utilities PRIVATE spdlog::spdlog)

add_library(coin
    coin/coin.cpp
)
target_include_directories(coin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_library(game
    game/game.cpp
)
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)