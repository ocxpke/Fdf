/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_alg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:48:47 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/14 22:31:54 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void	swap_points(t_bresenham *data)
{
	int	tmp;

	tmp = (*data).x0;
	(*data).x0 = (*data).x1;
	(*data).x1 = tmp;
	tmp = (*data).y0;
	(*data).y0 = (*data).y1;
	(*data).y1 = tmp;
}

static void	manage_decision_param(t_bresenham *data, int oper1, int oper2,
		int mode)
{
	if (mode)
	{
		if ((*data).decision_param >= 0)
		{
			(*data).point += (*data).direction;
			(*data).decision_param -= oper1;
		}
		(*data).decision_param += oper2;
	}
	else
	{
		if ((*data).decision_param >= 0)
		{
			(*data).point += (*data).direction;
			(*data).decision_param -= oper1;
		}
		(*data).decision_param += oper2;
	}
}

static void	draw_horizontal_line(mlx_image_t *img, t_bresenham data)
{
	int	i;
	int	oper1;
	int	oper2;

	i = 0;
	if (data.x0 > data.x1)
		swap_points(&data);
	data.delta_x = data.x1 - data.x0;
	data.delta_y = data.y1 - data.y0;
	if (data.delta_y < 0)
		data.direction = -1;
	data.delta_y *= data.direction;
	oper1 = (2 * (data).delta_x);
	oper2 = (2 * (data).delta_y);
	if (data.delta_x != 0)
	{
		data.point = data.y0;
		data.decision_param = oper2 - data.delta_x;
		while (i < data.delta_x)
		{
			mlx_put_pixel(img, data.x0 + i, data.point, 0x00FFFFFF);
			manage_decision_param(&data, oper1, oper2, 1);
			i++;
		}
	}
}

static void	draw_vertical_line(mlx_image_t *img, t_bresenham data)
{
	int	i;
	int	oper1;
	int	oper2;

	i = 0;
	if (data.y0 > data.y1)
		swap_points(&data);
	data.delta_x = data.x1 - data.x0;
	data.delta_y = data.y1 - data.y0;
	if (data.delta_x < 0)
		data.direction = -1;
	data.delta_x *= data.direction;
	oper1 = (2 * (data).delta_y);
	oper2 = (2 * (data).delta_x);
	if (data.delta_y != 0)
	{
		data.point = data.x0;
		data.decision_param = oper2 - data.delta_y;
		while (i < data.delta_y)
		{
			mlx_put_pixel(img, data.point, data.y0 + i, 0x00FFFFFF);
			manage_decision_param(&data, oper1, oper2, 0);
			i++;
		}
	}
}

void	draw_line(mlx_image_t *img, t_vector v1, t_vector v2)
{
	t_bresenham	data;

	data.x0 = v1.x;
	data.x1 = v2.x;
	data.y0 = v1.y;
	data.y1 = v2.y;
	data.direction = 1;
	if (abs(v2.x - v1.x) > abs(v2.y - v1.y))
		draw_horizontal_line(img, data);
	else
		draw_vertical_line(img, data);
}

/*
//Simple algorythmn that draws a line on the 8 octants.
//Makes floating point calculations

int	max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

void	line_alg_no_effi(mlx_image_t *img, t_vector *v1, t_vector *v2)
{
	int		dx;
	int		dy;
	double	steps;
	double	stepX;
	double	stepY;

	dx = v2->x - v1->x;
	dy = v2->y - v1->y;
	steps = max(abs(dx), abs(dy));
	stepX = dx / steps;
	stepY = dy / steps;
	for (int i = 0; i < steps; i++)
	{
		printf("%f, %f\n", v1->x + i * stepX, v1->y + i * stepY);
		mlx_put_pixel(img, v1->x + i * stepX, v1->y + i * stepY, 0x00FF00FF);
	}
}
*/
