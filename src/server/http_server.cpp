#include <httplib.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class HealthHandler{
public:
    void handle(httplib::Server& server) const{
        server.Get("/api/health", [](const httplib::Request& req, httplib::Response& res){
            json response = {{"status", "ok"}};
            res.set_content(response.dump(), "application/json");
        });
    }
};

class UserHandler{
public:
    void handle(httplib::Server& server){
        server.Get("/api/users", [](const httplib::Request&, httplib::Response& res){
            json users = {
                {{"id", 1}, {"name", "Nishant Kaushik"}, {"email", "nk@scsd.com"}},
                {{"id", 2}, {"name", "Amol Karande"}, {"email", "amol@ggl.com"}}
            };
            res.set_content(users.dump(), "application/json");
        });
    }
};

int main(){
    httplib::Server svr;

    auto health_handler = std::make_unique<HealthHandler>();
    auto user_handler = std::make_unique<UserHandler>();

    health_handler->handle(svr);
    user_handler->handle(svr);

    svr.listen("0.0.0.0", 8080);
    return 0;
}