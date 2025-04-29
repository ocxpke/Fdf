/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:51:40 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/30 01:47:39 by jose-ara         ###   ########.fr       */
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
# define MAX_ROTATION 360
# define MIN_ROTATION 0
# define JUMP_ROTATION 2

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
void				init_map_info(char *file_in, t_map_info *map_info);
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
void				init_window_components(char *argv, t_window *win_info);

/**		________________________________
 *		|
 *		|	INIT_MODEL_VALUES.C FILE
 *		|_______________________________
 */

/**
 * @brief	Allocates and initialises all components needed to dispaly our
 * map
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
 * @brief	Allocates meomry for our matrix of points, values are not
 * setted.
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

/**		________________________________
 *		|
 *		|	BRESENHAM_ALG.C FILE
 *		|_______________________________
 */

/**
 * @brief	Draws a pixel line using mlx_put_pixel from v0 to v1.
 *
 * @param img	The image where we are going to draw pixels
 * @param model_values	Model characteristics
 * @param v0	The first point of the line
 * @param v1	The last point of the line
 *
 * @return	Void
 */
void				draw_line(mlx_image_t *img, t_model_values *model_values,
						t_coordinates v0, t_coordinates v1);

/**		________________________________
 *		|
 *		|	AUX_BRESENHAM.C FILE
 *		|_______________________________
 */

/**
 * @brief	Here we initialize the content of the t_bresenham struct
 *
 * @param data	The struct we will initialize
 * @param model_values	Model characteristics
 * @param v0	The first point of the line
 * @param v1	The last point of the line
 *
 * @return	Void
 */
void				set_bresenham(t_bresenham *data,
						t_model_values *model_values, t_coordinates v0,
						t_coordinates v1);
/**
 * @brief	We set the color depending on the relative height of
 * the point between v0 and v1
 *
 * @param model_values	Model characteristics
 * @param data	The struct with all the data for bresenham_alg
 *
 * @return	Void
 */
void				set_colors(t_model_values *model_values, t_bresenham *data);
/**
 * @brief	Checks if the point x and y value are in range with the image
 *
 * @param x	The x value
 * @param y	The y value
 * @param img	The image struct that contains the width and height
 *
 * @return		0 if it's not in range, 1 if it's in range.
 */
int					point_in_field(int x, int y, mlx_image_t *img);

/**		________________________________
 *		|
 *		|	ISOMETRIC_PROJECTION.C FILE
 *		|_______________________________
 */

/**
 * @brief	Roam the p_matrix and set all the necesary values for p_matrix.x
 * and p_matrix.y to be displayed
 *
 * @param win_info	Struct that holds all the window information
 * @param map_info	Struct that holds all the map information needed
 * @param p_matrix Matrix containing all the points to be displayed
 *
 * @return	Void
 */
void				calculate_main_projection(t_window *win_info,
						t_map_info *map_info, t_coordinates **p_matrix);
/**
 * @brief	Draw line by connecting each point with the next one for each
 * row and column
 *
 * @param win_info	Struct that holds all the window information
 * @param map_info	Struct that holds all the map information needed
 * @param p_matrix Matrix containing all the points to be displayed
 *
 * @return	Void
 */
void				display_main_projection(t_window *win_info,
						t_map_info *map_info, t_coordinates **p_matrix);
/**
 * @brief	We calculate the minimun spacing that fits for the window
 *
 * @param win_info	Struct that holds all the window information
 * @param map_info	Struct that holds all the map information needed
 *
 * @return	Minimum MIN_SPACING, else the spacing calculated
 */
int					calculate_spacing(t_window *win_info, t_map_info *map_info);

/**		________________________________
 *		|
 *		|	RECALCULATE_PROJECTION.C FILE
 *		|_______________________________
 */

/**
 * @brief	Here we set the offsets of the model to be centered on screen
 *
 * @param img	The mlx image strcut containing the width and height.
 * @param model_values  Contains all the data needed for representing the model
 *
 * @return	Void
 */
void				set_offsets(mlx_image_t *img, t_model_values *model_values);
/**
 * @brief	We reset the model_values and recaculate everythin again (Use
 * this for reset)
 *
 * @param fdf_data  All the data of the FDF needed (WRAPPER)
 *
 * @return	Void
 */
void				redraw_projection(t_fdf_data *fdf_data);

