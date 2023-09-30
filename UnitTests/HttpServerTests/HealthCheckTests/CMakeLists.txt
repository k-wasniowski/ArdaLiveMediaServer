add_executable(HealthCheckTests
    ${CMAKE_CURRENT_SOURCE_DIR}/HealthCheckControllerTests.cpp
)

target_link_libraries(HealthCheckTests
        PRIVATE
    HttpServer::HealthCheck
)

target_link_libraries(HealthCheckTests
        PRIVATE
    GTest::gtest_main
)

gtest_discover_tests(HealthCheckTests)