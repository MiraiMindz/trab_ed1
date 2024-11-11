# We will use the C99 Standard because it's the most compatible one.
# Set the minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and C standard version
project(lista_telefonica C)

# Set C Standard
set(CMAKE_C_STANDARD 89)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Force CMake to use Clang
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

add_compile_options(
    -O3 -ggdb -g -pg -march=native -std=c89
    -Wall -Wextra -Werror -Wshadow -Wformat -Wreturn-type -Wuninitialized
    -Wno-missing-braces -pedantic
    -fsanitize=address
)
# Source files
set(SOURCES src/main.c) 

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Link the necessary libraries
target_link_libraries(${PROJECT_NAME} asan)

