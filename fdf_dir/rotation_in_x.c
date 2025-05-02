/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_in_x.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:31:01 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/02 18:18:43 by jose-ara         ###   ########.fr       */
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

void	calculate_rotated_points_x(t_window *win_info, t_map_info *map_info,
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
			p_matrix[i][j].y = rotation_on_x_value_y(m_val, p_matrix[i][j].y_o,
					p_matrix[i][j].z_o);
			p_matrix[i][j].z = rotation_on_x_value_z(m_val, p_matrix[i][j].y_o,
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
