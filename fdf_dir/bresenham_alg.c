/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_alg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:48:47 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/30 00:58:55 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

/**
 * @brief	We swap the points of v0 and v1 of bresenham
 *
 * @param data	All data needed for the bresenham algorithm
 *
 * @return Void
 */
static void	swap_points(t_bresenham *data)
{
	int	tmp;

	tmp = data->x0;
	data->x0 = data->x1;
	data->x1 = tmp;
	tmp = data->y0;
	data->y0 = data->y1;
	data->y1 = tmp;
	tmp = data->z0;
	data->z0 = data->z1;
	data->z1 = tmp;
}

/**
 * @brief	Here we decide if the slope of bresenham needs to be changed
 *
 * @param data	All data needed for the bresenham algorithm
 *
 * @return Void
 */
static inline void	manage_decision_param(t_bresenham *data)
{
	if (data->decision_param >= 0)
	{
		data->point += data->direction;
		data->decision_param -= data->oper1;
	}
	data->decision_param += data->oper2;
}

/**
 * @brief	Draws a pixel line for the horizontal octancts.
 *
 * @param img	The image where we are going to draw pixels
 * @param model_values	Model caracterictics
 * @param data	All data needed for the bresenham algorithm
 *
 * @return Void
 */
static void	draw_horizontal_line(mlx_image_t *img, t_model_values *model_values,
		t_bresenham data)
{
	int	i;

	i = 0;
	if (data.x0 > data.x1)
		swap_points(&data);
	data.delta_x = data.x1 - data.x0;
	data.delta_y = data.y1 - data.y0;
	if (data.delta_y < 0)
		data.direction = -1;
	data.delta_y *= data.direction;
	data.oper1 = (2 * (data).delta_x);
	data.oper2 = (2 * (data).delta_y);
	set_colors(model_values, &data);
	if (data.delta_x != 0)
	{
		data.point = data.y0;
		data.decision_param = data.oper2 - data.delta_x;
		while (i < data.delta_x)
		{
			if (point_in_field(data.x0 + i, data.point, img))
				mlx_put_pixel(img, data.x0 + i, data.point, data.color_print);
			manage_decision_param(&data);
			i++;
		}
	}
}

/**
 * @brief	Draws a pixel line for the vertical octancts.
 *
 * @param img	The image where we are going to draw pixels
 * @param model_values	Model caracterictics
 * @param data	All data needed for the bresenham algorithm
 *
 * @return Void
 */
static void	draw_vertical_line(mlx_image_t *img, t_model_values *model_values,
		t_bresenham data)
{
	int	i;

	i = 0;
	if (data.y0 > data.y1)
		swap_points(&data);
	data.delta_x = data.x1 - data.x0;
	data.delta_y = data.y1 - data.y0;
	if (data.delta_x < 0)
		data.direction = -1;
	data.delta_x *= data.direction;
	data.oper1 = (2 * (data).delta_y);
	data.oper2 = (2 * (data).delta_x);
	set_colors(model_values, &data);
	if (data.delta_y != 0)
	{
		data.point = data.x0;
		data.decision_param = data.oper2 - data.delta_y;
		while (i < data.delta_y)
		{
			if (point_in_field(data.point, data.y0 + i, img))
				mlx_put_pixel(img, data.point, data.y0 + i, data.color_print);
			manage_decision_param(&data);
			i++;
		}
	}
}

void	draw_line(mlx_image_t *img, t_model_values *model_values,
		t_coordinates v0, t_coordinates v1)
{
	t_bresenham	data;

	set_bresenham(&data, model_values, v0, v1);
	data.direction = 1;
	if (!point_in_field(data.x0, data.y0, img) && !point_in_field(data.x1,
			data.y1, img))
		return ;
	if (abs(data.x1 - data.x0) >= abs(data.y1 - data.y0))
		draw_horizontal_line(img, model_values, data);
	else
		draw_vertical_line(img, model_values, data);
}
