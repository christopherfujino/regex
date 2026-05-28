cmake_minimum_required(VERSION 3.31)
set(CMAKE_C_COMPILER clang)
project(KenGrep LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(chris-grep
  grep-chris.c)

target_compile_options(chris-grep PRIVATE
  -Wall -Werror -Wpedantic -Wextra)
