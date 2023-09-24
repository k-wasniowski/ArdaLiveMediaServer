add_executable(CoreTests
    ${CMAKE_CURRENT_SOURCE_DIR}/MediaBufferTests.cpp
)

target_link_libraries(CoreTests
        PRIVATE
    Media::Core
)

target_link_libraries(CoreTests
        PRIVATE
    GTest::gtest_main
)

gtest_discover_tests(CoreTests)