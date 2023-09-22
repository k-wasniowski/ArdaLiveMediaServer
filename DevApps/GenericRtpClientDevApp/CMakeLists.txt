# Copyright 2023 The Arda Project Authors. All rights reserved.
#
# Copying, utilizing or revealing any part or entirety of this file
# and its contents without proper authorization is not allowed.

add_executable(GenericRtpClientDevApp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_include_directories(GenericRtpClientDevApp
        PRIVATE
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(GenericRtpClientDevApp
        PUBLIC
    MediaServer::GenericRtpClient
)
