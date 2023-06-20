cmake_minimum_required(VERSION 3.0.2)
project(lsa)

find_package(Eigen3 3.4.0 REQUIRED NO_MODULE)

set(SRC
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/lsa.cpp
)

add_executable(lsa ${SRC})
target_link_libraries (lsa Eigen3::Eigen)
