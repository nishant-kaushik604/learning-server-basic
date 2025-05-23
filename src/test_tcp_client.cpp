#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main(){
    try{
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("localhost", "12345");
        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        std::string message = "Hello, TCP!\n";
        boost::asio::write(socket, boost::asio::buffer(message));

        char buffer[1024];
        boost::system::error_code ec;
        size_t len = socket.read_some(boost::asio::buffer(buffer), ec);
        if(!ec){
            std::cout << "Recieved: " << std::string(buffer, len) << std::endl;
        }else{
            std::cerr << "Error: " << ec.message() << std::endl;
        }
    }
    catch(std::exception& e){
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;

}