#include <jsoncpp/json/json.h>
#include <fstream>
#include <mutex>

#include "../common/httplib.h"
// #include "oj_model.hpp"
#include "oj_model_mysql.hpp"
#include "oj_view.hpp"


namespace os_control{
    using namespace os_model;
    using namespace os_view;

    const string service_machines_conf = "./conf/service_machine.conf";

    class CompileMachine{
    private:
        string _ip;
        int _port;
        shared_ptr<atomic<uint64_t>> _load; 
    public:
        CompileMachine(string ip, int port):_ip(ip), _port(port){
            _load = std::make_shared<std::atomic<uint64_t>>(0);
        }
        ~CompileMachine(){
        }
        std::string GetIp(){
            return _ip;
        }
        int GetPort(){
            return _port;
        }
        // 增加负载
        void IncreaseLoad(){
            _load->fetch_add(1, std::memory_order_relaxed);
        }
        // 减少负载
        void DecreaseLoad(){
            _load->fetch_sub(1, std::memory_order_relaxed);
        }
        void ResetLoad(){
            (*_load) = 0;
        }
        // 当前负载
        uint64_t Load(){
            return *_load;
        }
    };

    class LoadBalance{
    private:
        vector<CompileMachine> _compile_machines;
        vector<int> _online_machines;
        vector<int> _offline_machines;
        mutex _mutex;

    private:
        bool LoadAllMachines(){
            ifstream in(service_machines_conf);

            if (!in.is_open()) {
                LOG(ERROR) << "Service machine config file not found!" << endl;
                return false;
            }

            string line;
            while(getline(in, line)){
                // 获取conf信息
                vector<string> machine;
                StringUtil::SplitString(line, &machine, ":");
                if(machine.size() != 2){
                    LOG(ERROR) << "conf spilt error" << endl;
                    return false;
                }
                // 将信息形成Machine对象
                // cout << machine[0] << machine[1] << endl;

                CompileMachine cm(machine[0], stoi(machine[1]));
                _online_machines.push_back(_compile_machines.size());
                _compile_machines.push_back(move(cm));
            }
            in.close();
            return true;
        }
    public:
        void OfflineMachine(int id){
            // 对_oneline_machines访问需要加锁
            std::lock_guard<std::mutex> lock(_mutex);
            for(auto it = _online_machines.begin(); it != _online_machines.end(); it++){
                if(*it == id){
                    _online_machines.erase(it);
                    _offline_machines.push_back(id);
                    // 离线后将负载清零
                    _compile_machines[id].ResetLoad();
                    break;
                }
            }            
        }
        void OnlineMachine(){
            //重启所有机器
            std::lock_guard<std::mutex> lock(_mutex);
            _online_machines.insert(_online_machines.end(), _offline_machines.begin(), _offline_machines.end());
            _offline_machines.clear();  
            LOG(INFO) << "reload all service" << endl;
        }

        bool SmartChoice(int* id/*输出型参数*/, CompileMachine** machine/*输出型参数*/){
            // 防止同时分配引发问题加锁
            std::lock_guard<std::mutex> lock(_mutex);
            // 均衡负载选择合适编译服务器和id返回
            if(_online_machines.size() == 0){
                LOG(FATAL) << "no online compile service" << endl;
                return false;
            }

            int min_id = _online_machines[0];
            // 没有赋值构造，也不能赋值构造，否则原子变量有问题，除了在LoadAllMachine中可以构造CompileMachine对象其他地方都不行
            CompileMachine* min = &_compile_machines[_online_machines[0]];
            for(int i = 1; i < _online_machines.size(); i++){
                CompileMachine* cur = &_compile_machines[_online_machines[i]];
                if(cur->Load() < min->Load()){
                    min = cur;
                    min_id = i;
                }
            }
            *id = min_id;
            *machine = min;
            return true;
        }

