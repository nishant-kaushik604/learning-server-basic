#include "tcp_echo_server.hpp"
#include <boost/asio.hpp>
#include <iostream>

TcpServer::TcpServer(boost::asio::io_context &io_context, short port) : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
{
    do_accept();
}

void TcpServer::do_accept()
{
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
            if (!ec)
            {
                std::make_shared<TcpSession>(std::move(socket))->start();
            }
            do_accept();
        });
}

TcpServer::TcpSession::TcpSession(tcp::socket socket) : socket_(std::move(socket)){}

void TcpServer::TcpSession::start()
{
    do_read();
}

void TcpServer::TcpSession::do_read()
{
    auto self(shared_from_this());
    socket_.async_read_some(
        boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                do_write(length);
            }
        });
}

void TcpServer::TcpSession::do_write(std::size_t length)
{
    auto self(shared_from_this());
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                do_read();
            }
        });
}

int main(){
    boost::asio::io_context io_context;
    TcpServer server(io_context, 12345);
    io_context.run();
    return 0;
}