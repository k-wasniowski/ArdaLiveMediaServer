add_library(Server
        STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Server.cpp
)

target_include_directories(Server
        PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Server
        PUBLIC
    MediaServer::MediaManager
    Http::HealthCheck
    Http::Resources
)

add_library(Http::Server ALIAS Server)