add_executable(SessionDescriptionTests
    ${CMAKE_CURRENT_SOURCE_DIR}/SessionDescriptionTests.cpp
)

target_link_libraries(SessionDescriptionTests
        PRIVATE
    Media::Sdp
)

target_link_libraries(SessionDescriptionTests
        PRIVATE
    GTest::gtest_main
)

gtest_discover_tests(SessionDescriptionTests)