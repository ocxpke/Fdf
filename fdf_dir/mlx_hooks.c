/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:41:42 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/04 19:00:22 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief	Sets the keys that will be used to translate the model.
 *
 * @param keydata MLX structure that contains all the information needed for the
 * keyboard event.
 * @param param The fdf struct (WRAPPER) that will be cast later.
 *
 * @return	Void
 */
static void	translate_hooks(mlx_key_data_t keydata, t_fdf_data *fdf_data)
{
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		set_x_axis_position(fdf_data, 0);
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		set_x_axis_position(fdf_data, 1);
	if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		set_y_axis_position(fdf_data, 0);
	if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		set_y_axis_position(fdf_data, 1);
}

/**
 * @brief	Sets the keys that will be used to rotate the model.
 *
 * @param keydata MLX structure that contains all the information needed for the
 * keyboard event.
 * @param param The fdf struct (WRAPPER) that will be cast later.
 *
 * @return	Void
 */
static void	rotation_hooks(mlx_key_data_t keydata, t_fdf_data *fdf_data)
{
	if (keydata.key == MLX_KEY_Q && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		rotate_model_x(fdf_data, 0, 1);
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		rotate_model_x(fdf_data, 0, 0);
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		rotate_model_y(fdf_data, 1, 1);
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		rotate_model_y(fdf_data, 1, 0);
	if (keydata.key == MLX_KEY_Z && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		rotate_model_z(fdf_data, 2, 1);
	if (keydata.key == MLX_KEY_X && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		rotate_model_z(fdf_data, 2, 0);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		if (fdf_data->map_info->model_values->auto_rot)
			fdf_data->map_info->model_values->auto_rot = false;
		else
			fdf_data->map_info->model_values->auto_rot = true;
	}
}

void	keyboard_hooks(mlx_key_data_t keydata, void *param)
{
	t_fdf_data	*fdf_data;

	fdf_data = (t_fdf_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		return (mlx_close_window(fdf_data->win_info->window));
	if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS)
		swap_map(fdf_data);
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_PRESS)
	{
		if (fdf_data->win_info->leyend_img->enabled)
			fdf_data->win_info->leyend_img->enabled = false;
		else
			fdf_data->win_info->leyend_img->enabled = true;
	}
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
		project_first_angle_view(fdf_data);
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		reset_user_values(fdf_data);
	if (fdf_data->map_info->model_values->first_angle)
		return ;
	rotation_hooks(keydata, fdf_data);
	translate_hooks(keydata, fdf_data);
}

void	zoom_hook(double xdelta, double ydelta, void *param)
{
	t_fdf_data	*fdf_data;

	fdf_data = (t_fdf_data *)param;
	if (fdf_data->map_info->model_values->first_angle)
		return ;
	if (xdelta > 0)
		write(1, "x+\n", 3);
	if (xdelta < 0)
		write(1, "x-\n", 3);
	if (ydelta > 0)
		change_zoom_value(fdf_data, 1);
	else if (ydelta < 0)
		change_zoom_value(fdf_data, 0);
}
