/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_in_z.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:53:17 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/15 19:30:07 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	rotation_on_z_value_x(t_model_values *model_values, int x, int y)
{
	double	radians;

	radians = deg_to_rad(model_values->rotation_angle_z);
	return ((x * cos(radians)) - (y * sin(radians)));
}

double	rotation_on_z_value_y(t_model_values *model_values, int x, int y)
{
	double	radians;

	radians = deg_to_rad(model_values->rotation_angle_z);
	return ((x * sin(radians)) + (y * cos(radians)));
}

void	calculate_rotated_points_z(t_map_info *map_info)
{
	t_vector		*aux;
	t_model_values	*m_val;

	m_val = map_info->model_values;
	aux = map_info->vector_list;
	while (aux)
	{
		aux->x_p = rotation_on_z_value_x(m_val, aux->x, aux->y);
		aux->y_p = rotation_on_z_value_y(m_val, aux->x, aux->y);
		aux = aux->next;
	}
}

void	rotate_model_z(t_fdf_data *fdf_data, int axis, int mode)
{
	t_model_values	*model_values;

	model_values = fdf_data->map_info->model_values;
	check_axis_reset_values(fdf_data, model_values, axis);
	if (!mode && (model_values->rotation_angle_z <= 0))
		model_values->rotation_angle_z = 360;
	else if (!mode)
		model_values->rotation_angle_z -= 2;
	else if (mode && (model_values->rotation_angle_z >= 360))
		model_values->rotation_angle_z = 0;
	else if (mode)
		model_values->rotation_angle_z += 2;
	calculate_display_rotation(fdf_data, axis);
}
