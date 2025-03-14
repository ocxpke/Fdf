/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:52:33 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/14 21:45:35 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <string.h>
#include <stdio.h>


int	main(/*int argc, char **argv*/)
{
	/*
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
	*/
	mlx_t *win = mlx_init(500, 500, "Paco", false);
	mlx_image_t *img = mlx_new_image(win, 450, 450);
	t_vector x1;
	x1.x = 225;
	x1.y = 225;
	t_vector x2;
	x2.x = 0;
	x2.y = 0;
	t_vector x3;
	x3.x = 450;
	x3.y = 0;
	t_vector x4;
	x4.x = 0;
	x4.y = 450;
	t_vector x5;
	x5.x = 450;
	x5.y = 450;
	t_vector x6;
	x6.x = 225;
	x6.y = 450;
	t_vector x7;
	x7.x =450;
	x7.y = 225;
	t_vector x8;
	x8.x = 225;
	x8.y = 0;
	t_vector x9;
	x9.x =0;
	x9.y = 225;

	draw_line(img, x1, x2);
	draw_line(img, x1, x3);
	draw_line(img, x1, x4);
	draw_line(img, x1, x5);
	draw_line(img, x1, x6);
	draw_line(img, x1, x7);
	draw_line(img, x1, x8);
	draw_line(img, x1, x9);
	mlx_image_to_window(win, img, 0, 0);

	mlx_loop(win);
	mlx_terminate(win);
}


