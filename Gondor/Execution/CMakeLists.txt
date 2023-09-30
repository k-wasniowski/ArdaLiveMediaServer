add_library(Execution
        STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ExecutionContext.cpp
)

target_include_directories(Execution
        PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIR}
)

add_library(Gondor::Execution ALIAS Execution)