NAME	:= fdf
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= ../MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= ./libft/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	:= fdf.c\
	swap_map.c\
	mlx_hooks.c\
	manage_zoom.c\
	model_values.c\
	bresenham_alg.c\
	manage_window.c\
	aux_bresenham.c\
	rotation_in_x.c\
	rotation_in_y.c\
	rotation_in_z.c\
	manage_rotation.c\
	manage_map_info.c\
	reset_components.c\
	first_angle_views.c\
	init_model_values.c\
	automatic_rotation.c\
	isometric_projection.c\
	manage_model_position.c\
	manage_display_points.c\
	recalculate_projection.c\
	manage_first_angle_projection.c

OBJS:= ${SRCS:.c=.o}

LIBFT_DIR = -L./libft -llibft

all: libmlx libft $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	make -C ./libft

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	make -C ./libft fclean

fclean: clean
	@rm -rf $(NAME)

re: fclean all

run: all
	XDG_SESSION_TYPE=x11 DISPLAY=:0 ./fdf ../test_maps/42.fdf

.PHONY: all, clean, fclean, re, libmlx, libft
