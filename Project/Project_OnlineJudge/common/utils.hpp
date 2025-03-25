#pragma once

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
namespace com_utils
{
    const std::string temp_path = "./temp/";

    class TimeUtil
    {
    public:
        static std::string GetTimeStamp()
        {
            struct timeval _time;
            gettimeofday(&_time, nullptr);
            return std::to_string(_time.tv_sec);
        }

    };

    class PathUtil
    {
    public:
        static std::string AddSuffix(const std::string &file_name, const std::string &suffix)
        {
            std::string path = temp_path;
            path += file_name;
            path += suffix;
            return path;
        }
        
        // 编译文件
        static std::string Source(const std::string file_name)
        {
            return AddSuffix(file_name, ".cpp");
        }
        static std::string Target(const std::string file_name)
        {
            return AddSuffix(file_name, ".exe");
        }
        static std::string CompileError(const std::string file_name)
        {
            return AddSuffix(file_name, ".cmp_err");
        }
        // 运行文件
        static std::string Stdin(const std::string file_name)
        {
            return AddSuffix(file_name, ".stdin");
        }
        static std::string Stdout(const std::string file_name)
        {
            return AddSuffix(file_name, ".stdout");
        }
        static std::string Stderr(const std::string file_name)
        {
            return AddSuffix(file_name, ".stderr");
        }

    };

    class FileUtil
    {
    public:
        static bool IsFileExist(const std::string path)
        {
            struct stat st;
            // 判断文件是否存在
            int rs = stat(path.c_str(), &st);
            if (rs == -1)
            {
                return false;
            }
            return true;
        }
    };

}