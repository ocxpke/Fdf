/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:52:33 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/18 03:02:41 by jose-ara         ###   ########.fr       */
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
	init_model_values(map_info);
	dis_points = init_points_matrix(map_info);
	calculate_main_projection(win_info, map_info, dis_points);
	display_main_projection(win_info, map_info, dis_points);
	mlx_image_to_window(win_info->window, win_info->img, win_info->init_width
		* 0.025, win_info->init_heigth * 0.005);
	// Guarrada 1 arreglar
	fdf_data.dis_points = dis_points;
	fdf_data.map_info = map_info;
	fdf_data.win_info = win_info;
	// el ampersand?
	// guarrada 2
	win_info->leyend_texture = mlx_load_png("./leyenda.png");
	win_info->leyend_img = mlx_texture_to_image(win_info->window,
			win_info->leyend_texture);
	mlx_image_to_window(win_info->window, win_info->leyend_img,
		win_info->init_width - 501, 0);
	mlx_put_string(win_info->window, argv[1], win_info->init_width - 475, 10);
	//
	mlx_key_hook(win_info->window, &keyboard_hooks, &fdf_data);
	mlx_scroll_hook(win_info->window, &zoom_hook, &fdf_data);
	mlx_loop_hook(win_info->window, &automatic_rotation, &fdf_data);
	mlx_loop(win_info->window);
}
