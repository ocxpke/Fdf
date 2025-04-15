/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_model_values.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:07:13 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/15 19:12:27 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_model_values(t_window *win_info, t_map_info *map_info)
{
	t_model_values	*model_values;

	map_info->model_values = (t_model_values *)ft_calloc(1,
			sizeof(t_model_values));
	if (!map_info->model_values)
		return (exit(EXIT_FAILURE));
	model_values = map_info->model_values;
	model_values->max_x = 0;
	model_values->max_y = 0;
	model_values->max_z = map_info->highest_point;
	model_values->min_x = 0;
	model_values->min_y = 0;
	model_values->min_z = map_info->lowest_point;
	model_values->center_x_axis = 0;
	model_values->center_y_axis = 0;
	model_values->zoom = 1;
	model_values->spacing = calculate_spacing(win_info, map_info);
	model_values->user_x_pos = 0;
	model_values->user_y_pos = 0;
	model_values->rotation_angle_x = 0;
	model_values->rotation_angle_y = 0;
	model_values->rotation_angle_z = 0;
	model_values->rotation_axis = 0;
}
