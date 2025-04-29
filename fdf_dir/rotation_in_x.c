/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_in_x.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:31:01 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/30 00:49:57 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

inline double	rotation_on_x_value_y(t_model_values *model_values, int y,
		int z)
{
	double	radians;

	radians = deg_to_rad(model_values->rotation_angle_x);
	return ((y * cos(radians)) - (z * sin(radians)));
}

inline double	rotation_on_x_value_z(t_model_values *model_values, int y,
		int z)
{
	double	radians;

	radians = deg_to_rad(model_values->rotation_angle_x);
	return ((y * sin(radians)) + (z * cos(radians)));
}

void	calculate_rotated_points_x(t_map_info *map_info)
{
	t_vector		*aux;
	t_model_values	*m_val;

	m_val = map_info->model_values;
	aux = map_info->vector_list;
	while (aux)
	{
		aux->y_p = rotation_on_x_value_y(m_val, aux->y, aux->z);
		aux->z_p = rotation_on_x_value_z(m_val, aux->y, aux->z);
		aux = aux->next;
	}
}

void	rotate_model_x(t_fdf_data *fdf_data, int axis, int mode)
{
	t_model_values	*model_values;

	model_values = fdf_data->map_info->model_values;
	check_axis_reset_values(fdf_data, model_values, axis);
	if (!mode && (model_values->rotation_angle_x <= MIN_ROTATION))
		model_values->rotation_angle_x = MAX_ROTATION;
	else if (!mode)
		model_values->rotation_angle_x -= JUMP_ROTATION;
	else if (mode && (model_values->rotation_angle_x >= MAX_ROTATION))
		model_values->rotation_angle_x = MIN_ROTATION;
	else if (mode)
		model_values->rotation_angle_x += JUMP_ROTATION;
	calculate_display_rotation(fdf_data, axis);
}
