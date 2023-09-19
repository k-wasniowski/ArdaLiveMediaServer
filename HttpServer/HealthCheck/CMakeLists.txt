# Copyright 2023 The Arda Project Authors. All rights reserved.
#
# Copying, utilizing or revealing any part or entirety of this file
# and its contents without proper authorization is not allowed.

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