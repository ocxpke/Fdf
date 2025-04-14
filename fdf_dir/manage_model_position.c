/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_model_position.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:23:40 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/14 19:39:34 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_x_axis_position(t_fdf_data *fdf_data, int mode)
{
	t_model_values	*model_values;

	reset_user_view(fdf_data->win_info);
	model_values = fdf_data->map_info->model_values;
	if (mode)
		model_values->user_x_pos += 50;
	else
		model_values->user_x_pos -= 50;
	redraw_projection(fdf_data);
}

void	set_y_axis_position(t_fdf_data *fdf_data, int mode)
{
	t_model_values	*model_values;

	reset_user_view(fdf_data->win_info);
	model_values = fdf_data->map_info->model_values;
	if (mode)
		model_values->user_y_pos += 50;
	else
		model_values->user_y_pos -= 50;
	redraw_projection(fdf_data);
}
