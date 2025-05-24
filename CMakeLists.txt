cmake_minimum_required(VERSION 3.15)
    project(HttpServerProject)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    # Find vcpkg-installed libraries
    find_package(httplib CONFIG REQUIRED)
    find_package(nlohmann_json CONFIG REQUIRED)
    find_package(CURL CONFIG REQUIRED )
    find_package(Boost REQUIRED COMPONENTS asio)
    find_package(GTest CONFIG REQUIRED)

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

    # Build TCP echo server
    add_executable(tcp_echo_server common/network/tcp_echo_server.cpp)
    target_link_libraries(tcp_echo_server PRIVATE Boost::asio)

    add_executable(test_tcp_client src/test_tcp_client.cpp)
    target_link_libraries(test_tcp_client PRIVATE Boost::asio)

    add_executable(http_socket_server common/network/http_socket_server.cpp)
    target_link_libraries(http_socket_server PRIVATE Boost::asio)

    add_executable(test_http_client tests/test_http_client.cpp)
    target_link_libraries(test_http_client PRIVATE http_client GTest::gtest GTest::gtest_main)

    # add_executable(test_servers tests/test_servers.cpp common/network/tcp_echo_server.cpp common/network/http_socket_server.cpp)
    # target_link_libraries(test_servers PRIVATE http_client httplib::httplib Boost::asio GTest::gtest GTest::gtest_main)

    enable_testing()
    add_test(NAME HttpClientTest COMMAND test_http_client)
    #add_test(NAME ServerTests COMMAND test_servers)
