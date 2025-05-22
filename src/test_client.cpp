#include "http_client/http_client.hpp"
#include <iostream>

int main(){
    HttpClient client;
    try{
        std::string response = client.get("https://jsonplaceholder.typicode.com/users");
        std::cout << "Response: " << response.substr(0, 100) << "..." << std::endl;
    }catch(const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}