/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_in_y.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:51:01 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/15 19:29:56 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	rotation_on_y_value_x(t_model_values *model_values, int x, int z)
{
	double	radians;

	radians = deg_to_rad(model_values->rotation_angle_y);
	return ((x * cos(radians)) + (z * sin(radians)));
}

double	rotation_on_y_value_z(t_model_values *model_values, int x, int z)
{
	double	radians;

	radians = deg_to_rad(model_values->rotation_angle_y);
	return (((-x) * sin(radians)) + (z * cos(radians)));
}

void	calculate_rotated_points_y(t_map_info *map_info)
{
	t_vector		*aux;
	t_model_values	*m_val;

	m_val = map_info->model_values;
	aux = map_info->vector_list;
	while (aux)
	{
		aux->x_p = rotation_on_y_value_x(m_val, aux->x, aux->z);
		aux->z_p = rotation_on_y_value_z(m_val, aux->x, aux->z);
		aux = aux->next;
	}
}

void	rotate_model_y(t_fdf_data *fdf_data, int axis, int mode)
{
	t_model_values	*model_values;

	model_values = fdf_data->map_info->model_values;
	check_axis_reset_values(fdf_data, model_values, axis);
	if (!mode && (model_values->rotation_angle_y <= 0))
		model_values->rotation_angle_y = 360;
	else if (!mode)
		model_values->rotation_angle_y -= 2;
	else if (mode && (model_values->rotation_angle_y >= 360))
		model_values->rotation_angle_y = 0;
	else if (mode)
		model_values->rotation_angle_y += 2;
	calculate_display_rotation(fdf_data, axis);
}
