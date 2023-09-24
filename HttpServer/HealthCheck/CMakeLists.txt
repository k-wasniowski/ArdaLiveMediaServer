add_library(HealthCheck
        STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/HealthCheckController.cpp
)

target_link_libraries(HealthCheck
        PUBLIC
    Drogon::Drogon
)

target_include_directories(HealthCheck
        PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(Http::HealthCheck ALIAS HealthCheck)