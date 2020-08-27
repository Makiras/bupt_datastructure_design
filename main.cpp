#include "algorithm.h"
#include "cinatra.hpp"
#include "config.h"
#include "interface.h"
#include "model.h"
#include <bits/stdc++.h>

int main()
{
    int max_thread_num = std::thread::hardware_concurrency();
    cinatra::http_server server(max_thread_num);
    server.listen("0.0.0.0", "8080");
    server.set_http_handler<cinatra::GET>("/", [](cinatra::request &req, cinatra::response &res) {
        res.redirect("/index.html");
    });
    init();

    // USING RESTFUL API

    server.set_http_handler<cinatra::POST, cinatra::DEL>("/person", [](cinatra::request &req, cinatra::response &res) {
        auto p_name = req.get_query_value("p_name");
        auto p_start = req.get_query_value("p_start");
        auto p_end = req.get_query_value("p_end");
        auto p_start_time = req.get_query_value("p_start_time");
        auto p_time_limit = req.get_query_value("p_time_limit");

        if (p_name.empty())
        {
            res.set_status_and_content(cinatra::status_type::ok, "no name", cinatra::req_content_type::json);
            return;
        }
        if (req.get_method() == "DEL" || req.get_method() == "DELETE")
        {
            auto p_name = req.get_query_value("p_name");
            delete_person(std::string(p_name));
            res.set_status_and_content(cinatra::status_type::ok, "Done", cinatra::req_content_type::json);
            return;
        }
        if (p_time_limit.empty())
            p_time_limit = "0";

        char *resStr;
        new_person(std::string(p_name),
                   std::stoi(std::string(p_start)),
                   std::stoi(std::string(p_end)),
                   std::stoi(std::string(p_start_time)),
                   std::stoi(std::string(p_time_limit)),
                   resStr);
        std::cout << "resStr" << std::endl;
        std::cout << resStr << std::endl;
        res.set_status_and_content(cinatra::status_type::ok, resStr, cinatra::req_content_type::json);
        std::cout << p_name << " " << p_start << " " << p_end << " " << p_start_time << std::endl;
        if (!p_time_limit.empty())
            std::cout << "Time limit in " << p_time_limit << std::endl;
        
        // rember to free prevent memeory leak !
        delete[] resStr;
    });

    server.set_http_handler<cinatra::GET, cinatra::POST>("/get_map", [](cinatra::request &req, cinatra::response &res){
        char *resStr;
        get_map(resStr);
        res.set_status_and_content(cinatra::status_type::ok,resStr,cinatra::req_content_type::json);
        // rember to free prevent memeory leak !
        delete[] resStr;
    });

    server.run();
    destory();
    return 0;
}
