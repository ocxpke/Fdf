/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:52:33 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/23 19:25:56 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_map_info	*map_info;
	t_window	win_info;

	if (argc != 2)
		return (-1);
	map_info = NULL;
	init_map_info(argv[1], &map_info);
	print_map_info(map_info);
	init_window_components(&win_info);
	display_main_projection(&win_info, map_info);
	mlx_key_hook(win_info.window, &my_key_hook, &win_info);
	mlx_scroll_hook(win_info.window, &zoom_hook, NULL);
	mlx_loop(win_info.window);
	mlx_delete_image(win_info.window, win_info.img);
	mlx_terminate(win_info.window);
	free_vec_list(&map_info->vector_list);
	free(map_info);
}
