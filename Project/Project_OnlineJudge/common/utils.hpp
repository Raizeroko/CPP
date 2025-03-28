#pragma once

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <atomic>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp> 

namespace com_utils
{
    const std::string temp_path = "./temp/";

    class TimeUtil
    {
    public:
        static std::string GetTimeStamp()
        {
            struct timeval time_stamp;
            gettimeofday(&time_stamp, nullptr);
            return std::to_string(time_stamp.tv_sec);
        }
        //获得毫秒时间戳
        static std::string GetTimeMs()
        {
            struct timeval _time;
            gettimeofday(&_time, nullptr);
            return std::to_string(_time.tv_sec * 1000 + _time.tv_usec / 1000);
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
        static std::string UniqueFileName()
        {
            static std::atomic_uint id(0);
            id++;
            // 毫秒级时间戳+原子性递增唯一值: 来保证唯一性
            std::string ms = TimeUtil::GetTimeMs();
            std::string uniq_id = std::to_string(id);
            return ms + "_" + uniq_id;
        }

        static bool WriteFile(const std::string& path_name, const std::string& content){
            std::ofstream write_file(path_name);
            if(!write_file){
                return false;
            }
            write_file << content;
            write_file.close();  // 确保关闭文件
            return true;
        }
        static bool ReadFile(const std::string& path_name, std::string* content, bool keep = false){
            content->clear();
            std::ifstream read_file(path_name);
            if(!read_file){
                return false;
            }
            std::string line;
            while(getline(read_file, line)){
                (*content) += line;
                (*content) += (keep ? "\n" : ""); 
            }
            read_file.close();
            return true;
        }
    };

    class StringUtil{
    public:
        static bool SplitString(const std::string input/*输入型参数*/, std::vector<std::string>& output/*输出型参数*/, const std::string& split_by){
            // output.resize(0);
            // std::stringstream ss(input);
            // std::string tmp;
            // while(getline(ss, tmp, split_by)){
            //     output.push_back(tmp);
            // }
            boost::split(output, input, boost::is_any_of(split_by), boost::algorithm::token_compress_on);

            return true;
        }
    };

}