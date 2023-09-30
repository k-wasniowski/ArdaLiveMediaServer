find_package(GTest REQUIRED)
include(GoogleTest)

add_subdirectory(GondorTests)
add_subdirectory(MediaTests)
add_subdirectory(MediaServerTests)
add_subdirectory(HttpServerTests)
