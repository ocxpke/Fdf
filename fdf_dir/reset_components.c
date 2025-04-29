/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_components.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:00:00 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/29 23:57:30 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_model_components(t_vector *vector)
{
	t_vector	*aux;

	aux = vector;
	while (aux)
	{
		aux->x_p = aux->x;
		aux->y_p = aux->y;
		aux->z_p = aux->z;
		aux = aux->next;
	}
}

void	reset_user_values(t_fdf_data *fdf_data)
{
	t_model_values	*model_values;

	model_values = fdf_data->map_info->model_values;
	model_values->first_angle = false;
	model_values->user_x_pos = 0;
	model_values->user_y_pos = 0;
	model_values->zoom = 1;
	model_values->rotation_angle_x = 0;
	model_values->rotation_angle_y = 0;
	model_values->rotation_angle_z = 0;
	reset_user_view(fdf_data->win_info);
	reset_model_components(fdf_data->map_info->vector_list);
	redraw_projection(fdf_data);
}

inline void	reset_user_view(t_window *win_info)
{
	memset(win_info->img->pixels, BACKGROUND_COLOR, win_info->img->width
		* win_info->img->height * sizeof(int32_t));
}
