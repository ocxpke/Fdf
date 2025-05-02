NAME	:= fdf
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= ../MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= ./libft/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	:= fdf.c\
	bresenham_alg.c\
	manage_window.c\
	manage_map_info.c\
	manage_display_points.c\
	isometric_projection.c\
	aux_bresenham.c\
	init_model_values.c\
	recalculate_projection.c\
	manage_zoom.c\
	mlx_hooks.c\
	model_values.c\
	manage_model_position.c\
	reset_components.c\
	manage_rotation.c\
	rotation_in_x.c\
	rotation_in_y.c\
	rotation_in_z.c\
	automatic_rotation.c\
	manage_first_angle_projection.c\
	first_angle_views.c

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

re: clean all

run: all
	XDG_SESSION_TYPE=x11 DISPLAY=:0 ./fdf ../test_maps/pira.fdf

.PHONY: all, clean, fclean, re, libmlx, libft
