cmake_minimum_required(VERSION 4.1)
project(EDU_project C)

set(CMAKE_C_STANDARD 99)

add_executable(EDU main.c
        data.c
        data.h
        authentication.c
        authentication.h
        admin.c
        admin.h
        faculty.c
        faculty.h
        student.c
        student.h
        utilities.c
        utilities.h
        main.c
)
