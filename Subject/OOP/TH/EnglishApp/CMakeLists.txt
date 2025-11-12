cmake_minimum_required(VERSION 3.15)
project(EnglishApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Sql Widgets)
find_package(SQLite3 REQUIRED)

find_package(pybind11 REQUIRED)

include_directories(
    include
    ${SQLite3_INCLUDE_DIRS}
)

file(GLOB SRC_FILES
    src/*.cpp
)

pybind11_add_module(englishapp SHARED
    ${SRC_FILES}
)

target_link_libraries(englishapp
    PRIVATE
        Qt6::Core
        Qt6::Sql
        Qt6::Widgets
        SQLite::SQLite3
)
