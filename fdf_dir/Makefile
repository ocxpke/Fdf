NAME	:= fdf
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= ../MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= ./libft/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	:= fdf.c\
	bresenham_alg.c\
	manage_window.c\
	manage_vectors.c\
	manage_map_info.c\
	manage_display_points.c\
	isometric_projection.c\
	aux_bresenham.c\
	init_model_values.c\
	recalculate_projection.c\
	manage_zoom.c\
	mlx_hooks.c

OBJS	:= ${SRCS:.c=.o}

LIBFT_DIR = -L./libft -llibft

all: libmlx libft $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	make -C ./libft

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	make -C ./libft fclean

fclean: clean
	@rm -rf $(NAME)

re: clean all

run: all
	MESA_SHADER_CACHE_DIR=$HOME/.cache/mesa XDG_SESSION_TYPE=x11 DISPLAY=:0 valgrind --leak-check=full --log-file=out.txt ./fdf ../test_maps/42.fdf

.PHONY: all, clean, fclean, re, libmlx, libft
