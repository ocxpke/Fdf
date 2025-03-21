/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_map_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:00:17 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/21 20:19:10 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_x_and_y_length(t_map_info *map_info)
{
	int			x_max;
	int			y_max;
	t_vector	*aux;

	x_max = map_info->vector_list->x;
	y_max = map_info->vector_list->y;
	aux = map_info->vector_list;
	while (aux)
	{
		if (x_max < aux->x)
			x_max = aux->x;
		if (y_max < aux->y)
			y_max = aux->y;
		aux = aux->next;
	}
	map_info->x_length = x_max;
	map_info->y_length = y_max;
}

void	search_higher_lower_points(t_map_info *map_info)
{
	int			highest_point;
	int			lowest_point;
	t_vector	*aux;

	highest_point = map_info->vector_list->z;
	lowest_point = map_info->vector_list->z;
	aux = map_info->vector_list;
	while (aux)
	{
		if (highest_point < aux->z)
			highest_point = aux->z;
		if (lowest_point > aux->z)
			lowest_point = aux->z;
		aux = aux->next;
	}
	map_info->highest_point = highest_point;
	map_info->lowest_point = lowest_point;
}

void	print_map_info(t_map_info *map_info)
{
	ft_printf("X length is: %d, and Y length is: %d\n", map_info->x_length,
		map_info->y_length);
	ft_printf("Highest point is: %d, and lowest point is: %d\n",
		map_info->highest_point, map_info->lowest_point);
	print_vec_list(map_info->vector_list);
}

void	init_map_info(char *file_in, t_map_info **map_info)
{
	int	fd;

	fd = open(file_in, O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	(*map_info) = (t_map_info *)ft_calloc(1, sizeof(t_map_info));
	if (!(*map_info))
		return ;
	init_vectors(fd, &((*map_info)->vector_list));
	if (!(*map_info)->vector_list)
		return (free(*map_info), perror("Fallo"));
	set_x_and_y_length(*map_info);
	search_higher_lower_points(*map_info);
	close(fd);
}
