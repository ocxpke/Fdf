/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_angle_views.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:37:44 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/21 19:40:31 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_raised_view(t_window *win_info, t_map_info *map_info,
		t_coordinates **p_matrix)
{
	t_vector		*aux;
	t_model_values	*m_val;
	double			spacing;

	m_val = map_info->model_values;
	aux = map_info->vector_list;
	spacing = spacing_first_angle(win_info->img, map_info->x_length
			+ (map_info->highest_point + (map_info->lowest_point * -1)));
	reset_model_values(m_val);
	while (aux)
	{
		p_matrix[aux->x][aux->y].x = aux->x * spacing;
		p_matrix[aux->x][aux->y].y = (aux->z * -1) * spacing;
		p_matrix[aux->x][aux->y].z = aux->z;
		set_model_values(m_val, p_matrix[aux->x][aux->y].x,
			p_matrix[aux->x][aux->y].y);
		aux = aux->next;
	}
	absolute_min_values(m_val);
	center_view_in_quadrant(win_info->img, m_val, 1);
	m_val->offset_x = m_val->min_x;
	m_val->offset_y = m_val->min_y;
	display_main_projection(win_info, map_info, p_matrix);
}

void	draw_profile_view(t_window *win_info, t_map_info *map_info,
		t_coordinates **p_matrix)
{
	t_vector		*aux;
	t_model_values	*m_val;
	double			spacing;

	m_val = map_info->model_values;
	aux = map_info->vector_list;
	spacing = spacing_first_angle(win_info->img, map_info->y_length
			+ (map_info->highest_point + (map_info->lowest_point * -1)));
	reset_model_values(m_val);
	while (aux)
	{
		p_matrix[aux->x][aux->y].x = aux->y * spacing;
		p_matrix[aux->x][aux->y].y = (aux->z * -1) * spacing;
		p_matrix[aux->x][aux->y].z = aux->z;
		set_model_values(m_val, p_matrix[aux->x][aux->y].x,
			p_matrix[aux->x][aux->y].y);
		aux = aux->next;
	}
	absolute_min_values(m_val);
	center_view_in_quadrant(win_info->img, m_val, 2);
	m_val->offset_x = m_val->min_x;
	m_val->offset_y = m_val->min_y;
	display_main_projection(win_info, map_info, p_matrix);
}

void	draw_plant_view(t_window *win_info, t_map_info *map_info,
		t_coordinates **p_matrix)
{
	t_vector		*aux;
	t_model_values	*m_val;
	double			spacing;

	m_val = map_info->model_values;
	aux = map_info->vector_list;
	spacing = spacing_first_angle(win_info->img, map_info->y_length
			+ map_info->x_length);
	reset_model_values(m_val);
	while (aux)
	{
		p_matrix[aux->x][aux->y].x = aux->y * spacing;
		p_matrix[aux->x][aux->y].y = aux->x * spacing;
		p_matrix[aux->x][aux->y].z = aux->z;
		set_model_values(m_val, p_matrix[aux->x][aux->y].x,
			p_matrix[aux->x][aux->y].y);
		aux = aux->next;
	}
	absolute_min_values(m_val);
	center_view_in_quadrant(win_info->img, m_val, 3);
	m_val->offset_x = m_val->min_x;
	m_val->offset_y = m_val->min_y;
	display_main_projection(win_info, map_info, p_matrix);
}
