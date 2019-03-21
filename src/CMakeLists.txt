cmake_minimum_required(VERSION 3.13)
project(src)

set(CMAKE_CXX_STANDARD 11)

add_executable(src main.cpp AssetsAddresses.h Game.cpp Game.h Mario.cpp Mario.h Block.cpp Block.h rsdl.cpp rsdl.hpp Physics.cpp Physics.h Object.h Geometry.cpp Geometry.h Object.cpp utility.cpp utility.h)