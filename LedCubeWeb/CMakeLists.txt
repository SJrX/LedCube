cmake_minimum_required(VERSION 3.27)
project(LedCubeWeb)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(LedCubeWeb
        src/arduino_secrets.h
        src/characters.h
)
