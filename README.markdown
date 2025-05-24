# C++ HTTP Server Project

## Overview
This project is a C++-based HTTP server and client application, inspired by the JSONPlaceholder API. It demonstrates backend development skills, including RESTful APIs, HTTP communication, TCP socket programming, and modular code design. Built with modern C++ (C++17), it uses libraries like `cpp-httplib`, `nlohmann/json`, `libcurl`, and `boost::asio` to implement a scalable server, a reusable HTTP client, and low-level socket servers. The project emphasizes networking, modularity, STL usage, and testing, suitable for learning backend concepts.

## Features
- **RESTful HTTP Server**: Serves endpoints like `/api/health`, `/api/users`, and `/api/users/{id}`, fetching data from JSONPlaceholder.
- **HTTP Client**: Performs GET requests to external APIs (e.g., JSONPlaceholder) using `libcurl`.
- **TCP Echo Server**: Echoes client messages over TCP using `boost::asio`.
- **HTTP Socket Server**: Accepts HTTP requests from browsers (e.g., Chrome) and returns a simple HTML page, built with `boost::asio`.
- **Modular Design**: Reusable components in `common/` (e.g., `http_client`, `network`).
- **Attempted Testing**: Integration tests for servers and client using Google Test (partially implemented due to technical issues).

## Project Structure
```
http-server-project/
├── common/
│   ├── http_client/
│   │   └── http_client.cpp  # HTTP client implementation
│   │   └── http_client.hpp
│   └── network/
│       └── tcp_echo_server.cpp  # TCP echo server
│       └── tcp_echo_server.hpp
│       └── http_socket_server.cpp  # HTTP socket server
│       └── http_socket_server.hpp
├── src/
│   ├── server/
│   │   └── http_server.cpp  # HTTP server implementation
│   ├── test_client.cpp  # Test client for HTTP client
│   └── test_tcp_client.cpp  # Test client for TCP echo server
├── tests/
│   ├── test_http_client.cpp  # Unit tests for HTTP client
│   └── test_servers.cpp  # Integration tests (incomplete)
├── CMakeLists.txt  # CMake build configuration
├── README.md  # Project documentation
└── vcpkg.json  # Dependency manifest
```

## Dependencies
- **C++17**: Required for modern C++ features.
- **vcpkg**: Package manager for dependencies.
- **Libraries**:
  - `cpp-httplib`: HTTP server and client library.
  - `nlohmann/json`: JSON parsing for API responses.
  - `libcurl`: HTTP client requests.
  - `boost-asio`: Asynchronous I/O for socket programming.
  - `gtest`: Google Test for unit and integration testing (partially used).
- **CMake**: Build system.

Install dependencies via vcpkg:
```bash
./vcpkg/vcpkg install cpp-httplib nlohmann-json libcurl boost-asio gtest
```

## Tasks and Implementation

### Task 1: Project Setup
- Initialized a C++ project with CMake and vcpkg.
- Configured dependencies and directory structure (`common/`, `src/`, `tests/`).
- Set up Git for version control.

### Task 2: HTTP Server (Basic)
- Implemented `http_server` in `src/server/http_server.cpp` using `cpp-httplib`.
- Features:
  - `/api/health`: Returns "OK" for health checks.
  - Runs on `http://localhost:8080`.
- Learned RESTful API basics and HTTP server setup.

### Task 3: HTTP Server (Enhanced)
- Extended `http_server` to proxy requests to JSONPlaceholder:
  - `/api/users`: Fetches all users.
  - `/api/users/{id}`: Fetches a user by ID.
- Used `nlohmann/json` to parse and return JSON responses.
- Improved understanding of HTTP routing and external API integration.

### Task 4: HTTP Client
- Created `HttpClient` in `common/http_client/http_client.cpp` using `libcurl`.
- Supports GET requests (e.g., `https://jsonplaceholder.typicode.com/users/1`).
- Reusable component for server and test clients.
- Tested with `test_client` in `src/test_client.cpp`.

