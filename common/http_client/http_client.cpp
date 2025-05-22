#include "http_client.hpp"
#include <curl/curl.h>

HttpClient::HttpClient(){
    curl_global_init(CURL_GLOBAL_ALL);
}

HttpClient::~HttpClient(){
    curl_global_cleanup();
}

std::string HttpClient::get(std::string_view url) const
{
    CURL* curl = curl_easy_init();
    if (!curl)
    {
        throw std::runtime_error("Failed to initialize CURL");
    }

    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, url.data());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        throw std::runtime_error(curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl);
    
    return response;
}

size_t HttpClient::writeCallback(void *contents, size_t size, size_t nmemb, std::string *userp)
{
    userp->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}
