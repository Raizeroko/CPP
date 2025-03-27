#include <string>
#include <jsoncpp/json/json.h>
#include <iostream>

#include "compiler.hpp"
#include "runner.hpp"

#include "../common/utils.hpp"
#include "../common/log.hpp"

// 唯一文件名
// FileUtil::UniqueFileName();
// 毫秒级时间戳

// 形成临时.cpp文件

// 错误码转描述
// CodeToDecrib()

// 清理临时文件
// RemoveTemp()

namespace cs_compile_run
{
    using namespace cs_compile;
    using namespace cs_run;
    using com_utils::FileUtil;
    using com_utils::PathUtil;

    class CompileRun
    {
        CompileRun() {}
        ~CompileRun() {}

        // 清除临时文件
        static void RemoveTempFile(const std::string &file_name)
        {
            // 清理⽂件的个数是不确定的，但是有哪些我们是知道的 
            std::string src = PathUtil::Source(file_name); 
            if(FileUtil::IsFileExist(src)) unlink(src.c_str());

            std::string compiler_error = PathUtil::CompileError(file_name);
            if (FileUtil::IsFileExist(compiler_error)) unlink(compiler_error.c_str());
            
            std::string execute = PathUtil::Target(file_name);
            if (FileUtil::IsFileExist(execute)) unlink(execute.c_str());
            
            std::string in_file = PathUtil::Stdin(file_name);
            if (FileUtil::IsFileExist(in_file)) unlink(in_file.c_str());
            
            std::string out_file = PathUtil::Stdout(file_name);
            if (FileUtil::IsFileExist(out_file)) unlink(out_file.c_str());
            
            std::string err_file = PathUtil::Stderr(file_name);
            if (FileUtil::IsFileExist(err_file)) unlink(err_file.c_str());
        }

        // 状态码对应描述
        static std::string CodeToDescribe(int status_code, const std::string file_name)
        {
            std::string describe;
            std::string compile_err;
            switch (status_code)
            {
            case 0:
                describe = "[运行成功]";
                break;
            case -1:
                describe = "[代码为空]";
                break;
            case -2:
                describe = "[编译错误]";
                break;
            case -3:
                describe = "[未知错误]";
                break;
            case -4:
                describe = "[json错误]";
                break;
            case SIGABRT:
                describe = "[内存溢出]";
                break;
            case SIGXCPU:
                describe = "[运行超时]";
                break;
            case SIGFPE:
                describe = "[浮点溢出]";
                break;
            default:
                describe = "[未知, " + std::to_string(status_code) + "]";
            }
            return describe;
        }

        // 状态码转Json序列化
        static std::string CodeToJson(int status_code, std::string file_name)
        {
            Json::Value ret_json;
            ret_json["status"] = status_code;
            ret_json["reason"] = CodeToDescribe(status_code, file_name);
            if (status_code == 0)
            {
                std::string out_content;
                if (!FileUtil::ReadFile(PathUtil::Stdout(file_name), out_content))
                {
                    LOG(ERROR) << "read stdout error" << std::endl;
                }
                ret_json["stdout"] = out_content;
                std::string err_content;
                if (!FileUtil::ReadFile(PathUtil::Stderr(file_name), err_content))
                {
                    LOG(ERROR) << "read stderr error" << std::endl;
                }
                ret_json["stderr"] = err_content;
            }
            else if(status_code < 0){
                std::string err_content;
                if (!FileUtil::ReadFile(PathUtil::CompileError(file_name), err_content))
                {
                    LOG(ERROR) << "read stderr error" << std::endl;
                }
                ret_json["stderr"] = err_content;
            }
            Json::StreamWriterBuilder writer;
            // 禁止将中文转译为unicode
            writer.settings_["emitUTF8"] = true;
            return Json::writeString(writer, ret_json);

            // Json::StyledWriter writer;
            // return writer.write(ret_json);
        }

    public:
        static void Start(const std::string &in_json, std::string &out_json)
        {
            /***************************************
             * 输⼊:
             * code： ⽤⼾提交的代码
             * input: ⽤⼾给⾃⼰提交的代码对应的输⼊，不做处理 * cpu_limit: 时间要求
             * mem_limit: 空间要求
             *
             * 输出:
             * [必填]
             * - status: 状态码
             * - reason: 请求结果
             * [选填]
             * - stdout: 我的程序运⾏完的结果
             * - stderr: 我的程序运⾏完的错误结果
             *
             * 参数：
             * in_json: {"code": "#include...", "input": "","cpu_limit":1, "mem_limit":10240}
             * out_json: {"status":"0", "reason":"","stdout":"","stderr":"",}
             ****************************************/
            // 形成临时文件名
            std::string file_name = FileUtil::UniqueFileName();
            int status_code;

            // json反序列化
            Json::CharReaderBuilder reader;
            Json::Value json_value;
            std::string errors;
            std::istringstream jsonStream(in_json);
            if (!Json::parseFromStream(reader, jsonStream, &json_value, &errors))
            {
                LOG(ERROR) << "input json error" << std::endl;
                status_code = -4;
                out_json = CodeToJson(status_code, file_name);
                return;
            }
            std::string code = json_value["code"].asString();
            std::string input = json_value["input"].asString();
            int cpu_limit = json_value["cpu_limit"].asInt();
            int mem_limit = json_value["mem_limit"].asInt();

            // 状态处理
            Json::Value ret_json;
            int exit_code;
            if (code.size() == 0)
            {
                // 没有代码
                status_code = -1;
                out_json = CodeToJson(status_code, file_name);
                return;
            }

            // 将代码写入文件
            if (!FileUtil::WriteFile(PathUtil::Source(file_name), code))
            {
                // 未知错误（服务器错误统一为未知错误）
                status_code = -3;
                out_json = CodeToJson(status_code, file_name);
                RemoveTempFile(file_name);
                return;
            }

            // 编译文件
            if (!Compiler::Compile(file_name))
            {
                // 编译出错
                status_code = -2;
                out_json = CodeToJson(status_code, file_name);
                RemoveTempFile(file_name);
                return;
            }

            // 运行文件
            exit_code = Runner::Run(file_name, cpu_limit, mem_limit);
            if (exit_code > 0)
            {
                // 运行出错
                status_code = exit_code;
            }
            else if (exit_code < 0)
            {
                // 未知错误
                status_code = -3;
            }
            else
            {
                // 正常运行
                status_code = 0;
            }
            out_json = CodeToJson(status_code, file_name);
            RemoveTempFile(file_name);

            return;
        }
    };

}
