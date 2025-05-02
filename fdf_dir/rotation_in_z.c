/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_in_z.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:53:17 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/02 18:29:59 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

inline double	rotation_on_z_value_x(t_model_values *model_values, int x,
		int y)
{
	double	radians;

	radians = deg_to_rad(model_values->rotation_angle_z);
	return ((x * cos(radians)) - (y * sin(radians)));
}

inline double	rotation_on_z_value_y(t_model_values *model_values, int x,
		int y)
{
	double	radians;

	radians = deg_to_rad(model_values->rotation_angle_z);
	return ((x * sin(radians)) + (y * cos(radians)));
}

void	calculate_rotated_points_z(t_window *win_info, t_map_info *map_info,
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
			p_matrix[i][j].x = rotation_on_z_value_x(m_val, p_matrix[i][j].x_o,
					p_matrix[i][j].y_o);
			p_matrix[i][j].y = rotation_on_z_value_y(m_val, p_matrix[i][j].x_o,
					p_matrix[i][j].y_o);
			calculations(map_info, p_matrix, i, j);
			j++;
		}
		i++;
	}
	absolute_min_values(m_val);
	center_model(win_info, m_val);
	set_offsets(win_info->img, map_info->model_values);
}

void	rotate_model_z(t_fdf_data *fdf_data, int axis, int mode)
{
	t_model_values	*model_values;

	model_values = fdf_data->map_info->model_values;
	check_axis_reset_values(fdf_data, model_values, axis);
	if (!mode && (model_values->rotation_angle_z <= MIN_ROTATION))
		model_values->rotation_angle_z = MAX_ROTATION;
	else if (!mode)
		model_values->rotation_angle_z -= JUMP_ROTATION;
	else if (mode && (model_values->rotation_angle_z >= MAX_ROTATION))
		model_values->rotation_angle_z = MIN_ROTATION;
	else if (mode)
		model_values->rotation_angle_z += JUMP_ROTATION;
	calculate_display_rotation(fdf_data, axis);
}
