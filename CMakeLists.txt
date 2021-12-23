cmake_minimum_required(VERSION 3.21)
project(AsteroidsMSVC)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

include_directories(AsteroidsMSVC)

add_executable(AsteroidsMSVC
        AsteroidsMSVC/Asteroid.cpp
        AsteroidsMSVC/Asteroid.h
        AsteroidsMSVC/Bullet.cpp
        AsteroidsMSVC/Bullet.h
        AsteroidsMSVC/Functions.cpp
        AsteroidsMSVC/Functions.h
        AsteroidsMSVC/Game.cpp
        AsteroidsMSVC/Game.h
        AsteroidsMSVC/main.cpp
        AsteroidsMSVC/Object.cpp
        AsteroidsMSVC/Object.h
        AsteroidsMSVC/Player.cpp
        AsteroidsMSVC/Player.h)

target_link_libraries(AsteroidsMSVC sfml-graphics sfml-audio)
