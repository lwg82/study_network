cmake_minimum_required(VERSION 2.8)

project(study-network)

# gcc ∂®“Â
set(CMAKE_C_FLAGS "-g -Wall -O0 -Wextra -Wvla -Wno-unused-function -Werror-implicit-function-declaration -Wno-missing-braces -Wno-missing-field-initializers ${CMAKE_C_FLAGS} -std=gnu99 -fno-strict-aliasing")


add_subdirectory(simple)

# cmake -DCMAKE_BUILD_TYPE=Debug ..  