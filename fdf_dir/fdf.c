/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:52:33 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/25 21:28:13 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief	Sets the content of the fdf_data type, used for hooks.
 *
 * @param fdf_data	Variable to set all data of FDF
 * @param dis_points	The points to be displayed on scren
 * @param map_info	All the details of our map
 * @param win_info	All the details needed for our window management
 *
 * @return	Void
 */
static inline void	set_fdf_data(t_fdf_data *fdf_data,
		t_coordinates **dis_points, t_map_info *map_info, t_window *win_info)
{
	fdf_data->dis_points = dis_points;
	fdf_data->map_info = map_info;
	fdf_data->win_info = win_info;
}

/**
 * @brief	Reached the end of our program, we need to liberate everything
 *
 * @param fdf_data	Locataion of all the data used on FDF
 *
 * @return	Void
 */
static void	terminate_fdf(t_fdf_data *fdf_data)
{
	t_window	*win_info;

	win_info = fdf_data->win_info;
	free_back_coord(fdf_data->dis_points);
	free(fdf_data->map_info->model_values);
	free_vec_list(&fdf_data->map_info->vector_list);
	mlx_delete_image(win_info->window, win_info->img);
	mlx_delete_image(win_info->window, win_info->leyend_img);
	mlx_delete_texture(win_info->leyend_texture);
	mlx_terminate(win_info->window);
}

/**
 * @note Is important to first allocate the memory used for the map,
 * rather than allocating the memory for MLX
 */
int	main(int argc, char **argv)
{
	t_coordinates	**dis_points;
	t_map_info		map_info;
	t_window		win_info;
	t_fdf_data		fdf_data;

	if (argc != 2)
		return (-1);
	init_map_info(argv[1], &map_info);
	dis_points = init_points_matrix(&map_info);
	init_model_values(&map_info);
	init_window_components(argv[1], &win_info);
	calculate_main_projection(&win_info, &map_info, dis_points);
	display_main_projection(&win_info, &map_info, dis_points);
	set_fdf_data(&fdf_data, dis_points, &map_info, &win_info);
	mlx_key_hook(win_info.window, keyboard_hooks, &fdf_data);
	mlx_scroll_hook(win_info.window, zoom_hook, &fdf_data);
	mlx_loop_hook(win_info.window, automatic_rotation, &fdf_data);
	mlx_loop(win_info.window);
	terminate_fdf(&fdf_data);
	return (EXIT_SUCCESS);
}
