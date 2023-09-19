# Copyright 2023 The Arda Project Authors. All rights reserved.
#
# Copying, utilizing or revealing any part or entirety of this file
# and its contents without proper authorization is not allowed.

add_executable(ArdaLiveMediaServer
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_include_directories(ArdaLiveMediaServer
        PRIVATE
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(ArdaLiveMediaServer
        PUBLIC
    Gondor::Execution
    MediaServer::MediaManager
    MediaServer::RtspClient
    Http::Server
)

#target_link_libraries(ArdaLiveMediaServer
#        PUBLIC
#    opencv_ml
#    opencv_dnn
#    opencv_core
#    opencv_flann
#    opencv_videoio
#)