/**		________________________________
 *		|
 *		| MODEL_VALUES.C FILE
 *		|_______________________________
 */

/**
 * @brief Resets to 0 max and min values, offsets (x & y), and the values used
 * for centering the model on both axis.
 *
 * @param model_values  Struct that contains all the information related to the
 * model
 *
 * @return	Void
 */
void				reset_model_values(t_model_values *model_values);
/**
 * @brief Compares the new X and Y values to check if the are new minimum or
 * maximum values.
 *
 * @param model_values  Struct that contains all the information related to the
 * model.
 * @param x The new X value.
 * @param y The new Y value.
 *
 * @return	Void
 */
void				set_model_values(t_model_values *model_values, int x,
						int y);
/**
 * @brief Sets the min value for x and y into positive values.
 *
 * @param model_values  Struct that contains all the information related to the
 * model
 *
 * @return	Void
 */
void				absolute_min_values(t_model_values *model_values);
/**
 * @brief Centers the model on case of being the model bigger than the window in
 * which is displayed.
 *
 * @param win_info  Struct that contains all the information of the window.
 * @param model_values  Struct that contains all the information related to the
 * model.
 *
 * @return	Void
 */
void				center_model(t_window *win_info,
						t_model_values *model_values);

/**		________________________________
 *		|
 *		| MLX_HOOKS.C FILE
 *		|_______________________________
 */

/**
 * @brief	Defines all events that can happen related with keyboard
 * inputs.
 *
 * @param keydata MLX structure that contains all the information needed for the
 * keyboard event.
 * @param param The fdf struct (WRAPPER) that will be cast later.
 *
 * @return	Void
 */
void				keyboard_hooks(mlx_key_data_t keydata, void *param);
/**
 * @brief	Defines all events that can happen related with mouse scrolls
 * inputs.
 *
 * @param xdelta Data from mouse horizontal scroll (left & right).
 * @param ydelta Data from mouse vertical scroll (up & down).
 * @param param The fdf struct (WRAPPER) that will be cast later.
 *
 * @return	Void
 */
void				zoom_hook(double xdelta, double ydelta, void *param);

/**		________________________________
 *		|
 *		| RESET_COMPONENTS.C FILE
 *		|_______________________________
 */

/**
 * @brief	Sets all X, Y, Z prime to the original value.
 *
 * @param vector	Pointer to the head of the vector list.
 *
 * @return	Void
 */
void				reset_model_components(t_vector *vector);
/**
 * @brief	Sets all the fdf data to the first frame of FDF,
 * the first projection. Then cleans window and draws the first projection.
 *
 * @param fdf_data	All the data used in FDF (WRAPPER)
 *
 * @return	Void
 */
void				reset_user_values(t_fdf_data *fdf_data);
/**
 * @brief	Cleans the window to an default color
 *
 * @param win_info	Conatins all the information of the window components.
 *
 * @return	Void
 */
void				reset_user_view(t_window *win_info);

/**		________________________________
 *		|
 *		| MANAGE_MODEL_POSITION.C FILE
 *		|_______________________________
 */

/**
 * @brief	Sets the model position on the X (Horizontal) axis
 * depeding on user input data.
 *
 * @param fdf_data	All the data used in FDF (WRAPPER)
 * @param mode	If 0 the model moves up; if 1 moves down
 *
 * @return	Void
 */
void				set_x_axis_position(t_fdf_data *fdf_data, int mode);
/**
 * @brief	Sets the model position on the Y (Vertical) axis
 * depeding on user input data.
 *
 * @param fdf_data	All the data used in FDF (WRAPPER)
 * @param mode	If 0 the model moves to the left; if 1 to the right
 *
 * @return	Void
 */
void				set_y_axis_position(t_fdf_data *fdf_data, int mode);

/**		________________________________
 *		|
 *		| MANAGE_ZOOM.C FILE
 *		|_______________________________
 */

/**
 * @brief	Sets the model dimesion depeding on user input data.
 *
 * @param fdf_data	All the data used in FDF (WRAPPER)
 * @param mode	If 0 zoom out, model smaller; if 1 zoom in, model bigger
 *
 * @return	Void
 */
void				change_zoom_value(t_fdf_data *fdf_data, int mode);

