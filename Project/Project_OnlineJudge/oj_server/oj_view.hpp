#include <vector>
#include <string>
#include <ctemplate/template.h>

// #include "oj_model.hpp"
#include "oj_model_mysql.hpp"

// 使用ctemplate完成页面渲染
// 将传入的html页面使用ctemplate替换其中的key为questions中对应的字段
namespace os_view{
    using namespace std;
    using namespace os_model;

    const string all_questions_path = "./template/all_questions.html";
    const string one_questions_path = "./template/one_questions.html";

    class View{
    public:
        View(){}
        ~View(){}

        // 题目列表页面渲染
        void AllExpandHtml(const vector<Question> &questions, std::string *html)
        {
            // 创建数据字典
            ctemplate::TemplateDictionary dict("parent");

            // 填充 questions_list 数据
            for (const auto& q : questions) {
                // AddSectionDictionary 用于添加循环列表数据
                ctemplate::TemplateDictionary* sub_dict = dict.AddSectionDictionary("questions_list");
                sub_dict->SetValue("number", q.number);     // 设置题号
                sub_dict->SetValue("title", q.title);       // 设置标题
                sub_dict->SetValue("star", q.star);         // 设置难度
            }

            // 加载模板文件
            ctemplate::Template* tpl = ctemplate::Template::GetTemplate(all_questions_path, ctemplate::DO_NOT_STRIP);

            // 渲染模板
            tpl->Expand(html, &dict);
        }

        // 单个做题页面渲染
        void OneExpandHtml(const struct Question &q, std::string *html)
        {
            // 创建数据字典
            ctemplate::TemplateDictionary dict("parent");

            // 填充 questions_list 数据
            dict.SetValue("number", q.number);
            dict.SetValue("title", q.title);
            dict.SetValue("star", q.star);
            dict.SetValue("desc", q.desc);
            dict.SetValue("code", q.header);

            // 加载模板文件
            ctemplate::Template* tpl = ctemplate::Template::GetTemplate(one_questions_path, ctemplate::DO_NOT_STRIP);

            // 渲染模板
            tpl->Expand(html, &dict);

        }
    };
};