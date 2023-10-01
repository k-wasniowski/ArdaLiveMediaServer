add_library(MediaServer
        STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MediaManagerProxy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GenericRtpClientProxy.cpp
)

target_include_directories(MediaServer
        PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(MediaServer
        PUBLIC
    Gondor::Execution
)

target_link_libraries(MediaServer
        PUBLIC
    MediaServer::MediaManager
    MediaServer::GenericRtpClient
)

add_library(MediaServer::MediaServer ALIAS MediaServer)