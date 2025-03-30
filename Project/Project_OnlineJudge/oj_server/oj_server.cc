#include <iostream>
#include "../common/httplib.h"
#include "oj_control.hpp"

using namespace httplib;
using namespace os_control;
int main(){
    Server svr;
    Control ctl;
    // cout << "test" << endl;

    // svr.Get()
    svr.Get("/all_questions", [&ctl](const Request& req, Response& resp) {
        string html;
        ctl.AllQuestions(&html);
        resp.set_content(html, "text/html; charset=utf-8");
    });

    svr.Get(R"(/questions/(\d+))", [&ctl](const Request& req, Response& resp) {
        std::string number = req.matches[1];
        string html;
        ctl.OneQuestion(number, &html);
        resp.set_content(html, "text/html; charset=utf-8");
    });

    svr.Post(R"(/judge/(\d+))", [&ctl](const Request& req, Response& resp) {
        std::string number = req.matches[1];
        string in_json = req.body;
        string out_json;
        ctl.JudgeQuestion(number, in_json, &out_json);
        resp.set_content(out_json, "text/plain; charset=utf-8");
    });

    svr.set_base_dir("./root");
    svr.listen("0.0.0.0", 7999);
}


// #include "../common/utils.hpp"
// #include <vector>
// #include <string>

// int main(){
//     std::string tmp = "1,判断回文,简单,1,,,,,,,,,40000";
//     using com_utils::StringUtil;
//     std::vector<std::string> out;
//     StringUtil::SplitString(tmp, out, ",");
//     for(auto e: out){
//         std::cout << e << std::endl;
//     }

// }