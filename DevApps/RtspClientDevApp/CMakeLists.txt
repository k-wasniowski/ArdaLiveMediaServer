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
