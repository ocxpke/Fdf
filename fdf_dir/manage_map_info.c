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
