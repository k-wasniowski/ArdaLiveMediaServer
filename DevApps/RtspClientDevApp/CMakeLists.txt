# Copyright 2023 The Arda Project Authors. All rights reserved.
#
# Copying, utilizing or revealing any part or entirety of this file
# and its contents without proper authorization is not allowed.

add_executable(RtspClientDevApp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_include_directories(RtspClientDevApp
        PRIVATE
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(RtspClientDevApp
        PUBLIC
    MediaServer::RtspClient
)