/**		________________________________
 *		|
 *		| MANAGE_ROTATION.C FILE
 *		|_______________________________
 */

/**
 * @brief	Transforms the angle value into his radian equivalent
 *
 * @param degree	The angle to transform
 *
 * @return	The radian value.
 */
double				deg_to_rad(double degrees);
/**
 * @brief	Checks if the rotation axis has been changed,
 * on that case resets the view and roation angles.
 *
 * @param fdf_data	All the data used in FDF (WRAPPER)
 * @param model_value	Struct that contains all the information related to the
 * model.
 * @param axis	0 => X axis, 1 => Y axis, 2 => Z axis
 *
 * @return	Void
 */
void				check_axis_reset_values(t_fdf_data *fdf_data,
						t_model_values *model_values, int axis);
/**
 * @brief	Calculate the value of rotating with the new angle value
 * on the slected axis, the calculates and display.
 *
 * @param fdf_data	All the data used in FDF (WRAPPER)
 * @param axis	0 => X axis, 1 => Y axis, 2 => Z axis
 *
 * @return	Void
 */
void				calculate_display_rotation(t_fdf_data *fdf_data, int axis);

/**		________________________________
 *		|
 *		| ROTATION_IN_X.C FILE
 *		|_______________________________
 */

/**
 * @brief	Calculates the Y prime components on the rotation of the X axis
 *
 * @param model_value	Struct that contains all the information related to the
 * model.
 * @param y	The original Y value
 * @param z	The original Z value
 *
 * @return	The value of Y prime
 */
double				rotation_on_x_value_y(t_model_values *model_values, int y,
						int z);
/**
 * @brief	Calculates the Z prime components on the rotation of the X axis
 *
 * @param model_value	Struct that contains all the information related to the
 * model.
 * @param y	The original Y value
 * @param z	The original Z value
 *
 * @return	The value of Z prime
 */
double				rotation_on_x_value_z(t_model_values *model_values, int y,
						int z);
/**
 * @brief	Iterates the list calculating the new values of Y and Z prime
 * on the rotation of the X axis
 *
 * @param map_info	Struct that holds all the map information needed
 *
 * @return	Void
 */
void				calculate_rotated_points_x(t_map_info *map_info);
/**
 * @brief	Checks if the axis of rotation has changes and rotates on
 * the X axis depending on the new value.
 *
 * @param fdf_data	All the data used in FDF (WRAPPER)
 * @param axis	0 => X axis, 1 => Y axis, 2 => Z axis
 * @param mode	If 0 rotates anticlockwise; if 1 rotates clockwise
 *
 * @return	Void
 */
void				rotate_model_x(t_fdf_data *fdf_data, int axis, int mode);

/**		________________________________
 *		|
 *		| ROTATION_IN_Y.C FILE
 *		|_______________________________
 */

/**
 * @brief	Calculates the X prime components on the rotation of the Y axis
 *
 * @param model_value	Struct that contains all the information related to the
 * model.
 * @param x	The original X value
 * @param z	The original Z value
 *
 * @return	The value of X prime
 */
double				rotation_on_y_value_x(t_model_values *model_values, int x,
						int z);
/**
 * @brief	Calculates the Z prime components on the rotation of the Y axis
 *
 * @param model_value	Struct that contains all the information related to the
 * model.
 * @param x	The original X value
 * @param z	The original Z value
 *
 * @return	The value of Z prime
 */
double				rotation_on_y_value_z(t_model_values *model_values, int x,
						int z);
/**
 * @brief	Iterates the list calculating the new values of X and Z prime
 * on the rotation of the Y axis
 *
 * @param map_info	Struct that holds all the map information needed
 *
 * @return	Void
 */
void				calculate_rotated_points_y(t_map_info *map_info);
/**
 * @brief	Checks if the axis of rotation has changes and rotates on
 * the Y axis depending on the new value.
 *
 * @param fdf_data	All the data used in FDF (WRAPPER)
 * @param axis	0 => X axis, 1 => Y axis, 2 => Z axis
 * @param mode	If 0 rotates anticlockwise; if 1 rotates clockwise
 *
 * @return	Void
 */
void				rotate_model_y(t_fdf_data *fdf_data, int axis, int mode);

/**		________________________________
 *		|
 *		| ROTATION_IN_Z.C FILE
 *		|_______________________________
 */

