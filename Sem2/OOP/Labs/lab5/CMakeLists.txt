cmake_minimum_required(VERSION 3.27)
project(LAB5_ULTIM_FINAL_BUN_OK C)

set(CMAKE_C_STANDARD 11)

add_executable(LAB5_ULTIM_FINAL_BUN_OK main.c
        medicament.c
        medicament.h
        MyList.c
        MyList.h
        customSort.c
        customSort.h
        farmacie_service.c
        farmacie_service.h
)
