add_library(Resources
        STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PeerConnection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/WebRtcController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/WhipSignalingHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/WhepSignalingHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/VideoEndpointRx.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/VideoEndpointTx.cpp
)

target_link_libraries(Resources
        PUBLIC
    Drogon::Drogon
    LibDataChannel::LibDataChannel
    MediaServer::MediaManager
    Media::Core
)

target_include_directories(Resources
        PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(Http::Resources ALIAS Resources)