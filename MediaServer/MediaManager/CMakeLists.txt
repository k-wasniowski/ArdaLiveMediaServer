# Copyright 2023 The Arda Project Authors. All rights reserved.
#
# Copying, utilizing or revealing any part or entirety of this file
# and its contents without proper authorization is not allowed.

add_library(MediaManager
        STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MediaManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MediaResource.cpp
)

target_include_directories(MediaManager
        PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(MediaServer::MediaManager ALIAS MediaManager)