#include <iostream>
#include <string>

#include "compile_run.hpp"

// int main(){
//     std::string test = "test";
//     cs_compile::Compiler::Compile(test);
//     cs_run::Runner::Run(test, 5, 1024*1024*20);

//     return 0;
// }


// 测试代码
int main()
{
    std::string in_json;
    Json::Value in_value;
    // R"()", raw string
    in_value["code"] = R"(
#include<iostream>
int main(){
    std::cout << "测试代码" << std::endl;
    // while(1){
    //     char* tmp = new char[1024*1024*10];
    // }
    // while(1){}
    // aa
    std::cerr << "测试错误打印" << std::endl;
    return 0;
})";
    in_value["input"] = "";
    in_value["cpu_limit"] = 1;
    in_value["mem_limit"] = 1024*1024*30;
    // Json::FastWriter writer;
    // in_json = writer.write(in_value);
    
    Json::StreamWriterBuilder writer;
    // 禁止将中文转译为unicode
    writer.settings_["emitUTF8"] = true;
    in_json = Json::writeString(writer, in_value);
    std::cout << in_json << std::endl;
    std::string out_json; 

    cs_compile_run::CompileRun::Start(in_json, out_json);
    std::cout << out_json << std::endl;
    return 0;
}