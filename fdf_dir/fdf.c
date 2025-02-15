/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:52:33 by jose-ara          #+#    #+#             */
/*   Updated: 2025/01/31 13:26:53 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	analyze_splitted(char **splitted, int cont, t_vector **vector_list)
{
	int	word;

	word = 0;
	while (splitted[word])
	{
		add_vector(vector_list, cont, word, ft_atoi(splitted[word]));
		word++;
	}
}

void	init_vectors(int fd, t_vector **vector_list)
{
	int		x;
	char	*line;
	char	**splitted;

	x = 0;
	line = get_next_line(fd);
	while (line)
	{
		splitted = ft_split(line, ' ');
		analyze_splitted(splitted, x, vector_list);
		free_back_splitted(splitted);
		x++;
		free(line);
		line = get_next_line(fd);
	}
}

int	main(int argc, char **argv)
{
	t_vector	*vectors;
	int			fd;

	if (argc != 2)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	vectors = NULL;
	init_vectors(fd, &vectors);
	print_vec_list(vectors);
	free_vec_list(&vectors);
	if (close(fd) == -1)
		exit(EXIT_FAILURE);
	return (0);
}
