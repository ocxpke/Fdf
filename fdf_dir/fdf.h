/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:51:40 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/11 21:46:40 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "./libft/libft.h"
# include <GLFW/glfw3.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <string.h>

typedef struct s_window
{
	mlx_t			*window;
	mlx_image_t		*img;
	int				init_width;
	int				init_heigth;
}					t_window;

typedef struct s_center_model
{
	int				max_x;
	int				min_x;
	int				max_y;
	int				min_y;
	int				center_x_axis;
	int				center_y_axis;
	int				min_z;
	int				max_z;
	int				spacing;
	double			zoom;
}					t_center_model;

typedef struct s_coordenates
{
	int				x;
	int				y;
	int				z;
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
	t_center_model	*model_values;
}					t_map_info;

typedef struct s_bresenham
{
	int				x0;
	int				x1;
	int				y0;
	int				y1;
	int				z0;
	int				z1;
	int				delta_x;
	int				delta_y;
	int				point;
	int				decision_param;
	int				direction;
	int				oper1;
	int				oper2;
	uint32_t		color_print;
}					t_bresenham;

typedef struct s_fdf_data
{
	t_coordinates	**dis_points;
	t_map_info		*map_info;
	t_window		*win_info;
}					t_fdf_data;

void				init_vectors(int fd, t_vector **vector_list);
int					add_vector(t_vector **vectors, int x, int y, int z);
void				free_vec_list(t_vector **vectors);
void				print_vec_list(t_vector *list);

void				draw_line(mlx_image_t *img, t_center_model *model_values,
						t_coordinates v0, t_coordinates v1);

t_map_info			*init_map_info(char *file_in);
void				print_map_info(t_map_info *map_info);

t_window			*init_window_components(void);
void				my_key_hook(mlx_key_data_t keydata, void *win_info);
void				zoom_hook(double xdelta, double ydelta, void *param);

t_coordinates		**init_points_matrix(t_map_info *map_info);
t_coordinates		**free_back_coord(t_coordinates **points_matrix);

void				display_main_projection(t_window *win_info,
						t_map_info *map_info, t_coordinates **p_matrix);

void				set_colors(t_center_model *model_values, t_bresenham *data);

int					point_in_field(int x, int y, mlx_image_t *img);

void				init_model_values(t_map_info *map_info);

void				change_zoom_value(t_fdf_data *fdf_data, int mode);

void				recalculate_projection(t_fdf_data *fdf_data);

void				calculate_main_projection(t_window *win_info,
						t_map_info *map_info, t_coordinates **p_matrix);

#endif
