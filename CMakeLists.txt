# CMake最低版本要求
cmake_minimum_required(VERSION 2.8)

# ------------------------------------------
# 项目信息
project(cmake_demo)

# 版本信息，在config.h.in中可以定义宏获取版本值
set (CMAKE_DEMO_VERSION_MAJOR 1)
set (CMAKE_DEMO_VERSION_MINOR 0)

# 可执行文件名
set (EXECUTABLE_NAME "cmake_demo")

# ------------------------------------------
# 开启debug模式，支持gdb调试
set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")

set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# ------------------------------------------
# 增加编译选项
# 加入一个配置头文件，用于处理CMake对源码的设置
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in" "${PROJECT_SOURCE_DIR}/config.h"
)

# -------------------------------------------
# 增加配置项
# 是否使用自带的mathlib库
option(USE_MY_MATHLIB "Use provided mathlib" ON)

if(USE_MY_MATHLIB)

include_directories("${PROJECT_SOURCE_DIR}")

add_subdirectory(mathlib)

set (EXTRA_LIBS ${EXTRA_LIBS} mathlib)

endif(USE_MY_MATHLIB)

# -------------------------------------------
# 增加环境检查
include(CheckSymbolExists)

# 检查系统是否存在 pow 函数
check_symbol_exists(pow "math.h" HAVE_POW)

# --------------------------------------------
# 查找当前目录下所有源文件
# 并将名称保存到DIR_SRCS变量
aux_source_directory(. DIR_SRCS)

# 添加mathlib编译子目录（放到编译选项中了）
#add_subdirectory(mathlib)

# 指定生成目标
# 将$DIR_SRCS源文件编译生成可执行文件cmake_demo
add_executable("${EXECUTABLE_NAME}" "${DIR_SRCS}")
#add_executable(cmake_demo main.cc)

# 添加链接库
# 可执行文件cmake_demo需要连接mathlib库
# target_link_libraries(cmake_demo mathlib)
target_link_libraries ("${EXECUTABLE_NAME}"  ${EXTRA_LIBS})

# ------------------------------------------------
# 安装信息
SET(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/build")

install(TARGETS "${EXECUTABLE_NAME}" DESTINATION bin)

install(FILES "${PROJECT_SOURCE_DIR}/config.h" DESTINATION include)

# -------------------------------------------------
# CTest测试

# 启用测试
enable_testing()

# 测试程序是否成功运行
add_test(test_run cmake_demo 1 add 2)

# 测试帮助信息是否正常提示
add_test(test_usage cmake_demo)

set_tests_properties(test_usage PROPERTIES PASS_REGULAR_EXPRESSION "Usage")
set_tests_properties(test_usage PROPERTIES PASS_REGULAR_EXPRESSION " x add y")
set_tests_properties(test_usage PROPERTIES PASS_REGULAR_EXPRESSION " x pow y")

# 测试加法
add_test(test_add_1_2 cmake_demo 1 add 2)

set_tests_properties(test_add_1_2 PROPERTIES PASS_REGULAR_EXPRESSION "1 add 2 is 3")

add_test(test_add_10_5 cmake_demo 10 add 5)

set_tests_properties(test_add_10_5 PROPERTIES PASS_REGULAR_EXPRESSION "10 add 5 is 15")

# 测试乘方，定义宏简化批量测试命令
macro(do_test arg1 arg2 arg3 result)
add_test("test_${arg2}_${arg1}_${arg3}" cmake_demo "${arg1}" "${arg2}" "${arg3}")
set_tests_properties("test_${arg2}_${arg1}_${arg3}" PROPERTIES PASS_REGULAR_EXPRESSION "${arg1} ${arg2} ${arg3} is ${result}")
endmacro(do_test)

# 使用上面的宏进行测试
do_test(2 pow 3 8)
do_test(3 pow 2 9)
do_test(3 add 2 5)

# ----------------------------------------------
# 构建一个 CPack 安装包
# 使用 cpack -C CPackConfig.cmake 命令构建二进制安装包
# 使用 cpack -C CPackSourceConfig.cmake 命令构建源码安装包

include (InstallRequiredSystemLibraries)

set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")

set (CPACK_PACKAGE_VERSION_MAJOR "${CMAKE_DEMO_VERSION_MAJOR}")

set (CPACK_PACKAGE_VERSION_MINOR "${CMAKE_DEMO_VERSION_MINOR}")

include (CPack)