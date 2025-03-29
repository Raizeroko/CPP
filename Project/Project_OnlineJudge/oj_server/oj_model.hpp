#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "../common/utils.hpp"
#include "../common/log.hpp"


// 根据题目list文件，加载所有题目信息到内存中
// model: 主要用来和数据交互，对外提供访问数据的接口

namespace os_model{
    using namespace std;
    using com_utils::StringUtil;
    using com_utils::FileUtil;
    using namespace com_log;

    struct Question{
        string number;     // 题号
        string title;      // 标题
        string star;       // 难度
        int cpu_limit;     // 时间限制
        int mem_limit;     // 内存限制
        string desc;       // 题目描述
        string header;     // 默认提供代码
        string tail;       // 测试用例代码
    };

    const string questions_list = "./questions/questions.list";
    const string questions_path = "./questions/";

    class Model{
    private:
        unordered_map<string, Question> _questions;
        bool LoadAllQuestions(){
            // 基于questions.list加载所有数据到Quetions中
            ifstream in(questions_list);
            string line;
            while(getline(in, line)){
                vector<string> tokens;
                if(!StringUtil::SplitString(line, &tokens, ",")){
                    LOG(ERROR) << "SplitString error" << endl;
                    return false;
                }
                if(tokens.size() != 5){
                    LOG(ERROR) << "Token size error" << endl;
                    return false;
                }
                Question ques;
                ques.number = tokens[0];
                ques.title = tokens[1];
                ques.star = tokens[2];
                ques.cpu_limit = stoi(tokens[3]);
                ques.mem_limit = stoi(tokens[4]);
                // 题目描述和对应代码提取。
                string question_path = questions_path;
                question_path += ques.number;
                question_path += "/";
                if(!FileUtil::ReadFile(question_path+"desc.txt", &ques.desc, true)){
                    LOG(ERROR) << "read desc.txt fail" << endl;
                }
                if(!FileUtil::ReadFile(question_path+"header.cpp", &ques.header, true)){
                    LOG(ERROR) << "read header.cpp fail" << endl;
                }
                if(!FileUtil::ReadFile(question_path+"tail.cpp", &ques.tail, true)){
                    LOG(ERROR) << "read tail.cpp fail" << endl;
                }
                _questions.insert({ques.number, ques});
            }
            LOG(INFO) << "load questions success" << endl;
            in.close();
            return true;
        }
    public:
        Model(){
            LoadAllQuestions();
        }
        ~Model(){}
        bool GetAllQuestions(vector<Question>* out/*输出型参数*/){
            out->resize(0);
            if(_questions.size() == 0){
                // 没有题目信息
                LOG(ERROR) << "没有题目信息" << std::endl;
                return false;
            }
            // 将所有题目信息转为vector返回
            for(auto cur: _questions){
                out->push_back(cur.second);
            }
            sort(out->begin(), out->end(), [](const Question& a, const Question& b){return a.number < b.number;});
            return true;
        }

        bool GetOneQuestion(const string& number/*输入型参数*/, Question* q/*输出型参数*/){
            // 根据题号获取对应题目信息
            auto it = _questions.find(number);
            if(it == _questions.end()){
                // 找不到该题目
                LOG(ERROR) << "找不到该题目: " << number << std::endl;
                return false;
            }
            
            *q = it->second;
            return true;
        }
    };
}












