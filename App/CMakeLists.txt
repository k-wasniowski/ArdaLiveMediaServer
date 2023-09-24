add_executable(ArdaLiveMediaServer
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_include_directories(ArdaLiveMediaServer
        PRIVATE
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(ArdaLiveMediaServer
        PUBLIC
    MediaServer::MediaManager
    MediaServer::RtspClient
    Http::Server
)