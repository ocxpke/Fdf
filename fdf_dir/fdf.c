/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:52:33 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/15 18:16:21 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_coordinates	**dis_points;
	t_map_info		*map_info;
	t_window		*win_info;
	t_fdf_data		fdf_data;

	if (argc != 2)
		return (-1);
	map_info = init_map_info(argv[1]);
	win_info = init_window_components();
	init_model_values(win_info, map_info);
	dis_points = init_points_matrix(map_info);
	calculate_main_projection(win_info, map_info, dis_points);
	display_main_projection(win_info, map_info, dis_points);
	mlx_image_to_window(win_info->window, win_info->img, win_info->init_width
		* 0.025, win_info->init_heigth * 0.005);
	fdf_data.dis_points = dis_points;
	fdf_data.map_info = map_info;
	fdf_data.win_info = win_info;
	mlx_key_hook(win_info->window, &keyboard_hooks, &fdf_data);
	mlx_scroll_hook(win_info->window, &zoom_hook, &fdf_data);
	mlx_loop(win_info->window);
}
