/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_model_values.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:07:13 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/11 20:07:30 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_model_values(t_map_info *map_info)
{
	map_info->model_values = (t_center_model *)ft_calloc(1,
			sizeof(t_center_model));
	if (!map_info->model_values)
		return (exit(EXIT_FAILURE));
	map_info->model_values->max_x = 0;
	map_info->model_values->max_y = 0;
	map_info->model_values->max_z = map_info->highest_point;
	map_info->model_values->min_x = 0;
	map_info->model_values->min_y = 0;
	map_info->model_values->min_z = map_info->lowest_point;
	map_info->model_values->center_x_axis = 0;
	map_info->model_values->center_y_axis = 0;
	map_info->model_values->zoom = 1;
}
