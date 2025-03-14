/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:51:40 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/14 22:03:24 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "./libft/libft.h"
# include <fcntl.h>

typedef struct s_vector
{
	int				x;
	int				y;
	int				z;
	struct s_vector	*next;
}					t_vector;

typedef struct s_bresenham
{
	int				x0;
	int				x1;
	int				y0;
	int				y1;
	int				delta_x;
	int				delta_y;
	int				point;
	int				decision_param;
	int				direction;
}					t_bresenham;

void				init_vectors(int fd, t_vector **vector_list);
int					add_vector(t_vector **vectors, int x, int y, int z);
void				free_vec_list(t_vector **vectors);
void				print_vec_list(t_vector *list);

void				draw_line(mlx_image_t *img, t_vector v1, t_vector v2);

#endif
