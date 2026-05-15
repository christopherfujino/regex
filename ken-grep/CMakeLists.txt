cmake_minimum_required(VERSION 3.31)
project(KenGrep)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(chris-grep
  grep-chris.c)

target_compile_options(chris-grep PRIVATE
  -Wall -Werror -Wpedantic -Wextra)
