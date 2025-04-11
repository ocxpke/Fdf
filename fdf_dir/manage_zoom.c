/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_zoom.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:59:27 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/11 21:23:34 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_zoom_value(t_fdf_data *fdf_data, int mode)
{
	memset(fdf_data->win_info->img->pixels, 0, fdf_data->win_info->img->width
		* fdf_data->win_info->img->height * sizeof(int32_t));
	if (!mode && (fdf_data->map_info->model_values->zoom > 0.1))
	{
		fdf_data->map_info->model_values->zoom -= 0.1;
		printf("Holaaa up %f\n", fdf_data->map_info->model_values->zoom);
	}
	else if (mode && (fdf_data->map_info->model_values->zoom < 5))
	{
		fdf_data->map_info->model_values->zoom += 0.1;
		printf("Holaaa up %f\n", fdf_data->map_info->model_values->zoom);
	}
	recalculate_projection(fdf_data);
}
