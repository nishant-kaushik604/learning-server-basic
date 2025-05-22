#ifndef HTTP_CLIENT_HPP
#define HTTP_CLIENT_HPP

#include <string>

class HttpClient{
public:
    HttpClient();
    ~HttpClient();

    std::string get(std::string_view url);

private:
    //static size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* userp);

    // Non-static callback
    size_t writeCallback(void* ccontents, size_t size, size_t nmemb);

    // Static wrapper to pass to libcurl
    static size_t writeCallbackWrapper(void* contents, size_t size, size_t nmemb, void* userp); 

    std::string response_;
};

#endif