/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:51:40 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/16 19:42:30 by jose-ara         ###   ########.fr       */
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

# define DEFAULT_COLOR 0x00FFFFFF
# define MINIMUM_SPACING 3
# define BACKGROUND_COLOR 0
# define USER_SPEED 50
# define ZOOM_CHANGE 0.01
# define ZOOM_MAX 7
# define ZOOM_MIN 0.1
# define PI_VALUE 3.141592

typedef struct s_window
{
	mlx_t			*window;
	mlx_image_t		*img;
	int				init_width;
	int				init_heigth;
}					t_window;

typedef struct s_model_values
{
	int				max_x;
	int				min_x;
	int				max_y;
	int				min_y;
	int				offset_x;
	int				offset_y;
	int				center_x_axis;
	int				center_y_axis;
	int				min_z;
	int				max_z;
	int				spacing;
	int				user_x_pos;
	int				user_y_pos;
	double			zoom;
	double			rotation_angle_x;
	double			rotation_angle_y;
	double			rotation_angle_z;
	int				rotation_axis;
	bool			auto_rot;
}					t_model_values;

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
	double			x_p;
	double			y_p;
	double			z_p;
	struct s_vector	*next;
}					t_vector;

typedef struct s_map_info
{
	int				x_length;
	int				y_length;
	int				highest_point;
	int				lowest_point;
	t_vector		*vector_list;
	t_model_values	*model_values;
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

void				draw_line(mlx_image_t *img, t_model_values *model_values,
						t_coordinates v0, t_coordinates v1);

t_map_info			*init_map_info(char *file_in);
void				print_map_info(t_map_info *map_info);

t_window			*init_window_components(void);
void				keyboard_hooks(mlx_key_data_t keydata, void *param);
void				zoom_hook(double xdelta, double ydelta, void *param);

t_coordinates		**init_points_matrix(t_map_info *map_info);
t_coordinates		**free_back_coord(t_coordinates **points_matrix);

void				display_main_projection(t_window *win_info,
						t_map_info *map_info, t_coordinates **p_matrix);

void				set_colors(t_model_values *model_values, t_bresenham *data);

int					calculate_spacing(t_window *win_info, t_map_info *map_info);

int					point_in_field(int x, int y, mlx_image_t *img);

void				init_model_values(t_window *win_info, t_map_info *map_info);

void				change_zoom_value(t_fdf_data *fdf_data, int mode);

void				set_offsets(mlx_image_t *img, t_model_values *model_values);
void				redraw_projection(t_fdf_data *fdf_data);

void				calculate_main_projection(t_window *win_info,
						t_map_info *map_info, t_coordinates **p_matrix);

void				set_model_values(t_model_values *model_values, int x,
						int y);
void				absolute_min_values(t_model_values *model_values);
void				center_model(t_window *win_info,
						t_model_values *model_values);
void				reset_model_values(t_model_values *model_values);

void				set_x_axis_position(t_fdf_data *fdf_data, int mode);
void				set_y_axis_position(t_fdf_data *fdf_data, int mode);

void				reset_model_components(t_vector *vector);
void				reset_user_values(t_fdf_data *fdf_data);
void				reset_user_view(t_window *win_info);

void				check_axis_reset_values(t_fdf_data *fdf_data,
						t_model_values *model_values, int axis);
void				calculate_display_rotation(t_fdf_data *fdf_data, int axis);
double				deg_to_rad(double degrees);

double				rotation_on_x_value_y(t_model_values *model_values, int y,
						int z);
double				rotation_on_x_value_z(t_model_values *model_values, int y,
						int z);
void				calculate_rotated_points_x(t_map_info *map_info);
void				rotate_model_x(t_fdf_data *fdf_data, int axis, int mode);

double				rotation_on_y_value_x(t_model_values *model_values, int x,
						int z);
double				rotation_on_y_value_z(t_model_values *model_values, int x,
						int z);
void				calculate_rotated_points_y(t_map_info *map_info);
void				rotate_model_y(t_fdf_data *fdf_data, int axis, int mode);

double				rotation_on_z_value_x(t_model_values *model_values, int x,
						int y);
double				rotation_on_z_value_y(t_model_values *model_values, int x,
						int y);
void				calculate_rotated_points_z(t_map_info *map_info);
void				rotate_model_z(t_fdf_data *fdf_data, int axis, int mode);

void				automatic_rotation(void *param);

#endif
