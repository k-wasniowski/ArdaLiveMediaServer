# Copyright 2023 The Arda Project Authors. All rights reserved.
#
# Copying, utilizing or revealing any part or entirety of this file
# and its contents without proper authorization is not allowed.

add_library(Core
        STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Frame.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/VideoFrame.cpp
)

target_include_directories(Core
        PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(Media::Core ALIAS Core)