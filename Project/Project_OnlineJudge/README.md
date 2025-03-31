# Raizeroko Code 项目 🚀

## 项目简介
Raizeroko Code项目是一个基于 C++ 开发的在线评测系统，包含两个主要模块：OJ (Online Judge) 服务器和代码编译服务器。OJ 服务器负责管理题目、用户提交和评测结果，而编译服务器负责安全地编译并执行用户提交的代码。该项目支持 MySQL 存储题目数据，并提供基于 HTTP 的交互接口，适用于分布式部署。✨

## 目录结构
```sh
.
├── common/              # 公共头文件
├── compile_server/      # 代码编译与执行服务
│   ├── compile_server  # 可执行文件
│   ├── compile_server.cc  # 服务器主程序
│   ├── compiler.hpp       # 编译器相关逻辑
│   ├── compile_run.hpp    # 编译运行模块
│   ├── runner.hpp         # 代码执行逻辑
│   ├── temp/              # 临时存放代码文件
├── oj_server/          # OJ 服务器
│   ├── oj_server       # 可执行文件
│   ├── oj_server.cc    # 服务器主程序
│   ├── oj_control.hpp  # 业务控制逻辑
│   ├── oj_model.hpp    # 数据模型
│   ├── oj_model_mysql.hpp # MySQL 相关
│   ├── oj_view.hpp     # 视图层
│   ├── conf/           # 配置文件
│   ├── root/           # Web 静态资源
│   ├── template/       # 页面模板
│   ├── questions/      # 题目数据
├── makefile            # 统一 Makefile
├── out/                # 发布目录
└── README.md           # 项目说明
```

## 编译项目 🛠️
在项目根目录运行：
```sh
make
```
这将在 `oj_server/` 和 `compile_server/` 目录下分别编译 `oj_server` 和 `compile_server` 可执行文件。

## 清理项目 🧹
```sh
make clean
```
删除所有编译生成的文件。

## 发布项目 📦
### 发布 OJ 服务器
```sh
make release_oj
```
生成 `out/oj_server/` 目录，并拷贝 `oj_server` 及相关文件。

### 发布编译服务器
```sh
make release_compile
```
生成 `out/compile_server/` 目录，并拷贝 `compile_server` 可执行文件。

### 发布完整项目
```sh
make release
```
同时发布 OJ 服务器和编译服务器。

## 运行 🏃‍♂️
在 `out/oj_server/` 目录下运行：
```sh
./oj_server
```
在 `out/compile_server/` 目录下运行：
```sh
./compile_server
```



