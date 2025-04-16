/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_projection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:37:51 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/16 19:36:54 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	calculate_spacing(t_window *win_info, t_map_info *map_info)
{
	int	sum;
	int	spacing;

	sum = map_info->x_length + map_info->y_length + map_info->highest_point;
	if (win_info->img->width <= win_info->img->height)
		spacing = win_info->img->width / sum;
	else
		spacing = win_info->img->height / sum;
	if (spacing < MINIMUM_SPACING)
		spacing = MINIMUM_SPACING;
	return (spacing);
}

void	calculate_main_projection(t_window *win_info, t_map_info *map_info,
		t_coordinates **p_matrix)
{
	t_vector		*aux;
	t_model_values	*m_val;

	m_val = map_info->model_values;
	aux = map_info->vector_list;
	while (aux)
	{
		p_matrix[aux->x][aux->y].x = (((aux->x_p * m_val->spacing) + (aux->y_p
						* m_val->spacing)) * cos(0.523599)) * m_val->zoom;
		p_matrix[aux->x][aux->y].y = (((aux->x_p * m_val->spacing) - (aux->y_p
						* m_val->spacing)) * sin(0.523599) - (aux->z_p
					* m_val->spacing)) * m_val->zoom;
		p_matrix[aux->x][aux->y].z = aux->z;
		set_model_values(m_val, p_matrix[aux->x][aux->y].x,
			p_matrix[aux->x][aux->y].y);
		aux = aux->next;
	}
	absolute_min_values(m_val);
	center_model(win_info, m_val);
	set_offsets(win_info->img, map_info->model_values);
}

/**
 * Recorro 2 veces la matriz de puntos OPTIMIZAR ESTO?
 */
void	display_main_projection(t_window *win_info, t_map_info *map_info,
		t_coordinates **p_matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i <= map_info->x_length)
	{
		j = 0;
		while (j <= map_info->y_length)
		{
			if (i < map_info->x_length)
				draw_line(win_info->img, map_info->model_values, p_matrix[i][j],
					p_matrix[i + 1][j]);
			if (j < map_info->y_length)
				draw_line(win_info->img, map_info->model_values, p_matrix[i][j],
					p_matrix[i][j + 1]);
			j++;
		}
		i++;
	}
}
