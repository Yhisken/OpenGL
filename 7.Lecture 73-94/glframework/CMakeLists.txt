#递归将本文件夹所有cpp放到WRAPPER中
file(GLOB_RECURSE FW ./ *.cpp)
#将WRAPPER中所有cpp编译为wrapper这个lib库
add_library(fw ${FW})