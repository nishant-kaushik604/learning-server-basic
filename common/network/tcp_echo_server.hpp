#ifndef TCP_ECHO_SERVER_HPP
#define TCP_ECHO_SERVER_HPP

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class TcpServer{
public:
    TcpServer(boost::asio::io_context& io_context, short port);
private:
    void do_accept();
    class TcpSession : public std::enable_shared_from_this<TcpSession>{
    public:
        TcpSession(tcp::socket socket);
        void start();
    private:
        void do_read();
        void do_write(std::size_t length);
        tcp::socket socket_;
        enum {max_length = 1024};
        char data_[max_length];
    };
    tcp::acceptor acceptor_;
};

#endif