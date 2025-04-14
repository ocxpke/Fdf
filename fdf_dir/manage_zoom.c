/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_zoom.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:59:27 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/14 19:18:23 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_zoom_value(t_fdf_data *fdf_data, int mode)
{
	reset_user_view(fdf_data->win_info);
	if (!mode && (fdf_data->map_info->model_values->zoom > ZOOM_MIN))
		fdf_data->map_info->model_values->zoom -= ZOOM_CHANGE;
	else if (mode && (fdf_data->map_info->model_values->zoom < ZOOM_MAX))
		fdf_data->map_info->model_values->zoom += ZOOM_CHANGE;
	redraw_projection(fdf_data);
}
