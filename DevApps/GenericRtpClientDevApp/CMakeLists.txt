add_executable(GenericRtpClientDevApp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_include_directories(GenericRtpClientDevApp
        PRIVATE
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(GenericRtpClientDevApp
        PUBLIC
    MediaServer::GenericRtpClient
)
