/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:51:40 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/21 22:56:39 by jose-ara         ###   ########.fr       */
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
	mlx_image_t		*leyend_img;
	mlx_texture_t	*leyend_texture;
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
	bool			first_angle;
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

/**		________________________________
 *		|
 *		|	MANAGE_MAP_INFO.C FILE
 *		|_______________________________
 */
/**
 * @brief	Initialized an struct for allocating all information
 * needed to manage the map (.fdf)
 *
 * @param file_in The path of the file to be readed
 *
 * @return	The initialized struct
 */
t_map_info			*init_map_info(char *file_in);
/**
 * @brief	Prints the map information, used for debugging.
 *
 * @param map_info	All the details of our map
 *
 * @return	Void
 */
void				print_map_info(t_map_info *map_info);

/**		________________________________
 *		|
 *		|	MANAGE_VECTORS.C FILE
 *		|_______________________________
 */
/**
 * @brief	Initialises out linked list vector, reading each line and
 * splitting it to get every vector
 *
 * @param fd	FD of out map
 * @param vector_list	Linked list with all the vectors
 *
 * @return	Void
 */
void				init_vectors(int fd, t_vector **vector_list);
/**
 * @brief	Adds a vector at the end of the list, if vector_list == NULL
 * changes the head pointer
 *
 * @param vector_list	Linked list with all the vectors
 * @param x		X value of the vector
 * @param y		Y value of the vector
 * @param z		Z value of the vector
 *
 * @return	0 if everythin is OK, -1 if something went wrong
 */
int					add_vector(t_vector **vectors, int x, int y, int z);
/**
 * @brief	Liberates all the allocated memory of our vectors linked list
 *
 * @param vector_list	Linked list with all the vectors
 *
 * @return	Void
 */
void				free_vec_list(t_vector **vectors);
/**
 * @brief	Print's all the componentes of every node of our vectors list.
 *
 * @param vector_list	Linked list with all the vectors
 *
 * @return	Void
 */
void				print_vec_list(t_vector *list);

/**		________________________________
 *		|
 *		|	MANAGE_VECTORS.C FILE
 *		|_______________________________
 */
/**
 * @brief	Initialised a struct for allocating all trhe information,
 * needed to manage our window
 *
 * @param argv	File name passed through parameter
 *
 * @return	The initialised window struct
 */
t_window			*init_window_components(char *argv);

/**		________________________________
 *		|
 *		|	INIT_MODEL_VALUES.C FILE
 *		|_______________________________
 */
/**
 * @brief	Allocates and initialises all components needed to dispaly our map
 *
 * @param map_info	The struct with all our map information
 *
 * @return	Void
 */
void				init_model_values(t_map_info *map_info);


/**		________________________________
 *		|
 *		|	INIT_MODEL_VALUES.C FILE
 *		|_______________________________
 */
/**
 * @brief	Allocates meomry for our matrix of points, values are not setted.
 *
 * @param map_info	The struct with all our map information
 *
 * @return	The coordinates matrix struct or null
 */
t_coordinates		**init_points_matrix(t_map_info *map_info);
/**
 * @brief	Liberates all the allocated memory of the coordenates matrix
 *
 * @param points_matrix	Matrix with all corrdinates of the amp
 *
 * @return	Always null
 */
t_coordinates		**free_back_coord(t_coordinates **points_matrix);


void				draw_line(mlx_image_t *img, t_model_values *model_values,
						t_coordinates v0, t_coordinates v1);

void				keyboard_hooks(mlx_key_data_t keydata, void *param);
void				zoom_hook(double xdelta, double ydelta, void *param);


void				display_main_projection(t_window *win_info,
						t_map_info *map_info, t_coordinates **p_matrix);

void				set_bresenham(t_bresenham *data,
						t_model_values *model_values, t_coordinates v0,
						t_coordinates v1);
void				set_colors(t_model_values *model_values, t_bresenham *data);

int					calculate_spacing(t_window *win_info, t_map_info *map_info);

int					point_in_field(int x, int y, mlx_image_t *img);

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

void				project_first_angle_view(t_fdf_data *fdf_data);

double				spacing_first_angle(mlx_image_t *img, double sum);
void				center_view_in_quadrant(mlx_image_t *img,
						t_model_values *model_values, int quadrant);

void				draw_plant_view(t_window *win_info, t_map_info *map_info,
						t_coordinates **p_matrix);
void				draw_profile_view(t_window *win_info, t_map_info *map_info,
						t_coordinates **p_matrix);
void				draw_raised_view(t_window *win_info, t_map_info *map_info,
						t_coordinates **p_matrix);

#endif
