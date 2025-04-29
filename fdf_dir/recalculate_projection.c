/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recalculate_projection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:43:08 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/29 23:46:19 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_offsets(mlx_image_t *img, t_model_values *model_values)
{
	int	total_width;
	int	total_height;

	total_width = model_values->max_x + model_values->min_x;
	total_height = model_values->max_y + model_values->min_y;
	model_values->offset_x = model_values->min_x + model_values->user_x_pos;
	model_values->offset_y = model_values->min_y + model_values->user_y_pos;
	if (total_width >= (int)img->width)
		model_values->offset_x -= ((total_width - img->width) / 2);
	if (total_height >= (int)img->height)
		model_values->offset_y -= ((total_height - img->height) / 2);
}

void	redraw_projection(t_fdf_data *fdf_data)
{
	reset_model_values(fdf_data->map_info->model_values);
	calculate_main_projection(fdf_data->win_info, fdf_data->map_info,
		fdf_data->dis_points);
	display_main_projection(fdf_data->win_info, fdf_data->map_info,
		fdf_data->dis_points);
}
