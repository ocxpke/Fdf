/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_display_points.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:09:27 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/21 19:57:51 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coordinates	**free_back_coord(t_coordinates **points_matrix)
{
	int	i;

	i = 0;
	while (points_matrix[i])
	{
		free(points_matrix[i]);
		i++;
	}
	free(points_matrix);
	return (NULL);
}

t_coordinates	**init_points_matrix(t_map_info *map_info)
{
	t_coordinates	**points_matrix;
	int				i;

	i = 0;
	points_matrix = (t_coordinates **)ft_calloc(map_info->x_length + 2,
			sizeof(t_coordinates *));
	if (!points_matrix)
		return (perror("Error v1 matrix"), NULL);
	while (i <= map_info->x_length)
	{
		points_matrix[i] = (t_coordinates *)ft_calloc(map_info->y_length + 1,
				sizeof(t_coordinates));
		if (!points_matrix[i])
			return (perror("Error v2 matrix"), free_back_coord(points_matrix));
		i++;
	}
	return (points_matrix);
}
