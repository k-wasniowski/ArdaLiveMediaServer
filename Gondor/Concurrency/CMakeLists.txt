add_library(Concurrency INTERFACE)

target_include_directories(Concurrency
        INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(Gondor::Concurrency ALIAS Concurrency)