/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:46:16 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/30 21:51:25 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_window	*init_window_components(void)
{
	t_window	*win_info;

	win_info = (t_window *)ft_calloc(1, sizeof(t_window));
	if (!win_info)
		return (perror("Error with init t_window"), NULL);
	mlx_set_setting(MLX_MAXIMIZED, 1);
	win_info->window = mlx_init(500, 500, "Fdf", true);
	mlx_get_monitor_size(0, &(win_info->init_width), &(win_info->init_heigth));
	win_info->img = mlx_new_image(win_info->window, round(win_info->init_width
				* 0.95), round(win_info->init_heigth));
	memset(win_info->img->pixels, 125, win_info->img->width
		* win_info->img->height * sizeof(int32_t));
	return (win_info);
}
