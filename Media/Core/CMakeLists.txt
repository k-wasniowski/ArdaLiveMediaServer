add_library(Core
        STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Frame.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MediaBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/VideoFrame.cpp
)

target_include_directories(Core
        PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(Media::Core ALIAS Core)