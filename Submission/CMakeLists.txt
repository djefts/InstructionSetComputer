cmake_minimum_required(VERSION 3.14)
project(InstructionSetComputer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

#add_executable(InstructionSetComputer
#        main.c
#        instruction_set.c
#        parsing_functions.c)
add_executable(InstructionSetComputer
        main_one_file.c)
