#需求的最低cmake程序版本
cmake_minimum_required(VERSION 3.12)
#本工程的名字
project(OpenGL)
#本工程支持的C++版本
set(CMAKE_CXX_STANDARD 17)

#在Cmake中使用全局预编译宏，来控制是否开启错误检查
add_definitions (-DDEBUG)

include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include)
link_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib)

add_subdirectory(wrapper)
add_subdirectory(application)
#将funs文件夹纳入到编译系统
#add_subdirectory(funcs)

#搜索所有的cpp，加入SRCS变量中
#aux_source_directory(. SRCS)
#本工程的所有cpp文件编译链接，生成exe
#add_executable(glStudy ${SRCS})
#将funcs.lib连接如softRender
#target_link_libraries(glStudy funcs)
add_executable(glStudy "main.cpp" "glad.c" "wrapper/checkError.h" "wrapper/checkError.cpp")

target_link_libraries(glStudy glfw3.lib wrapper app)