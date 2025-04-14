/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:41:42 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/14 19:08:31 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	keyboard_hooks(mlx_key_data_t keydata, void *param)
{
	t_fdf_data	*fdf_data;

	fdf_data = (t_fdf_data *)param;
	if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		set_y_axis_position(fdf_data, 0);
	if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		set_y_axis_position(fdf_data, 1);
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		set_x_axis_position(fdf_data, 0);
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		set_x_axis_position(fdf_data, 1);
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		reset_user_values(fdf_data);
}

void	zoom_hook(double xdelta, double ydelta, void *param)
{
	t_fdf_data	*fdf_data;

	fdf_data = (t_fdf_data *)param;
	if (xdelta > 0)
		write(1, "x+\n", 3);
	else if (xdelta < 0)
		write(1, "x-\n", 3);
	if (ydelta > 0)
		change_zoom_value(fdf_data, 1);
	else if (ydelta < 0)
		change_zoom_value(fdf_data, 0);
}
