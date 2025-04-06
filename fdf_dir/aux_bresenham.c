/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_bresenham.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:55:01 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/06 22:46:09 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
int	assign_color(int z, int min, int hexsection)
{
	int	real_value;

	real_value = z + (min * -1);
	if (real_value <= hexsection)
		return (1);
	else if ((real_value > hexsection) && (real_value <= (hexsection * 2)))
		return (2);
	else
		return (3);
}

uint32_t	set_color(t_center_model *model_values, t_bresenham data)
{
	int	trisection;
	int	color_0;
	int	color_1;

	if (model_values->max_z == model_values->min_z)
		return (0x00FFFFFF);
	trisection = (model_values->max_z + (model_values->min_z * -1)) / 3;
	color_0 = assign_color(data.z0, model_values->min_z, trisection);
	color_1 = assign_color(data.z1, model_values->min_z, trisection);
	if (color_0 == color_1)
		return ((0xFF << (color_0 * 8)) | 0xFF);
	else if (abs(color_0 - color_1) == 2)
		return ((0xFF << (2 * 8)) | 0xFF);
	else
		return ((0xFF << (color_0 * 8)) | (0xFF << (color_1 * 8)) | 0xFF);
}
		*/
uint32_t	assign_color(int z, int min, int pensection)
{
	int	real_value;

	real_value = z + (min * -1);
	if (real_value <= pensection)
		return (0x0000FFFF);
	else if ((real_value > pensection) && (real_value <= (pensection * 2)))
		return (0x00FFFFFF);
	else if ((real_value > (pensection * 2)) && (real_value <= (pensection
				* 3)))
		return (0x00FF00FF);
	else if ((real_value > (pensection * 3)) && (real_value <= (pensection
				* 4)))
		return (0xFFFF00FF);
	else
		return (0xFF0000FF);
}

void	set_colors(t_center_model *model_values, t_bresenham *data,
		int color_parts)
{
	int	pensection;

	if (model_values->max_z == model_values->min_z)
	{
		data->color_z0 = 0x00FFFFFF;
		data->color_z1 = 0x00FFFFFF;
		data->color_print = data->color_z0;
		return ;
	}
	pensection = (model_values->max_z + (model_values->min_z * -1)) / 5;
	data->color_z0 = assign_color(data->z0, model_values->min_z, pensection);
	data->color_z1 = assign_color(data->z0, model_values->min_z, pensection);
	data->color_print = data->color_z0;
	color_parts = 0;
}
