SRCS =	main.c auxiliary_functions_first.c auxiliary_functions_second.c initialization_and_error_functions.c \
		parsheader_main.c parsheader_range_ceiling_floor.c parsheader_texture_first.c parsheader_texture_second.c \
		parsmap_first.c parsmap_second.c raycasting.c draw_map.c new_norm_zero.c new_norm_first.c new_norm_second.c \
		new_norm_three.c new_norm_four.c new_norm_five.c new_norm_six.c new_norm_seven.c

CC = gcc
FLAGS = -Wall -Wextra -Werror -g -O2
MLXLIB = minilibx_mms_20200219
MLX = -framework Appkit
NAME = cub3D
OBJC = ${SRCS:.c=.o}

.c.o:
		${CC} ${FLAGS} -c $<
all: $(NAME)


$(NAME): ${OBJC} Makefile cub.h
		make -C $(MLXLIB)
		mv ./${MLXLIB}/libmlx.dylib libmlx.dylib
		${CC} ${MLX} libmlx.dylib -o ${NAME} ${OBJC}

clean:
		make -C ./${MLXLIB}/ clean
		-rm -f libmlx.dylib
		-rm -f ${OBJC}

fclean: clean
		-rm -f ${NAME}
		-rm -f screenshot.bmp

re: fclean all

.PHONY: all clean fclean re
