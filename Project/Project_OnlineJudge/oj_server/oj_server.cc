#include <iostream>
#include "../common/httplib.h"

using namespace httplib;
int main(){
    Server svr;

    // svr.Get()
    svr.Get("/all_questions", [](const Request& req, Response& resp) {
        resp.set_content("题目列表", "text/plain; charset=utf-8");
    });

    svr.Get(R"(/questions/(\d+))", [](const Request& req, Response& resp) {
        std::string number = req.matches[1];
        resp.set_content("选择题目：" + number, "text/plain; charset=utf-8");
    });

    svr.Get(R"(/judge/(\d+))", [](const Request& req, Response& resp) {
        std::string number = req.matches[1];
        resp.set_content("判断题目：" + number, "text/plain; charset=utf-8");
    });

    svr.set_base_dir("./root");
    svr.listen("0.0.0.0", 7999);
}