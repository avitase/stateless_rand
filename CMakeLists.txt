cmake_minimum_required(VERSION 3.12)
project(statelessrnd)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address \
                                        -fsanitize=leak \
                                        -fsanitize=undefined")

include_directories(include)
include_directories(lib SYSTEM)
add_executable(runAllUnitTests test/main.cxx test/test_stateless_rand.cpp)
