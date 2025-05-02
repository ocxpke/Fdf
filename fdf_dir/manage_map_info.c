/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_map_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:00:17 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/02 17:40:33 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief	Sets the length of X, and the length of Y.
 *
 * @param map_info	All the details of our map
 *
 * @return	Void
 */
/*
static void	set_x_and_y_length(t_map_info *map_info)
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
*/
/**
 * @brief	Sets for Z the highest value, and the lowest value
 *
 * @param map_info	All the details of our map
 *
 * @return	Void
 */
/*
static void	search_higher_lower_points(t_map_info *map_info)
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
*/

static int	splitted_len(char *line)
{
	char	**splitted;
	int		i;

	i = 0;
	splitted = ft_split(line, ' ');
	while (splitted[i] != NULL)
		i++;
	free_back_splitted(splitted);
	return (i);
}

void	init_map_info(char *file_in, t_map_info *map_info)
{
	int		fd;
	int		cont;
	char	*line;

	cont = 0;
	fd = open(file_in, O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	line = get_next_line(fd);
	map_info->y_length = splitted_len(line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		cont++;
	}
	map_info->x_length = cont;
	map_info->highest_point = 0;
	map_info->lowest_point = 0;
	ft_printf("Map length %d, %d\n", map_info->x_length, map_info->y_length);
	close(fd);
}
