cmake_minimum_required(VERSION 3.22)

project(NetworkExcersise VERSION 1.0 DESCRIPTION "This is for lab10." LANGUAGES C)

add_executable(server server.c)
add_executable(client client.c)