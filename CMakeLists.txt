# Copyright 2023 The Arda Project Authors. All rights reserved.
#
# Copying, utilizing or revealing any part or entirety of this file
# and its contents without proper authorization is not allowed.

cmake_minimum_required(VERSION 3.26)

include(FetchContent)

message("-- Setting up VCPKG package manager tool")
FetchContent_Declare(
    vcpkg
    GIT_REPOSITORY https://github.com/microsoft/vcpkg.git
    GIT_TAG        4a600e9fea71bd7872080cbb716797e04d30e6d3
)
FetchContent_MakeAvailable(vcpkg)

set(CMAKE_TOOLCHAIN_FILE ${vcpkg_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake)

project(ArdaLiveMediaServer LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)
include(AddGitSubmodule)
include(Docs)

find_package(Drogon CONFIG REQUIRED)
find_package(LibDataChannel CONFIG REQUIRED)
find_package(opentelemetry-cpp CONFIG REQUIRED)
find_package(Boost REQUIRED)

add_subdirectory(Gondor)
add_subdirectory(Media)
add_subdirectory(MediaServer)
add_subdirectory(HttpServer)
add_subdirectory(App)

add_subdirectory(UnitTests)
add_subdirectory(DevApps)