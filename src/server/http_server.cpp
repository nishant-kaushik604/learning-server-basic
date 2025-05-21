#include <httplib.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main(){
    httplib::Server svr;

    svr.Get("/api/health", [](const httplib::Request&, httplib::Response& res){
        json response = {{"status", "ok"}};
        res.set_content(response.dump(), "application/json");
    });

    svr.listen("0.0.0.0", 8080);
    return 0;
}