### Task 5: TCP Echo Server
- Implemented `TcpServer` in `common/network/tcp_echo_server.cpp` using `boost::asio`.
- Echoes client messages over TCP on port 12345.
- Tested with `test_tcp_client` in `src/test_tcp_client.cpp`.
- Learned asynchronous I/O and low-level socket programming.

### Task 5.5: HTTP Socket Server
- Implemented `HttpServer` in `common/network/http_socket_server.cpp` using `boost::asio`.
- Accepts HTTP requests (e.g., from Chrome) on port 8081.
- Prints request headers to console and returns a simple HTML page (`<h1>Hello, Chrome!</h1>`).
- Tested with Chrome (`http://localhost:8081`) and `test_client`.
- Deepened understanding of HTTP over TCP.

### Task 6: Testing (Incomplete)
- Attempted to add Google Test for unit and integration tests in `tests/`.
- Successfully implemented unit tests for `HttpClient` in `test_http_client.cpp`.
- Faced issues with integration tests for servers in `test_servers.cpp` (linking errors, hanging, `bad_executor`).
- Decided to leave testing incomplete due to persistent technical challenges.

## Build Instructions
1. **Clone the Repository**:
   ```bash
   git clone <your-repo-url>
   cd http-server-project
   ```
2. **Install vcpkg** (if not already installed):
   ```bash
   git clone https://github.com/microsoft/vcpkg.git
   ./vcpkg/bootstrap-vcpkg.sh
   ```
3. **Install Dependencies**:
   ```bash
   ./vcpkg/vcpkg install
   ```
4. **Build the Project**:
   ```bash
   mkdir build
   cd build
   cmake .. -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake
   make
   ```

## Usage
- **Run HTTP Server**:
  ```bash
  ./build/http_server
  ```
  Access endpoints:
  - `http://localhost:8080/api/health` (returns "OK")
  - `http://localhost:8080/api/users` (fetches users)
  - `http://localhost:8080/api/users/1` (fetches user ID 1)
- **Run TCP Echo Server**:
  ```bash
  ./build/tcp_echo_server
  ```
  Test with `test_tcp_client`:
  ```bash
  ./build/test_tcp_client
  ```
- **Run HTTP Socket Server**:
  ```bash
  ./build/http_socket_server
  ```
  Open Chrome and visit `http://localhost:8081` (displays "Hello, Chrome!").
  Test with `test_client`:
  ```bash
  ./build/test_client
  ```
- **Run Unit Tests (HTTP Client)**:
  ```bash
  ./build/test_http_client
  ```

## Testing
- **Manual Testing**:
  - Use Chrome or `curl` for HTTP server and HTTP socket server:
    ```bash
    curl http://localhost:8080/api/health
    curl http://localhost:8081
    ```
  - Use `test_tcp_client` for TCP echo server.
- **Automated Testing**:
  - HTTP client tests (`test_http_client`) are functional.
  - Server tests (`test_servers`) are incomplete due to linking and runtime issues.

## Known Issues
- Task 6 (Google Test integration) was not fully completed due to challenges with `cpp-httplib` and `boost::asio` server test lifecycles (hanging, `bad_executor`, linking errors).
- Ports 8080, 12345, and 8081 may conflict. Check with `lsof -i :port` and kill conflicting processes.

## Future Improvements
- Complete server integration tests using Google Test.
- Add logging for server requests and errors.
- Implement WebSockets for real-time communication.
- Enhance error handling in `HttpClient` and servers.

## Learning Outcomes
- Mastered HTTP server development with `cpp-httplib`.
- Learned HTTP client implementation with `libcurl`.
- Gained experience in TCP socket programming with `boost::asio`.
- Understood RESTful APIs through JSONPlaceholder integration.
- Practiced modular C++ design with STL (`std::string`, `std::shared_ptr`).
- Explored unit and integration testing with Google Test (partially).

## Acknowledgments
- Built as a learning project to explore backend development in C++.
- Inspired by JSONPlaceholder for REST API concepts.
- Uses open-source libraries: `cpp-httplib`, `nlohmann/json`, `libcurl`, `boost::asio`, `gtest`.

## License
MIT License. See [LICENSE](LICENSE) for details.