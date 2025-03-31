#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <mysql/mysql.h>
#include "../common/utils.hpp"
#include "../common/log.hpp"

// 根据题目list文件，加载所有题目信息到内存中
// model: 主要用来和数据交互，对外提供访问数据的接口

namespace os_model
{
    using namespace std;
    using com_utils::FileUtil;
    using com_utils::StringUtil;
    using namespace com_log;

    struct Question
    {
        string number; // 题号
        string title;  // 标题
        string star;   // 难度
        string desc;   // 题目描述
        string header; // 默认提供代码
        string tail;   // 测试用例代码
        int cpu_limit; // 时间限制
        int mem_limit; // 内存限制
    };

    // MySQL Server信息
    const string questions_table = "oj_questions"; // 表名
    const string sql_host = "127.0.0.1";           // MySQL ip
    const string sql_usr = "Raizeroko";            // MySQL 用户名
    const string sql_pwd = "wso2968314";           // 用户密码
    const string sql_db = "oj";                    // 数据库名
    const int sql_port = 3306;                     // 端口

    class Model
    {
    private:
        bool QueryMySql(const std::string &sql, vector<Question> *out)
        {
            MYSQL *conn = mysql_init(nullptr);
            // 连接到 MySQL 服务器
            if (!mysql_real_connect(conn, sql_host.c_str(), sql_usr.c_str(), sql_pwd.c_str(), sql_db.c_str(),
                                    sql_port, nullptr /*unix域套接字路径*/, 0 /*客户端标志*/))
            {
                return false;
            }

            // 设置字符集，防止乱码
            mysql_set_character_set(conn, "utf8");


            // 执行查询
            if (mysql_query(conn, sql.c_str()))
            {
                mysql_close(conn);
                return false;
            }

            // 获取结果
            MYSQL_RES *res = mysql_store_result(conn);
            if (!res)
            {
                mysql_close(conn);
                return false;
            }


            // 获取列数
            int num_fields = mysql_num_fields(res);
            MYSQL_ROW row;

            // 遍历获取结果
            while ((row = mysql_fetch_row(res)))
            {
                Question line;
                line.number = row[0];
                line.title = row[1];
                line.star = row[2];
                line.desc = row[3];
                line.header = row[4];
                line.tail = row[5];
                line.cpu_limit = stoi(row[6]);
                line.mem_limit = stoi(row[7]);
                out->push_back(line);
            }

            // 释放结果
            mysql_free_result(res);
            mysql_close(conn);


            return true;
        }

    public:
        Model() {}
        ~Model() {}
        bool GetAllQuestions(vector<Question> *out /*输出型参数*/)
        {
            out->resize(0);

            string sql;

            // 构建sql语句
            sql += "select * from ";
            sql += questions_table;

            // 获取全部问题的sql
            if (!QueryMySql(sql, out))
            {
                LOG(ERROR) << "load sql all questions error" << endl;
                return false;
            }
            return true;
        }

        bool GetOneQuestion(const string &number /*输入型参数*/, Question *q /*输出型参数*/)
        {
            string sql;
            sql += "select * from ";
            sql += questions_table;
            sql += " where id = ";
            sql += number;
            vector<Question> tmp;
            if (!QueryMySql(sql, &tmp))
            {
                LOG(ERROR) << "load sql one questions error" << endl;
                return false;
            }
            if(tmp.size() != 1){
                LOG(ERROR) << "load sql one questions error" << endl;
                return false;
            }
            *q = tmp[0];
            return true;
        }
    };
}
