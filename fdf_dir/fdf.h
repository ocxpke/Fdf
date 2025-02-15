/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:51:40 by jose-ara          #+#    #+#             */
/*   Updated: 2025/01/31 13:28:09 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "./libft/libft.h"
#include <fcntl.h>

typedef struct s_vector
{
	int				x;
	int				y;
	int				z;
	struct s_vector	*next;
}					t_vector;

int					add_vector(t_vector **vectors, int x, int y, int z);
void				free_vec_list(t_vector **vectors);
void				print_vec_list(t_vector *list);
