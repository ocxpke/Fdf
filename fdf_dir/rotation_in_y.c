/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_in_y.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:51:01 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/02 18:29:58 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

inline double	rotation_on_y_value_x(t_model_values *model_values, int x,
		int z)
{
	double	radians;

	radians = deg_to_rad(model_values->rotation_angle_y);
	return ((x * cos(radians)) + (z * sin(radians)));
}

inline double	rotation_on_y_value_z(t_model_values *model_values, int x,
		int z)
{
	double	radians;

	radians = deg_to_rad(model_values->rotation_angle_y);
	return (((-x) * sin(radians)) + (z * cos(radians)));
}

void	calculate_rotated_points_y(t_window *win_info, t_map_info *map_info,
		t_coordinates **p_matrix)
{
	t_model_values	*m_val;
	int				i;
	int				j;

	m_val = map_info->model_values;
	m_val->spacing = calculate_spacing(win_info, map_info);
	i = 0;
	while (i < map_info->x_length)
	{
		j = 0;
		while (j < map_info->y_length)
		{
			p_matrix[i][j].x = rotation_on_y_value_x(m_val, p_matrix[i][j].x_o,
					p_matrix[i][j].z_o);
			p_matrix[i][j].z = rotation_on_y_value_z(m_val, p_matrix[i][j].x_o,
					p_matrix[i][j].z_o);
			calculations(map_info, p_matrix, i, j);
			j++;
		}
		i++;
	}
	absolute_min_values(m_val);
	center_model(win_info, m_val);
	set_offsets(win_info->img, map_info->model_values);
}

void	rotate_model_y(t_fdf_data *fdf_data, int axis, int mode)
{
	t_model_values	*model_values;

	model_values = fdf_data->map_info->model_values;
	check_axis_reset_values(fdf_data, model_values, axis);
	if (!mode && (model_values->rotation_angle_y <= MIN_ROTATION))
		model_values->rotation_angle_y = MAX_ROTATION;
	else if (!mode)
		model_values->rotation_angle_y -= JUMP_ROTATION;
	else if (mode && (model_values->rotation_angle_y >= MAX_ROTATION))
		model_values->rotation_angle_y = MIN_ROTATION;
	else if (mode)
		model_values->rotation_angle_y += JUMP_ROTATION;
	calculate_display_rotation(fdf_data, axis);
}
