add_library(Resources
        STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GenericRtpController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/WebRtcController.cpp
)

target_link_libraries(Resources
        PUBLIC
    Drogon::Drogon
    LibDataChannel::LibDataChannel
    MediaServer::MediaManager
    MediaServer::MediaServer
    Media::Core
    nlohmann_json::nlohmann_json
)

target_include_directories(Resources
        PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(Http::Resources ALIAS Resources)