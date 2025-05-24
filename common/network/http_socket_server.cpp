#include "http_socket_server.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include <string>

HttpServer::HttpServer(boost::asio::io_context &io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
{
    do_accept();
}

void HttpServer::do_accept()
{
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
            if (!ec)
            {
                std::make_shared<HttpSession>(std::move(socket))->start();
            }
            do_accept();
        });
}

HttpServer::HttpSession::HttpSession(tcp::socket socket) : socket_(std::move(socket)){}

void HttpServer::HttpSession::start()
{
    do_read();
}

void HttpServer::HttpSession::do_read()
{
    auto self(shared_from_this());
    socket_.async_read_some(
        boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                // Print request to console
                std::cout << "Recieved HTTP request:\n"
                          << std::string(data_, length) << "\n---\n";

                // Prepare a basic HTML response
                std::string response =
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html\r\n"
                    "Content-Length: 42\r\n"
                    "Connection: close\r\n"
                    "\r\n"
                    "<html><body><h1>Hello, Chrome!</h1></body></html>";

                do_write(response);
            }
        });
}

void HttpServer::HttpSession::do_write(const std::string &response)
{
    auto self(shared_from_this());
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(response),
        [this, self](boost::system::error_code ec, std::size_t)
        {
            if (!ec)
            {
                // Close the socket after responding
                socket_.close();
            }
        });
}


int main(){

    try{
        boost::asio::io_context io_context;
        HttpServer server(io_context, 8081);    // Use port 8081 to avoid conflict with http_server
        io_context.run();
    }
    catch(const std::exception& e){
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

