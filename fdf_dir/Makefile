NAME	:= fdf
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= ../MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= ./libft/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	:= fdf.c\
	manage_vectors.c\
	bresenham_alg.c\
	manage_map_info.c\
	projections_3d.c\
	manage_window.c\
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
