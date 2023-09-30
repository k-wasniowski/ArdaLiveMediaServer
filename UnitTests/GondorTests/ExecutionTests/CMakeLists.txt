add_executable(ExecutionTests
    ${CMAKE_CURRENT_SOURCE_DIR}/ExecutionContextTests.cpp
)

target_link_libraries(ExecutionTests
        PRIVATE
    Gondor::Execution
)

target_link_libraries(ExecutionTests
        PRIVATE
    GTest::gtest_main
)

gtest_discover_tests(ExecutionTests)