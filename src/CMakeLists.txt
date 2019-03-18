cmake_minimum_required(VERSION 3.13)
project(src)

set(CMAKE_CXX_STANDARD 11)

add_executable(src main.cpp AssetsAddressLookup.cpp AssetsAddressLookup.h Game.cpp Game.h Mario.cpp Mario.h)