/**
 * @brief	Calculates the X prime components on the rotation of the Z axis
 *
 * @param model_value	Struct that contains all the information related to the
 * model.
 * @param x	The original X value
 * @param y	The original Y value
 *
 * @return	The value of X prime
 */
double				rotation_on_z_value_x(t_model_values *model_values, int x,
						int y);
/**
 * @brief	Calculates the Y prime components on the rotation of the Z axis
 *
 * @param model_value	Struct that contains all the information related to the
 * model.
 * @param x	The original X value
 * @param y	The original Y value
 *
 * @return	The value of Y prime
 */
double				rotation_on_z_value_y(t_model_values *model_values, int x,
						int y);
/**
 * @brief	Iterates the list calculating the new values of X and Y prime
 * on the rotation of the Z axis
 *
 * @param map_info	Struct that holds all the map information needed
 *
 * @return	Void
 */
void				calculate_rotated_points_z(t_map_info *map_info);
/**
 * @brief	Checks if the axis of rotation has changes and rotates on
 * the Z axis depending on the new value.
 *
 * @param fdf_data	All the data used in FDF (WRAPPER)
 * @param axis	0 => X axis, 1 => Y axis, 2 => Z axis
 * @param mode	If 0 rotates anticlockwise; if 1 rotates clockwise
 *
 * @return	Void
 */
void				rotate_model_z(t_fdf_data *fdf_data, int axis, int mode);

/**		________________________________
 *		|
 *		| AUTOMATIC_ROTATION.C FILE
 *		|_______________________________
 */

/**
 * @brief	Only selects the axis to rotate depending on the value
 * the user has selected
 *
 * @param param The fdf struct (WRAPPER) that will be cast later.
 *
 * @return	Void
 */
void				automatic_rotation(void *param);

/**		_______________________________________
 *		|
 *		| MANAGE_FIRST_ANGLE_PROJECTION.C FILE
 *		|______________________________________
 */

/**
 * @brief	Calculate a spacing tha fits into one quartet for the model length.
 *
 * @param img	The mlx image where the projection is going to be drawn.
 * @param sum	The length of the model.
 *
 * @return	The spacing selected for the view.
 */
double				spacing_first_angle(mlx_image_t *img, double sum);
/**
 * @brief	Sets the origin point for the views of the first angle projection,
 * depending on the quadrant selected
 *
 * @param img	The mlx image where the projection is going to be drawn.
 * @param model_values	Struct that contains all the information related to the
 * model.
 * @param quadrant	Quadrant selected to set the origin
 *
 * @return	Void
 */
void				center_view_in_quadrant(mlx_image_t *img,
						t_model_values *model_values, int quadrant);
/**
 * @brief	Cleans, divide the screen and project the views of the
 * first angle projection.
 *
 * @param fdf_data	All the data used in FDF (WRAPPER)
 *
 * @return	Void
 */
void				project_first_angle_view(t_fdf_data *fdf_data);

/**		_______________________________________
 *		|
 *		| FIRST_ANGLE_VIEWS.C FILE
 *		|______________________________________
 */

/**
 * @brief	Draws the plant view of the first angle projection, consists
 * of the X and Y coordinates
 *
 * @param win_info	Struct that holds all the window information
 * @param map_info	Struct that holds all the map information needed
 * @param p_matrix Matrix containing all the points to be displayed
 *
 * @return	Void
 */
void				draw_plant_view(t_window *win_info, t_map_info *map_info,
						t_coordinates **p_matrix);
/**
 * @brief	Draws the profile view of the first angle projection, consists
 * of the Y and Z coordinates
 *
 * @param win_info	Struct that holds all the window information
 * @param map_info	Struct that holds all the map information needed
 * @param p_matrix Matrix containing all the points to be displayed
 *
 * @return	Void
 */
void				draw_profile_view(t_window *win_info, t_map_info *map_info,
						t_coordinates **p_matrix);
/**
 * @brief	Draws the raised view of the first angle projection, consists
 * of the X and Z coordinates
 *
 * @param win_info	Struct that holds all the window information
 * @param map_info	Struct that holds all the map information needed
 * @param p_matrix Matrix containing all the points to be displayed
 *
 * @return	Void
 */
void				draw_raised_view(t_window *win_info, t_map_info *map_info,
						t_coordinates **p_matrix);

#endif
