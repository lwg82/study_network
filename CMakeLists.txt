cmake_minimum_required(VERSION 2.8)

project(study-network)


# 包含通用头文件
include_directories("${CMAKE_SOURCE_DIR}/include")

enable_language(CXX)

# cmake .. -DCMAKE_BUILD_TYPE=Debug
# gcc
#set(CMAKE_C_FLAGS  "-g -Wall -O0 -Wextra -Wvla -Wno-unused-function -Werror-implicit-function-declaration -Wno-missing-braces -Wno-missing-field-initializers ${CMAKE_C_FLAGS} -std=gnu99 -fno-strict-aliasing")
# g++
#set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -Wvla -Wno-unused-function -Werror-implicit-function-declaration -Wno-missing-field-initializers ${CMAKE_CXX_FLAGS} -std=c++11  -fno-strict-aliasing")

# ---------------------------------------------------------------------------------------
# Set default build to Debug release 
# ---------------------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose Release or Debug" FORCE)
endif()

# ---------------------------------------------------------------------------------------
# Compiler config
# ---------------------------------------------------------------------------------------
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)




# ---------------------------------------------------------------------------------------
#  project
# ---------------------------------------------------------------------------------------
add_subdirectory(simple)
add_subdirectory(rtsp-client)

# cmake -DCMAKE_BUILD_TYPE=Debug ..  
