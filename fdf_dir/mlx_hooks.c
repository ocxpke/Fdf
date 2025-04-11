/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:41:42 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/11 21:23:44 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf_data	*fdf_data;

	fdf_data = (t_fdf_data *)param;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_RELEASE)
	{
		change_zoom_value(fdf_data, 0);
	}
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_RELEASE)
	{
		change_zoom_value(fdf_data, 1);
	}
}

void	zoom_hook(double xdelta, double ydelta, void *param)
{
	t_fdf_data	*fdf_data;

	fdf_data = (t_fdf_data *)param;
	xdelta = 0;
	param = NULL;
	if (ydelta > 0)
	{
		printf("Holaaa up\n");
		change_zoom_value(fdf_data, 1);
	}
	else if (ydelta < 0)
	{
		printf("Holaaa down\n");
		change_zoom_value(fdf_data, 0);
	}
}
