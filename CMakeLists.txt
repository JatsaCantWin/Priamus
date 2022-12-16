cmake_minimum_required(VERSION 3.0)
project(Priamus)

set(CMAKE_CXX_STANDARD 14)

add_library(DatabaseModule
        libs/sqlite3/sqlite3.c
        /usr/include/cassandra.h
)

add_executable(Priamus src/main.cpp src/SQLiteConnector.cpp src/SQLiteConnector.h src/DataContainers/Table.cpp src/DataContainers/Table.h src/DataContainers/Column.cpp src/DataContainers/Column.h)

target_link_libraries(Priamus DatabaseModule cassandra)
