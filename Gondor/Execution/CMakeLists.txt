# Copyright 2023 The Arda Project Authors. All rights reserved.
#
# Copying, utilizing or revealing any part or entirety of this file
# and its contents without proper authorization is not allowed.

add_library(Execution
        STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TasksContext.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TasksExecutor.cpp
)

target_include_directories(Execution
        PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIR}
)

add_library(Gondor::Execution ALIAS Execution)