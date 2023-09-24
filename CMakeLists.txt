# Copyright 2023 The Arda Project Authors. All rights reserved.
#
# Copying, utilizing or revealing any part or entirety of this file
# and its contents without proper authorization is not allowed.

cmake_minimum_required(VERSION 3.26)

project(ArdaLiveMediaServer LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)

find_package(Drogon CONFIG REQUIRED)
find_package(LibDataChannel CONFIG REQUIRED)
find_package(opentelemetry-cpp CONFIG REQUIRED)
find_package(Boost REQUIRED)

add_subdirectory(Media)
add_subdirectory(MediaServer)
add_subdirectory(HttpServer)
add_subdirectory(App)

add_subdirectory(UnitTests)
add_subdirectory(DevApps)