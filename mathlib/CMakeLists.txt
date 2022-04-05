# CMake最低版本要求
cmake_minimum_required(VERSION 2.8)

# 项目信息
project(cmake_demo)

# 查找当前目录下所有源文件
# 并将名称保存到DIR_SRCS变量
aux_source_directory(. DIR_LIB_SRCS)

# 指定生成目标
# 将$DIR_LIB_SRCS源文件编译生成静态库mathlib
add_library (mathlib "${DIR_LIB_SRCS}")

# bin安装信息
install(TARGETS mathlib DESTINATION bin)

# include安装信息
install (FILES "${PROJECT_SOURCE_DIR}/mathlib.h" DESTINATION include/mathlib)
