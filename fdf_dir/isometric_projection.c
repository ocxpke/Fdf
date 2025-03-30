/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_projection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:37:51 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/30 23:02:40 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	calculate_spacing(t_window *win_info, t_map_info *map_info)
{
	int	sum;
	int	spacing;

	sum = map_info->x_length + map_info->y_length;
	if (win_info->init_heigth <= win_info->init_width)
		spacing = win_info->init_heigth / (sum * 1.5);
	else
		spacing = win_info->init_heigth / (sum * 1.5);
	return (spacing);
}

void	calculate_main_projection(t_window *win_info, t_map_info *map_info,
		t_coordinates **p_matrix)
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
		aux = aux->next;
	}
}

void	add_offset(t_map_info *map_info, t_coordinates **p_matrix)
{
	int			min_x;
	int			min_y;
	t_vector	*aux;

	aux = map_info->vector_list;
	min_x = 0;
	min_y = 0;
	while (aux)
	{
		if (p_matrix[aux->x][aux->y].x < min_x)
			min_x = p_matrix[aux->x][aux->y].x;
		if (p_matrix[aux->x][aux->y].y < min_y)
			min_y = p_matrix[aux->x][aux->y].y;
		aux = aux->next;
	}
	min_x *= -1;
	min_y *= -1;
	aux = map_info->vector_list;
	while (aux)
	{
		p_matrix[aux->x][aux->y].x += min_x;
		p_matrix[aux->x][aux->y].y += min_y;
		aux = aux->next;
	}
}

/**
 * Recorro 4 veces la matriz de puntos OPTIMIZAR ESTO!!!!!
 */
void	display_main_projection(t_window *win_info, t_map_info *map_info,
		t_coordinates **p_matrix)
{
	int	i;
	int	j;

	calculate_main_projection(win_info, map_info, p_matrix);
	add_offset(map_info, p_matrix);
	i = 0;
	while (i <= map_info->x_length)
	{
		j = 0;
		while (j <= map_info->y_length)
		{
			if (i < map_info->x_length)
				draw_line(win_info->img, p_matrix[i][j], p_matrix[i + 1][j]);
			if (j < map_info->y_length)
				draw_line(win_info->img, p_matrix[i][j], p_matrix[i][j + 1]);
			j++;
		}
		i++;
	}
}
