/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:45:34 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/14 19:43:18 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_model_values(t_model_values *model_values)
{
	model_values->center_x_axis = 0;
	model_values->center_y_axis = 0;
	model_values->max_x = 0;
	model_values->max_y = 0;
	model_values->min_x = 0;
	model_values->min_y = 0;
}

void	set_model_values(t_model_values *model_values, int x, int y)
{
	if (model_values->max_x < x)
		model_values->max_x = x;
	if (model_values->min_x > x)
		model_values->min_x = x;
	if (model_values->max_y < y)
		model_values->max_y = y;
	if (model_values->min_y > y)
		model_values->min_y = y;
}

void	absolute_min_values(t_model_values *model_values)
{
	model_values->min_x *= -1;
	model_values->min_y *= -1;
}

void	center_model(t_window *win_info, t_model_values *model_values)
{
	int	model_width;
	int	model_height;

	model_width = model_values->max_x + model_values->min_x;
	model_height = model_values->max_y + model_values->min_y;
	model_values->center_x_axis = (win_info->img->width - model_width) / 2;
	model_values->center_y_axis = (win_info->img->height - model_height) / 2;
	if ((((int)win_info->img->width) - model_width) <= 0)
		model_values->center_x_axis = 0;
	if ((((int)win_info->img->height) - model_height) <= 0)
		model_values->center_y_axis = 0;
}
