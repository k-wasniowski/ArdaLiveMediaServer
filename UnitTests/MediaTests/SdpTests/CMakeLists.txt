# Copyright 2023 The Arda Project Authors. All rights reserved.
#
# Copying, utilizing or revealing any part or entirety of this file
# and its contents without proper authorization is not allowed.

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