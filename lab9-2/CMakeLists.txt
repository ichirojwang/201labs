cmake_minimum_required(VERSION 3.22)

project(Lab9 VERSION 1.0 DESCRIPTION "This is an example for the lab." LANGUAGES C)

set(CMAKE_BUILD_TYPE Debug)

# Note: ASan and TSan are incompatible

# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)
# --------- Task 3 ---------
# Enable the thread sanitizer
# add_compile_options(-fsanitize=thread)
# add_link_options(-fsanitize=thread)

include_directories(include)
add_executable(main src/main.c)
target_include_directories(main PRIVATE include)
