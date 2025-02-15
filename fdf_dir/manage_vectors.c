/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_vectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:02:26 by jose-ara          #+#    #+#             */
/*   Updated: 2025/01/31 13:28:26 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
