add_executable(MediaManagerTests
    ${CMAKE_CURRENT_SOURCE_DIR}/MediaResourceTests.cpp
)

target_link_libraries(MediaManagerTests
        PRIVATE
    Gondor::Execution
    MediaServer::MediaManager
)

target_link_libraries(MediaManagerTests
        PRIVATE
    GTest::gtest_main
)

gtest_discover_tests(MediaManagerTests)