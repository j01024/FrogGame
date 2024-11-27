cmake_minimum_required(VERSION 3.10)

project (FrogGame C)
set(CMAKE_C_STANDARD 99)

add_executable(FrogGame 
                main.c
                src/background.c
                src/loop.c
                src/setup.c
                src/game.c
                src/frog.c
                src/utility.c
                src/colors.c
                src/car.c
                src/interfaces/drawing.c
                src/interfaces/events.c
                src/interfaces/position.c)
target_link_libraries(FrogGame ncurses)

target_include_directories(FrogGame PRIVATE
                           ${CMAKE_SOURCE_DIR}/src
                           ${CMAKE_SOURCE_DIR}/include
                           ${CMAKE_SOURCE_DIR}/include/interfaces
                           )