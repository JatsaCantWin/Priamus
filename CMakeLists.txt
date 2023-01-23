cmake_minimum_required(VERSION 3.0)
project(Priamus)

set(CMAKE_CXX_STANDARD 14)

add_library(DatabaseModule
        libs/sqlite3/sqlite3.c
        /usr/include/cassandra.h
        /usr/include/libmongoc-1.0/mongoc/mongoc.h
        /usr/include/libbson-1.0/bson/bson.h
)

include_directories("/usr/include/libmongoc-1.0")
include_directories("/usr/include/libbson-1.0")

add_executable(Priamus src/main.cpp src/DatabaseConnectors/SQLiteConnector.cpp src/DatabaseConnectors/SQLiteConnector.h src/DatabaseConnectors/CassandraConnector.cpp src/DatabaseConnectors/CassandraConnector.h src/DatabaseConnectors/MongoDBConnector.cpp src/DatabaseConnectors/MongoDBConnector.h src/DataContainers/Cell.cpp src/DataContainers/Cell.h src/DataContainers/Table.cpp src/DataContainers/Table.h src/DataContainers/Column.cpp src/DataContainers/Column.h)

target_link_libraries(Priamus DatabaseModule cassandra mongoc-1.0 bson-1.0)