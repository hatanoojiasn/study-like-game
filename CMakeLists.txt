cmake_minimum_required(VERSION 3.16)
project(study_like_game C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(BUILD_HOST_APP "Build raylib host GUI app" ON)
option(BUILD_TESTS "Build tests" ON)

add_library(engine_core
    src/engine/engine.c
    src/game/game.c
)

target_include_directories(engine_core
    PUBLIC
        src
)

target_compile_options(engine_core PRIVATE -Wall -Wextra -Wpedantic)

if(BUILD_HOST_APP)
    find_package(raylib QUIET)
    if(raylib_FOUND)
        add_executable(study_like_game
            src/main.c
            src/platform/host_raylib/platform_host.c
        )
        target_include_directories(study_like_game PRIVATE src)
        target_link_libraries(study_like_game PRIVATE engine_core raylib)
        target_compile_options(study_like_game PRIVATE -Wall -Wextra -Wpedantic)
    else()
        message(WARNING "raylib not found: skipping host GUI app target (set BUILD_HOST_APP=OFF to silence)")
    endif()
endif()

if(BUILD_TESTS)
    enable_testing()
    add_executable(test_game_determinism
        tests/test_game_determinism.c
        src/engine/engine.c
        src/game/game.c
    )
    target_include_directories(test_game_determinism PRIVATE src)
    target_compile_options(test_game_determinism PRIVATE -Wall -Wextra -Wpedantic)
    add_test(NAME test_game_determinism COMMAND test_game_determinism)
endif()
