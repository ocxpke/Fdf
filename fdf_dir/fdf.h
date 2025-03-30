/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:51:40 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/30 21:27:49 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "./libft/libft.h"
# include <GLFW/glfw3.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>

typedef struct s_window
{
	mlx_t			*window;
	mlx_image_t		*img;
	int32_t			init_width;
	int32_t			init_heigth;
}					t_window;

typedef struct s_coordenates
{
	int				x;
	int				y;
}					t_coordinates;

typedef struct s_vector
{
	int				x;
	int				y;
	int				z;
	struct s_vector	*next;
}					t_vector;

typedef struct s_map_info
{
	int				x_length;
	int				y_length;
	int				highest_point;
	int				lowest_point;
	int				x_offset;
	int				y_offset;
	t_vector		*vector_list;
}					t_map_info;

typedef struct s_bresenham
{
	int				x0;
	int				x1;
	int				y0;
	int				y1;
	int				delta_x;
	int				delta_y;
	int				point;
	int				decision_param;
	int				direction;
	int				oper1;
	int				oper2;
}					t_bresenham;

void				init_vectors(int fd, t_vector **vector_list);
int					add_vector(t_vector **vectors, int x, int y, int z);
void				free_vec_list(t_vector **vectors);
void				print_vec_list(t_vector *list);

void				draw_line(mlx_image_t *img, t_coordinates v0,
						t_coordinates v1);

t_map_info			*init_map_info(char *file_in);
void				print_map_info(t_map_info *map_info);

t_window			*init_window_components(void);
void				my_key_hook(mlx_key_data_t keydata, void *win_info);
void				zoom_hook(double xdelta, double ydelta, void *param);

t_coordinates		**init_points_matrix(t_map_info *map_info);
t_coordinates		**free_back_coord(t_coordinates **points_matrix);

void				display_main_projection(t_window *win_info,
						t_map_info *map_info, t_coordinates **p_matrix);

#endif
