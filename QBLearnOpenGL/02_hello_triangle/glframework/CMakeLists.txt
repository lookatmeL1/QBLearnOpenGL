#递归将本文件夹所有cpp放到funcs中
file(GLOB_RECURSE FW ./ *.cpp)

#将FUNS中所有cpp编译为funcs这个lib库
add_library(fw ${FW})