#include "http_client.hpp"
#include <curl/curl.h>

HttpClient::HttpClient(){
    curl_global_init(CURL_GLOBAL_ALL);
}

HttpClient::~HttpClient(){
    curl_global_cleanup();
}

std::string HttpClient::get(std::string_view url)
{
    CURL* curl = curl_easy_init();
    if (!curl)
    {
        throw std::runtime_error("Failed to initialize CURL");
    }

    response_.clear();

    curl_easy_setopt(curl, CURLOPT_URL, url.data());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallbackWrapper);
    // Pass this instance as userp
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        throw std::runtime_error(curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl);
    
    return response_;
}

size_t HttpClient::writeCallback(void *contents, size_t size, size_t nmemb)
{
    response_.append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

size_t HttpClient::writeCallbackWrapper(void *contents, size_t size, size_t nmemb, void *userp)
{
    // Cast userp to HttpClient* and call non-static writeCallback

    return static_cast<HttpClient*>(userp)->writeCallback(contents, size, nmemb);
}
