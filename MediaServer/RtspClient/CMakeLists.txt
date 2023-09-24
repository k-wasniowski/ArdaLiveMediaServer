add_library(RtspClient
        STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RtspClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Details/RtspClientSession.cpp
)

target_include_directories(RtspClient
        PUBLIC
    ${Boost_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(RtspClient
        PRIVATE
    opentelemetry-cpp::api
    opentelemetry-cpp::ext
    opentelemetry-cpp::sdk
    opentelemetry-cpp::logs
)

add_library(MediaServer::RtspClient ALIAS RtspClient)