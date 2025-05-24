#include <gtest/gtest.h>
#include <boost/asio.hpp>
#include "http_client/http_client.hpp"
#include "network/tcp_echo_server.hpp"
#include "network/http_socket_server.hpp"
#include <thread>
#include <chrono>
#include <memory>
#include <httplib.h>

using boost::asio::ip::tcp;

// Runner for cpp-httplib server
class HttplibRunner {
public:
    HttplibRunner(short port)
        : server(std::make_shared<httplib::Server>()), running(false) {
        server->Get("/api/health", [](const httplib::Request&, httplib::Response& res) {
            res.set_content("OK", "text/plain");
        });
        server_thread = std::thread([this, port]() {
            running = true;
            server->listen("localhost", port);
            running = false;
        });
        // Wait for server to start
        while (!running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    ~HttplibRunner() {
        if (running) {
            server->stop();
        }
        if (server_thread.joinable()) {
            server_thread.join();
        }
    }

private:
    std::shared_ptr<httplib::Server> server;
    std::thread server_thread;
    bool running;
};

// Runner for boost::asio servers
class AsioRunner {
public:
    AsioRunner(std::function<void(boost::asio::io_context&, short)> server_func, short port)
        : io_context(std::make_shared<boost::asio::io_context>()) {
        server_thread = std::thread([this, server_func, port]() {
            server_func(*io_context, port);
            io_context->run();
        });
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Wait for server to start
    }

    ~AsioRunner() {
        io_context->stop();
        if (server_thread.joinable()) {
            server_thread.join();
        }
    }

private:
    std::shared_ptr<boost::asio::io_context> io_context;
    std::thread server_thread;
};

TEST(ServerTest, HttpServerHealthCheck) {
    auto runner = std::make_unique<HttplibRunner>(8080);
    HttpClient client;
    std::string response = client.get("http://localhost:8080/api/health");
    EXPECT_EQ(response, "OK");
}

TEST(ServerTest, TcpEchoServerEchoes) {
    auto runner = std::make_unique<AsioRunner>(
        [](boost::asio::io_context& io_context, short port) {
            TcpServer server(io_context, port);
        }, 12345);

    boost::asio::io_context io_context;
    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve("localhost", "12345");
    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);
    std::string message = "Test Echo\n";
    boost::asio::write(socket, boost::asio::buffer(message));
    char buffer[1024];
    size_t len = socket.read_some(boost::asio::buffer(buffer));
    EXPECT_EQ(std::string(buffer, len), message);
}

TEST(ServerTest, HttpSocketServerReturnsHtml) {
    auto runner = std::make_unique<AsioRunner>(
        [](boost::asio::io_context& io_context, short port) {
            HttpServer server(io_context, port);
        }, 8081);

    HttpClient client;
    std::string response = client.get("http://localhost:8081");
    EXPECT_TRUE(response.find("<h1>Hello, Chrome!</h1>") != std::string::npos);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}