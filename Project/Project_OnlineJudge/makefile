# 目标目录
OUT_DIR = out
OJ_OUT = $(OUT_DIR)/oj_server
COMPILE_OUT = $(OUT_DIR)/compile_server

# 子模块目录
OJ_DIR = oj_server
COMPILE_DIR = compile_server

.PHONY: all clean release_oj release_compile release

# 1. 编译所有模块（只在源目录编译，不复制文件）
all:
	$(MAKE) -C $(OJ_DIR)
	$(MAKE) -C $(COMPILE_DIR)

# 2. 清理所有编译文件
clean:
	$(MAKE) -C $(OJ_DIR) clean
	$(MAKE) -C $(COMPILE_DIR) clean
	rm -rf $(OUT_DIR)

# 3. 发布 OJ 服务器（只拷贝可执行文件和运行时所需文件）
release_oj: all
	@echo "正在发布 Online Judge Server..."
	@mkdir -p $(OJ_OUT)/conf $(OJ_OUT)/root $(OJ_OUT)/template $(OJ_OUT)/questions
	@cp $(OJ_DIR)/oj_server $(OJ_OUT)/
	@cp -r $(OJ_DIR)/conf $(OJ_OUT)/
	@cp -r $(OJ_DIR)/root $(OJ_OUT)/
	@cp -r $(OJ_DIR)/template $(OJ_OUT)/
	@cp -r $(OJ_DIR)/questions $(OJ_OUT)/
	@cp README.md $(OJ_OUT)/
	@echo "OJ Server 发布完成，文件存放于 $(OJ_OUT)"

# 4. 发布编译服务器（只拷贝可执行文件）
release_compile: all
	@echo "正在发布 Compile Server..."
	@mkdir -p $(COMPILE_OUT)/temp
	@cp $(COMPILE_DIR)/compile_server $(COMPILE_OUT)/
	@cp -r $(COMPILE_DIR)/temp $(COMPILE_OUT)/
	@cp README.md $(COMPILE_OUT)/
	@echo "Compile Server 发布完成，文件存放于 $(COMPILE_OUT)"

# 5. 发布所有组件
release: release_oj release_compile
	@echo "所有服务发布完成，可分别部署 $(OJ_OUT) 和 $(COMPILE_OUT)"
