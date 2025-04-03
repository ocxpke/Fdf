/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_projection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:37:51 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/03 20:14:05 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_model_values(t_center_model *model_values)
{
	model_values->max_x = 0;
	model_values->max_y = 0;
	model_values->min_x = 0;
	model_values->min_y = 0;
	model_values->center_x_axis = 0;
	model_values->center_y_axis = 0;
}

void	set_model_values(t_center_model *model_values, int x, int y)
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

// Fix
int	calculate_spacing(t_window *win_info, t_map_info *map_info)
{
	int	sum;
	int	spacing;

	sum = map_info->x_length + map_info->y_length + map_info->highest_point;
	if (win_info->img->width <= win_info->img->height)
		spacing = win_info->img->width / sum;
	else
		spacing = win_info->img->height / sum;
	if (spacing < 3)
		spacing = 3;
	return (spacing);
}

// add offset
void	calculate_main_projection(t_window *win_info, t_map_info *map_info,
		t_coordinates **p_matrix, t_center_model *model_values)
{
	t_vector	*aux;
	int			spacing;

	spacing = calculate_spacing(win_info, map_info);
	aux = map_info->vector_list;
	while (aux)
	{
		p_matrix[aux->x][aux->y].x = ((aux->x * spacing) + (aux->y * spacing))
			* cos(0.523599);
		p_matrix[aux->x][aux->y].y = ((aux->x * spacing) - (aux->y * spacing))
			* sin(0.523599) - (aux->z * spacing);
		set_model_values(model_values, p_matrix[aux->x][aux->y].x,
			p_matrix[aux->x][aux->y].y);
		aux = aux->next;
	}
	model_values->center_x_axis = ((win_info->img->width - (model_values->max_x
					+ (model_values->min_x * -1))) / 2);
	model_values->center_y_axis = ((win_info->img->height - (model_values->max_y
					+ (model_values->min_y * -1))) / 2);
}

// change
/*
void	add_offset(t_window *win_info, t_map_info *map_info,
		t_coordinates **p_matrix)
{
	int			min_x;
	int			min_y;
	int			max_x;
	int			max_y;
	t_vector	*aux;

	aux = map_info->vector_list;
	min_x = 0;
	min_y = 0;
	max_x = 0;
	max_y = 0;
	while (aux)
	{
		if (p_matrix[aux->x][aux->y].x < min_x)
			min_x = p_matrix[aux->x][aux->y].x;
		if (p_matrix[aux->x][aux->y].y < min_y)
			min_y = p_matrix[aux->x][aux->y].y;
		if (p_matrix[aux->x][aux->y].x > max_x)
			max_x = p_matrix[aux->x][aux->y].x;
		if (p_matrix[aux->x][aux->y].y > max_y)
			max_y = p_matrix[aux->x][aux->y].y;
		aux = aux->next;
	}
	min_x *= -1;
	min_y *= -1;
	aux = map_info->vector_list;
	printf("AAAAAAAAAAAAA --> %d, %d, %d, %d\n", win_info->img->height, max_y,
		min_y, ((win_info->img->height - (max_y + (min_y * -1))) / 2));
	while (aux)
	{
		p_matrix[aux->x][aux->y].x += min_x + ((win_info->img->width - (max_x
						+ min_x)) / 2);
		p_matrix[aux->x][aux->y].y += min_y + ((win_info->img->height - (max_y
						+ min_y)) / 2);
		aux = aux->next;
	}
}
	*/

/**
 * Recorro 2 veces la matriz de puntos OPTIMIZAR ESTO?
 */
void	display_main_projection(t_window *win_info, t_map_info *map_info,
		t_coordinates **p_matrix)
{
	t_center_model	model_values;
	int				i;
	int				j;

	init_model_values(&model_values);
	calculate_main_projection(win_info, map_info, p_matrix, &model_values);
	i = 0;
	while (i <= map_info->x_length)
	{
		j = 0;
		while (j <= map_info->y_length)
		{
			if (i < map_info->x_length)
				draw_line(win_info->img, &model_values, p_matrix[i][j],
					p_matrix[i + 1][j]);
			if (j < map_info->y_length)
				draw_line(win_info->img, &model_values, p_matrix[i][j],
					p_matrix[i][j + 1]);
			j++;
		}
		i++;
	}
}
