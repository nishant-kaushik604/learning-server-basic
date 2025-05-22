#ifndef HTTP_CLIENT_HPP
#define HTTP_CLIENT_HPP

#include <string>

class HttpClient{
public:
    HttpClient();
    ~HttpClient();

    std::string get(std::string_view url) const;

private:
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
};

#endif