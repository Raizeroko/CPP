#include <iostream>
#include <string>

#include "compile_run.hpp"
#include "../common/httplib.h"

using namespace httplib;

void Usage(const std::string proc){
    std::cout << "Please use like>> " << proc <<" [port]";

}

// 将compile_run形成网络服务
int main(int argc, char* argv[]){
    if(argc != 2){
        Usage(argv[0]);
        return 0;
    }

    Server svr;

    // 请求服务测试
    // svr.Get("/hello", [](const Request& req, Response &resp){
    //     std::cout << "get req" << std::endl;
    //     resp.set_content("httplib 测试", "text/plain; charset=utf-8");

    // });

    svr.Post("/compile_run", [](const Request& req, Response &resp){
        std::string in_json = req.body;
        std::cout << in_json;
        std::string out_json;
        cs_compile_run::CompileRun::Start(in_json, out_json);
        resp.set_content(out_json, "application/json; charset=utf-8");
    });

    
    svr.listen("0.0.0.0", std::stoi(argv[1]));
    return 0;
}


// 测试代码

// int main(){
//     std::string test = "test";
//     cs_compile::Compiler::Compile(test);
//     cs_run::Runner::Run(test, 5, 1024*1024*20);

//     return 0;
// }

// int main()
// {
//     std::string in_json;
//     Json::Value in_value;
//     // R"()", raw string
//     in_value["code"] = R"(
// #include<iostream>
// int main(){
//     std::cout << "测试代码" << std::endl;
//     // while(1){
//     //     char* tmp = new char[1024*1024*10];
//     // }
//     // while(1){}
//     // aa
//     std::cerr << "测试错误打印" << std::endl;
//     return 0;
// })";
//     in_value["input"] = "";
//     in_value["cpu_limit"] = 1;
//     in_value["mem_limit"] = 1024*1024*30;
//     // Json::FastWriter writer;
//     // in_json = writer.write(in_value);
    
//     Json::StreamWriterBuilder writer;
//     // 禁止将中文转译为unicode
//     writer.settings_["emitUTF8"] = true;
//     in_json = Json::writeString(writer, in_value);
//     std::cout << in_json << std::endl;
//     std::string out_json; 

//     cs_compile_run::CompileRun::Start(in_json, out_json);
//     std::cout << out_json << std::endl;
//     return 0;
// }
