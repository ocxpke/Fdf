/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections_3d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:32:06 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/20 20:41:26 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coordinates	**free_back_coordinates(t_coordinates **points)
{
	int	i;

	i = 0;
	while (points[i])
	{
		free(points[i]);
		i++;
	}
	free(points);
	return (NULL);
}

t_coordinates	**init_coordinates_matrix(t_map_info *map_info)
{
	int				i;
	t_coordinates	**points;

	i = 0;
	points = (t_coordinates **)ft_calloc(map_info->x_length + 2,
			sizeof(t_coordinates *));
	if (!points)
		return (NULL);
	while (i <= map_info->x_length)
	{
		points[i] = (t_coordinates *)ft_calloc(map_info->y_length + 1,
				sizeof(t_coordinates));
		if (!points[i])
			return (free_back_coordinates(points));
		i++;
	}
	return (points);
}

void	fill_coordinates_matrix(t_coordinates **points, t_map_info *map_info)
{
	t_vector	*aux;

	aux = map_info->vector_list;
	while (aux)
	{
		points[aux->x][aux->y].x = aux->x * 50;
		points[aux->x][aux->y].y = aux->y * 50;
		aux = aux->next;
	}
}

void	draw_map(t_window *win_info, t_map_info *map_info,
		t_coordinates **points)
{
	int	x;
	int	y;

	x = 0;
	while (x <= map_info->x_length)
	{
		y = 0;
		while (y <= map_info->y_length)
		{
			if (x != map_info->x_length)
				draw_line(win_info->img, points[x][y], points[x + 1][y]);
			if (y != map_info->y_length)
				draw_line(win_info->img, points[x][y], points[x][y + 1]);
			y++;
		}
		x++;
	}
}

void	display_main_projection(t_window *win_info, t_map_info *map_info)
{
	t_coordinates	**points;

	points = init_coordinates_matrix(map_info);
	if (!points)
		exit(EXIT_FAILURE);
	fill_coordinates_matrix(points, map_info);
	draw_map(win_info, map_info, points);
	free_back_coordinates(points);
}
