#pragma once
#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../common/utils.hpp"
#include "../common/log.hpp"


// 只负责代码编译
namespace cs_compile
{
    using com_utils::FileUtil;
    using com_utils::PathUtil;
    using namespace com_log;
    
    class Compiler
    {
    public:
        Compiler()
        {
        }
        ~Compiler()
        {
        }

        static bool Compile(const std::string &file_name)
        {
            int child = fork();
            if (child == 0)
            {
                int op_fd = open(PathUtil::CompileError(file_name).c_str(), O_RDWR | O_CREAT, 0644);
                if (op_fd == -1)
                {
                    // open fail
                    LOG(ERROR) << "open fail" << std::endl;
                }
                int rdp = dup2(op_fd, 2);
                if (rdp == -1)
                {
                    // dup fail
                    LOG(ERROR) << "dup fail" << std::endl;
                }
                // g++ -o target src -std=c++11
                int rexe = execlp("g++", "g++", "-o", PathUtil::Target(file_name).c_str(), PathUtil::Source(file_name).c_str(),
                                  "-std=c++11");
                if (rexe == -1)
                {
                    LOG(ERROR) << "execlp fail" << std::endl;
                }
                exit(-1);
            }
            else
            {
                waitpid(child, nullptr, 0);
                if (!FileUtil::IsFileExist(PathUtil::Target(file_name)))
                {
                    // 编译失败
                    LOG(Info) << "编译失败" << std::endl;
                    return false;
                }
            
                // 编译成功
                LOG(Info) << "编译成功" << std::endl;
                return true;
            }
        }
    };
}
