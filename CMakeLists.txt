cmake_minimum_required(VERSION 3.15)
    project(HttpServerProject)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    # Find vcpkg-installed libraries
    find_package(httplib CONFIG REQUIRED)
    find_package(nlohmann_json CONFIG REQUIRED)

    # Build HTTP server
    add_executable(http_server src/server/http_server.cpp)
    target_link_libraries(http_server PRIVATE httplib::httplib nlohmann_json::nlohmann_json)