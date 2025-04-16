/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automatic_rotation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:08:29 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/16 15:08:47 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	automatic_rotation(void *param)
{
	t_fdf_data		*fdf_data;
	t_model_values	*model_values;

	fdf_data = (t_fdf_data *)param;
	model_values = fdf_data->map_info->model_values;
	if (model_values->auto_rot)
	{
		if (model_values->rotation_axis == 0)
			rotate_model_x(fdf_data, model_values->rotation_axis, 1);
		else if (model_values->rotation_axis == 1)
			rotate_model_y(fdf_data, model_values->rotation_axis, 1);
		else if (model_values->rotation_axis == 2)
			rotate_model_z(fdf_data, model_values->rotation_axis, 1);
	}
}
