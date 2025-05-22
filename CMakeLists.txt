cmake_minimum_required(VERSION 3.15)
    project(HttpServerProject)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    # Find vcpkg-installed libraries
    find_package(httplib CONFIG REQUIRED)
    find_package(nlohmann_json CONFIG REQUIRED)
    find_package(CURL CONFIG REQUIRED )

    # Include common directory for headers
    include_directories(${CMAKE_SOURCE_DIR}/common)

    # Build HTTP server
    add_executable(http_server src/server/http_server.cpp)
    target_link_libraries(http_server PRIVATE httplib::httplib nlohmann_json::nlohmann_json)

    # Build HTTP client as a static library
    add_library(http_client STATIC common/http_client/http_client.cpp)
    target_link_libraries(http_client PRIVATE CURL::libcurl)

    #Build test client
    add_executable(test_client src/test_client.cpp)
    target_link_libraries(test_client PRIVATE http_client)