        void ShowMachines(){
            std::lock_guard<std::mutex> lock(_mutex);
            for(auto &id : _online_machines) {
                std::cout << id << " ";
            } 
            std::cout << std::endl;
            std::cout << "offline machine list: ";
            for(auto &id : _offline_machines) {
                std::cout << id << " ";
            } 
            std::cout << std::endl; 
        }
    public:
        LoadBalance(){
            // 加载所有编译服务器
            if(!LoadAllMachines()){
                LOG(ERROR) << "load all machine fail" << endl;
            }
            LOG(INFO) << "load all machine success" << endl;
        }
        ~LoadBalance(){}
    };


    class Control{
    private:
        Model _model;
        View _view;
        LoadBalance _load_balance;

    public:
        Control(){}
        ~Control(){}

        void RestartMachines(){
            _load_balance.OnlineMachine();
            // debug
            // _load_balance.ShowMachines();

        }

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
        void JudgeQuestion(const std::string number, const std::string in_json, std::string* out_json){
            /***********************
             * 输入:
             * number: 判断的题号
             * in_json: 用户发送的题目json
             * 
             * 输出:
             * out_json: 返回的判题结果json
             * 
             * 参数:abort
             * in_json:{"code": "class Solution...", "input": ""}
             ***********************/
            // 根据number获取对应的题目信息
            Question que_info;
            if(!_model.GetOneQuestion(number, &que_info)){
                LOG(ERROR) << "get judge question info error" << endl;
            }

            // 反序列化json
            Json::CharReaderBuilder reader;
            Json::Value json_value;
            std::string errors;
            std::istringstream jsonStream(in_json);
            if (!Json::parseFromStream(reader, jsonStream, &json_value, &errors))
            {
                LOG(ERROR) << "Judge JSON parsing error: " << errors;
                *out_json = R"({"error": "Invalid JSON format"})";
                return;
            }
            // 拼接形成完整代码, 完整的json请求
            Json::Value compile_value;
            std::string code = json_value["code"].asString();
            code += que_info.tail;

            compile_value["code"] = code;
            compile_value["input"] = json_value["input"].asString();
            compile_value["mem_limit"] = que_info.mem_limit;
            compile_value["cpu_limit"] = que_info.cpu_limit;
            Json::StreamWriterBuilder writer;
            // 禁止将中文转译为unicode
            writer.settings_["emitUTF8"] = true;
            std::string compile_json = Json::writeString(writer, compile_value);


            // 选择负载最低的主机
            while(true){
                int id;
                CompileMachine* machine;
                // 获得负载最低的服务id和对应编译服务器信息
                if(!_load_balance.SmartChoice(&id, &machine)){
                    LOG(FATAL) << "all compile server offline, use ^\\ to restart compile server" << endl;
                    break;
                }
                // 有了json，有了服务器，将信息发送带服务器完成编译
                httplib::Client cli(machine->GetIp(), machine->GetPort());
                // 使用该服务增加对应负载
                machine->IncreaseLoad();
                LOG(INFO) << machine->GetIp() << ":" <<  machine->GetPort() << " load: "<< machine->Load() << endl;

                // 发起http返回结果
                // 发送Post请求，发送json
                auto res = cli.Post("/compile_run", compile_json, "application/json; charset=utf-8");
                if(res){
                    if(res->status == 200){
                        // 完成并返回结果, 将结果赋给out_json
                        *out_json = res->body;
                        // 请求完成负载降低
                        machine->DecreaseLoad();
                        LOG(INFO) << "Get compile result success" << endl;
                        break;
                    }
                    // 得到结果但是不是预期结果，涉及到其他退出码的
                    machine->DecreaseLoad();
                    continue;
                }
                else{
                    // 没收到请求，当前服务器没能完成编译工作，表示服务器出问题，将其加入到离线服务器列表中，选择其他服务器
                    _load_balance.OfflineMachine(id);
                    LOG(ERROR) << "service[" << id << "] already offline" << endl;

                    // 用于测试
                    _load_balance.ShowMachines();

                }
            }
            return ;

        }
        
    };



};