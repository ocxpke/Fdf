/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:52:33 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/30 21:28:52 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_coordinates	**dis_points;
	t_map_info		*map_info;
	t_window		*win_info;

	if (argc != 2)
		return (-1);
	map_info = init_map_info(argv[1]);
	win_info = init_window_components();
	dis_points = init_points_matrix(map_info);
	display_main_projection(win_info, map_info, dis_points);
	mlx_image_to_window(win_info->window, win_info->img, win_info->init_width
		* 0.025, 0);
	mlx_loop(win_info->window);
}
