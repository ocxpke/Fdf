/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_bresenham.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:55:01 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/11 19:49:54 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint32_t	assign_color(int z0, int z1, int min, double pensection)
{
	double	real_value;

	real_value = ((double)(z0 + (min * -1)) + (z1 + (min * -1))) / 2;
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

void	set_colors(t_center_model *model_values, t_bresenham *data)
{
	double	pensection;

	if (model_values->max_z == model_values->min_z)
	{
		data->color_print = 0x00FFFFFF;
		return ;
	}
	pensection = ((double)model_values->max_z + (model_values->min_z * -1)) / 5;
	data->color_print = assign_color(data->z0, data->z1, model_values->min_z,
			pensection);
}

int	point_in_field(int x, int y, mlx_image_t *img)
{
	if ((((y <= (int)img->height) && (y >= 0)) && ((x <= (int)img->width)
				&& (x >= 0))))
		return (1);
	return (0);
}
