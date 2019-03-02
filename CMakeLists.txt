cmake_minimum_required(VERSION 3.13)
project(filler C)

set(CMAKE_C_STANDARD 99)

add_compile_options(-Wall -Wextra)
include_directories(./libft/includes)
FILE(GLOB LIBFT_SRCS ./libft/*.c ./libft/*/*.c)

add_executable(filler ${LIBFT_SRCS} srcs/main.c srcs/ft_figure_parser.c srcs/ft_filler.h srcs/ft_map_parser.c srcs/ft_play_game.c srcs/ft_utils.c srcs/ft_set_fig.c)