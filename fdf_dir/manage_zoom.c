/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_zoom.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:59:27 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/21 19:40:55 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_zoom_value(t_fdf_data *fdf_data, int mode)
{
	t_model_values	*model_values;

	model_values = fdf_data->map_info->model_values;
	reset_user_view(fdf_data->win_info);
	if (!mode && (model_values->zoom > ZOOM_MIN))
		model_values->zoom -= (ZOOM_CHANGE * model_values->zoom);
	else if (mode && (model_values->zoom < ZOOM_MAX))
		model_values->zoom += (ZOOM_CHANGE * model_values->zoom);
	redraw_projection(fdf_data);
}
