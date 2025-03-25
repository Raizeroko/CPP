#pragma once
#include<string>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

#include "../common/utils.hpp"
#include "../common/log.hpp"


// 只负责运行,不关心运行是否出错
namespace cs_run{
    using com_utils::PathUtil;
    using namespace com_log;

    class Runner{
    private:
        Runner(){}
        ~Runner(){}
    public:
        // 避免执行的程序运行超时或占用过多内存
        static void SetLimit(){
            // CPU运行时间限制
            struct rlimit cpu_rlim;
            cpu_rlim.rlim_max = RLIM_INFINITY;
            cpu_rlim.rlim_cur = 5;           // 5s
            int r_cpu = setrlimit(RLIMIT_CPU, &cpu_rlim);
            if(r_cpu < 0){
                LOG(ERROR) << "set run time error" << std::endl;
            }
            
            // 最大运行内存限制
            struct rlimit mem_rlim;
            mem_rlim.rlim_max = RLIM_INFINITY;
            mem_rlim.rlim_cur = 40*1024*1024; // 40MB
            int r_mem = setrlimit(RLIMIT_AS, &mem_rlim);
            if(r_mem < 0){
                LOG(ERROR) << "set run memory error" << std::endl;
            }

        }

        static int ExcuteCode(const std::string& file_name){
            int stdin_fd = open(PathUtil::Stdin(file_name).c_str(), O_CREAT | O_RDONLY, 0664);
            int stdout_fd = open(PathUtil::Stdout(file_name).c_str(), O_CREAT | O_WRONLY, 0664);
            int stderr_fd = open(PathUtil::Stderr(file_name).c_str(), O_CREAT | O_WRONLY, 0664);
            
            if(stdin_fd < 0 | stdout_fd < 0 | stderr_fd < 0){
                LOG(ERROR) << "open excute file error" << std::endl;
            }
            pid_t pid = fork();
            if(pid < 0){
                close(stdin_fd);
                close(stdout_fd);
                close(stderr_fd);
                LOG(ERROR) << "fork error" << std::endl;
                return -1;
            }
            else if(pid == 0){
                // 子进程
                int rdup_in = dup2(stdin_fd, 0);
                int rdup_out = dup2(stdout_fd, 1);
                int rdup_err = dup2(stderr_fd, 2);
                if(rdup_in < 0 | rdup_out < 0 | rdup_err < 0){
                    LOG(ERROR) << "dup error" << std::endl;
                }

                const char* execl_name = PathUtil::Target(file_name).c_str();
                SetLimit();
                int rexecl = execl(execl_name, execl_name, nullptr);
                if(rexecl < 0){
                    LOG(ERROR) << "execl error" << std::endl;
                }
                return -1;

            }
            else{
                close(stdin_fd);
                close(stdout_fd);
                close(stderr_fd);
                int status = 0;
                int rwp = waitpid(pid, &status, 0);
                if(rwp < 0){
                    LOG(ERROR) << "wait error"<< std::endl;
                }
                int child_signal = WTERMSIG(status);
                LOG(INFO) << "chlid exit, exit code:" << child_signal << std::endl;
                return child_signal;
            }
        }


    };
}

