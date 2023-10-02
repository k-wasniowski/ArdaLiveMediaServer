add_library(MediaManager
        STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MediaManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MediaResource.cpp
)

target_include_directories(MediaManager
        PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(MediaManager
        PUBLIC
    Gondor::Concurrency
)

add_library(MediaServer::MediaManager ALIAS MediaManager)