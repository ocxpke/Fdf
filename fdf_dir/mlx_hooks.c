/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:41:42 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/23 19:29:00 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_key_hook(mlx_key_data_t keydata, void *win_info)
{
	t_window	*paco;

	paco = (t_window *)win_info;
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_RELEASE)
	{
		ft_printf("Q\n");
		mlx_image_to_window(paco->window, paco->img, round(paco->init_width
				* 0.025), round(paco->init_heigth * 0.01));
	}
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
	{
		ft_printf("W\n");
		if (paco->img->enabled == false)
			paco->img->enabled = true;
		else
			paco->img->enabled = false;
	}
}

void	zoom_hook(double xdelta, double ydelta, void *param)
{
	xdelta = 0;
	param = NULL;
	if (ydelta > 0)
		printf("Up!\n");
	else if (ydelta < 0)
		printf("Down!\n");
}
