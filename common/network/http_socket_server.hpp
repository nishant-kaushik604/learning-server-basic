#ifndef HTTP_SOCKET_SERVER_HPP
#define HTTP_SOCKET_SERVER_HPP

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class HttpServer{
public:
    HttpServer(boost::asio::io_context& io_context, short port);
private:
    void do_accept();
    class HttpSession : std::enable_shared_from_this<HttpSession>{
    public:
        HttpSession(tcp::socket socket);
        void start();
    private:
        void do_read();
        void do_write(const std::string& response);
        tcp::socket socket_;
        enum {max_length = 1024};
        char data_[max_length];
    };
    tcp::acceptor acceptor_;
};

#endif