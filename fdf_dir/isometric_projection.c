/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_projection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:37:51 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/11 21:11:16 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		t_coordinates **p_matrix)
{
	t_vector	*aux;

	map_info->model_values->spacing = calculate_spacing(win_info, map_info);
	aux = map_info->vector_list;
	while (aux)
	{
		p_matrix[aux->x][aux->y].x = ((aux->x * map_info->model_values->spacing)
				+ (aux->y * map_info->model_values->spacing)) * cos(0.523599);
		p_matrix[aux->x][aux->y].y = ((aux->x * map_info->model_values->spacing)
				- (aux->y * map_info->model_values->spacing)) * sin(0.523599)
			- (aux->z * map_info->model_values->spacing);
		p_matrix[aux->x][aux->y].z = aux->z;
		set_model_values(map_info->model_values, p_matrix[aux->x][aux->y].x,
			p_matrix[aux->x][aux->y].y);
		aux = aux->next;
	}
	map_info->model_values->min_x *= -1;
	map_info->model_values->min_y *= -1;
	map_info->model_values->center_x_axis = ((win_info->img->width
				- (map_info->model_values->max_x
					+ map_info->model_values->min_x)) / 2);
	map_info->model_values->center_y_axis = ((win_info->img->height
				- (map_info->model_values->max_y
					+ map_info->model_values->min_y)) / 2);
}

/**
 * Recorro 2 veces la matriz de puntos OPTIMIZAR ESTO?
 */
void	display_main_projection(t_window *win_info, t_map_info *map_info,
		t_coordinates **p_matrix)
{
	int	i;
	int	j;

	init_model_values(map_info);
	calculate_main_projection(win_info, map_info, p_matrix);
	i = 0;
	while (i <= map_info->x_length)
	{
		j = 0;
		while (j <= map_info->y_length)
		{
			if (i < map_info->x_length)
				draw_line(win_info->img, map_info->model_values, p_matrix[i][j],
					p_matrix[i + 1][j]);
			if (j < map_info->y_length)
				draw_line(win_info->img, map_info->model_values, p_matrix[i][j],
					p_matrix[i][j + 1]);
			j++;
		}
		i++;
	}
}
