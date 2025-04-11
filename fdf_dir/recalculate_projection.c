/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recalculate_projection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:43:08 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/11 21:25:23 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	recalculate_values(t_fdf_data *fdf_data)
{
	t_vector	*aux;

	aux = fdf_data->map_info->vector_list;
	while (aux)
	{
		fdf_data->dis_points[aux->x][aux->y].x = (double)(((aux->x
					* fdf_data->map_info->model_values->spacing) + (aux->y
					* fdf_data->map_info->model_values->spacing))
			* cos(0.523599)) * fdf_data->map_info->model_values->zoom;
		fdf_data->dis_points[aux->x][aux->y].y = (double)(((aux->x
					* fdf_data->map_info->model_values->spacing) - (aux->y
					* fdf_data->map_info->model_values->spacing))
			* sin(0.523599) - (aux->z
				* fdf_data->map_info->model_values->spacing))
			* fdf_data->map_info->model_values->zoom;
		aux = aux->next;
	}
}

void	recalculate_projection(t_fdf_data *fdf_data)
{
	int	i;
	int	j;

	i = 0;
	//recalculate_values(fdf_data);
	while (i <= fdf_data->map_info->x_length)
	{
		j = 0;
		while (j <= fdf_data->map_info->y_length)
		{
			if (i < fdf_data->map_info->x_length)
				draw_line(fdf_data->win_info->img,
					fdf_data->map_info->model_values,
					fdf_data->dis_points[i][j], fdf_data->dis_points[i + 1][j]);
			if (j < fdf_data->map_info->y_length)
				draw_line(fdf_data->win_info->img,
					fdf_data->map_info->model_values,
					fdf_data->dis_points[i][j], fdf_data->dis_points[i][j + 1]);
			j++;
		}
		i++;
	}
}
