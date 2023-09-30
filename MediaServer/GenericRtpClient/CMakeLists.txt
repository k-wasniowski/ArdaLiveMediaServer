# Copyright 2023 The Arda Project Authors. All rights reserved.
#
# Copying, utilizing or revealing any part or entirety of this file
# and its contents without proper authorization is not allowed.

add_library(GenericRtpClient
        STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GenericRtpClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Details/RtpClientSession.cpp
)

target_include_directories(GenericRtpClient
        PUBLIC
    ${Boost_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(GenericRtpClient
        PRIVATE
    Media::Core
    Media::Sdp
)

target_link_libraries(GenericRtpClient
        PRIVATE
    MediaServer::MediaManager
)

add_library(MediaServer::GenericRtpClient ALIAS GenericRtpClient)