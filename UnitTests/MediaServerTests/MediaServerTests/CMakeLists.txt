add_executable(MediaServerTests
    ${CMAKE_CURRENT_SOURCE_DIR}/ServerTests.cpp
)

target_link_libraries(MediaServerTests
        PRIVATE
    Gondor::Execution
    MediaServer::MediaServer
)

target_link_libraries(MediaServerTests
        PRIVATE
    GTest::gtest_main
)

gtest_discover_tests(MediaServerTests)