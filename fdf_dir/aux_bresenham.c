/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_bresenham.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:55:01 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/04 21:31:26 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	assign_color(int z, int min, int trisection)
{
	int	real_value;

	real_value = z + (min * -1);
	if (real_value < trisection)
		return (1);
	else if (real_value >= trisection && real_value <= (trisection * 2))
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
	ft_printf("trisection: %d\n", trisection);
	color_0 = assign_color(data.z0, model_values->min_z, trisection);
	color_1 = assign_color(data.z1, model_values->min_z, trisection);
	ft_printf("color1: %d, color2: %d\n", color_0, color_1);
	if (color_0 == color_1)
		return ((0xFF << (color_0 * 8)) | 0xFF);
	else
		return ((0xFF << (color_0 * 8)) | (0xFF << (color_1 * 8)) | 0xFF);
}
