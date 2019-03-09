cmake_minimum_required(VERSION 3.13)
project(filler_viz C)      # project name

set(CMAKE_C_STANDARD 99)

add_compile_options(-Wall -Wextra) # flags
find_library(OPEN_GL OpenGl)
find_library(APP_KIT AppKit)
include_directories(./libft/includes)  # directory with headers
link_directories(/usr/local/lib ./libft)
link_libraries(mlx)
FILE(GLOB LIBFT_SRCS ./libft/*.c ./libft/*/*.c)  # ADD LIBFT as sources

add_executable(filler_viz ${LIBFT_SRCS} srcs/main.c) # all c-files here
target_link_libraries(filler_viz ${OPEN_GL} ${APP_KIT})  # LINK libraries
