#include <iostream>
#include "httplib.h"   
#include <string>
#include <vector>

int main() {
    using namespace httplib;

    Server svr;

   
    svr.Get("/", [](const Request&, Response &res) {
        res.set_content("Mental Wellness Site Backend Running!", "text/plain");
    });

    
    svr.Get("/tips", [](const Request&, Response &res) {
        std::string tips_json =
            R"({
                "tips": [
                    "Take short breaks during study sessions.",
                    "Stay hydrated throughout the day.",
                    "Talk to friends or mentors when stressed.",
                    "Get fresh air and sunlight regularly.",
                    "Practice deep breathing for relaxation."
                ],
                "note": "These are general wellness suggestions, not professional medical advice."
            })";

        res.set_content(tips_json, "application/json");
    });

    
    svr.Post("/contact", [](const Request &req, Response &res) {
      
        auto name = req.get_param_value("name");
        auto message = req.get_param_value("message");

      
        std::cout << "New message received:\n";
        std::cout << "Name: " << name << "\n";
        std::cout << "Message: " << message << "\n\n";

        res.set_content("Message received!", "text/plain");
    });

    std::cout << "Server running on http://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);

    return 0;
}
