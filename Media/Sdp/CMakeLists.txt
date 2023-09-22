# Copyright 2023 The Arda Project Authors. All rights reserved.
#
# Copying, utilizing or revealing any part or entirety of this file
# and its contents without proper authorization is not allowed.

add_library(Sdp
        STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SessionDescription.cpp
)

target_include_directories(Sdp
        PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Sdp
        PUBLIC
    LibDataChannel::LibDataChannel
)

add_library(Media::Sdp ALIAS Sdp)