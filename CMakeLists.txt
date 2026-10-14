
cmake_minimum_required(VERSION 3.16)

project(untitled LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    PrintSupport
)

qt_add_executable(untitled
    main.cpp
    dialog.cpp
    dialog.h
)

target_link_libraries(untitled PRIVATE
    Qt6::Widgets
    Qt6::PrintSupport
)

if(MSVC)
    target_compile_options(untitled PRIVATE /utf-8)
endif()
