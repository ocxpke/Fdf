/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:18:09 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/15 19:30:02 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	deg_to_rad(double degrees)
{
	return (degrees * (PI_VALUE / 180.0));
}

void	change_rotation_axis(t_fdf_data *fdf_data, int rot_axis)
{
	t_model_values	*model_values;

	model_values = fdf_data->map_info->model_values;
	if (model_values->rotation_axis != rot_axis)
	{
		model_values->rotation_angle_x = 0;
		model_values->rotation_angle_y = 0;
		model_values->rotation_angle_z = 0;
		reset_model_components(fdf_data->map_info->vector_list);
		model_values->rotation_axis = rot_axis;
	}
}

void	check_axis_reset_values(t_fdf_data *fdf_data,
		t_model_values *model_values, int axis)
{
	change_rotation_axis(fdf_data, axis);
	reset_user_view(fdf_data->win_info);
	reset_model_values(model_values);
}

void	calculate_display_rotation(t_fdf_data *fdf_data, int axis)
{
	if (axis == 0)
		calculate_rotated_points_x(fdf_data->map_info);
	else if (axis == 1)
		calculate_rotated_points_y(fdf_data->map_info);
	else if (axis == 2)
		calculate_rotated_points_z(fdf_data->map_info);
	calculate_main_projection(fdf_data->win_info, fdf_data->map_info,
		fdf_data->dis_points);
	display_main_projection(fdf_data->win_info, fdf_data->map_info,
		fdf_data->dis_points);
}
