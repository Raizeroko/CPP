#include "oj_model.hpp"
#include "oj_view.hpp"


namespace os_control{
    using namespace os_model;
    using namespace os_view;

    class Control{
    private:
        Model _model;
        View _view;

    public:
        Control(){}
        ~Control(){}

        bool AllQuestions(string *html/*输出型参数*/){
            // 使用model获取信息，使用veiw对信息渲染，将html返回
            vector<Question> all_ques;
            // 获取信息
            _model.GetAllQuestions(&all_ques);
            // 渲染网页
            _view.AllExpandHtml(all_ques, html);
            return true;
        }

        bool OneQuestion(const string& number/*输入型参数*/, string* html/*输出型参数*/){
            // 使用model获取对应题号信息，使用veiw对信息渲染，将html返回
            Question one_que;
            // 获取信息
            _model.GetOneQuestion(number, &one_que);
            // 渲染网页
            _view.OneExpandHtml(one_que, html);
            return true;
        }
        
    };



};