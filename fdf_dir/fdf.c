/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:52:33 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/21 20:17:46 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_map_info	*map_info;
	t_window	window_info;

	if (argc != 2)
		return (-1);
	map_info = NULL;
	init_map_info(argv[1], &map_info);
	print_map_info(map_info);
	init_window_components(&window_info);
	display_main_projection(&window_info, map_info);
	mlx_image_to_window(window_info.window, window_info.img,
		round(window_info.init_width * 0.025), round(window_info.init_heigth
			* 0.01));
	mlx_loop(window_info.window);
	mlx_terminate(window_info.window);
	free_vec_list(&map_info->vector_list);
	free(map_info);
}
