#include <gtest/gtest.h>
#include "http_client/http_client.hpp"

TEST(HttpClientTest, GetRequestSuccess){
    HttpClient client;
    std::string response = client.get("https://jsonplaceholder.typicode.com/users/1");
    EXPECT_FALSE(response.empty());
    EXPECT_TRUE(response.find("\"id\": 1") != std::string::npos);
}

TEST(HttpClientTest, InvalidUrlThrows){
    HttpClient client;
    EXPECT_THROW(client.get("http://invalid-url"), std::runtime_error);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}