#include <iostream>
#include <string>
#include "compiler.hpp"
#include "runner.hpp"

int main(){
    std::string test = "test";
    cs_compile::Compiler::Compile(test);
    cs_run::Runner::ExcuteCode(test);

    return 0;
}