enable_testing()

find_package(GTest REQUIRED)
include(GoogleTest)

add_subdirectory(HttpServerTests)
add_subdirectory(MediaTests)
