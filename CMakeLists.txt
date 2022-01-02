cmake_minimum_required(VERSION 3.5)
project(Lift_Imitate)

set(SOURCES
    src/main.cpp
    src/datatype.cpp
    src/control.cpp
    src/class.cpp
)

add_executable(Lift_Imitate ${SOURCES})

target_include_directories(Lift_Imitate
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
