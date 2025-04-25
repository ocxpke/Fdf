/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_vectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:02:26 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/25 21:14:37 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief	Analyses the splitted struct with all the vectors readed of a line,
 * and adds node by node
 *
 * @param splitted	The splitted struct with every node
 * @param cont The x component of the vector (file line)
 * @param vector_list	Linked list with all the vectors
 *
 * @return	Void
 */
static void	analyze_splitted(char **splitted, int cont, t_vector **vector_list)
{
	int	word;

	word = 0;
	while (splitted[word])
	{
		if (add_vector(vector_list, cont, word, ft_atoi(splitted[word])) == -1)
		{
			// Check
			free_vec_list(vector_list);
			perror("Error with vector list component");
			exit(EXIT_FAILURE);
		}
		word++;
	}
}

int	add_vector(t_vector **vectors, int x, int y, int z)
{
	t_vector	*new_vector;
	t_vector	*iter;

	new_vector = (t_vector *)ft_calloc(1, sizeof(t_vector));
	if (!new_vector)
		return (-1);
	new_vector->x = x;
	new_vector->y = y;
	new_vector->z = z;
	new_vector->x_p = x;
	new_vector->y_p = y;
	new_vector->z_p = z;
	new_vector->next = NULL;
	if (!(*vectors))
	{
		(*vectors) = new_vector;
		return (0);
	}
	iter = (*vectors);
	while (iter->next)
		iter = iter->next;
	iter->next = new_vector;
	return (0);
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
	free(line);
}

void	free_vec_list(t_vector **vectors)
{
	t_vector	*iter;
	t_vector	*to_free;

	iter = (*vectors);
	while (iter)
	{
		to_free = iter;
		iter = iter->next;
		free(to_free);
	}
	*vectors = NULL;
}

void	print_vec_list(t_vector *list)
{
	while (list)
	{
		ft_printf("X: %d, Y: %d, Z: %d\n", list->x, list->y, list->z);
		list = list->next;
	}
}
