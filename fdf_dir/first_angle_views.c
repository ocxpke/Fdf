/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_angle_views.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:37:44 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/04 19:18:57 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline void	offsets_and_display(t_window *win_info,
		t_map_info *map_info, t_coordinates **p_matrix, int quadrant)
{
	t_model_values	*m_val;

	m_val = map_info->model_values;
	absolute_min_values(m_val);
	center_view_in_quadrant(win_info->img, m_val, quadrant);
	m_val->offset_x = m_val->min_x;
	m_val->offset_y = m_val->min_y;
	display_main_projection(win_info, map_info, p_matrix);
}

void	draw_raised_view(t_window *win_info, t_map_info *map_info,
		t_coordinates **p_matrix)
{
	t_model_values	*m_val;
	double			spacing;
	int				i;
	int				j;

	m_val = map_info->model_values;
	spacing = spacing_first_angle(win_info->img, map_info->x_length
			+ (map_info->highest_point + (map_info->lowest_point * -1)));
	reset_model_values(m_val);
	i = 0;
	while (i < map_info->x_length)
	{
		j = 0;
		while (j < map_info->y_length)
		{
			p_matrix[i][j].x_p = p_matrix[i][j].x_o * spacing;
			p_matrix[i][j].y_p = (p_matrix[i][j].z_o * -1) * spacing;
			p_matrix[i][j].z_p = p_matrix[i][j].z_o;
			set_model_values(m_val, p_matrix[i][j].x_p, p_matrix[i][j].y_p);
			j++;
		}
		i++;
	}
	offsets_and_display(win_info, map_info, p_matrix, 1);
}

void	draw_profile_view(t_window *win_info, t_map_info *map_info,
		t_coordinates **p_matrix)
{
	t_model_values	*m_val;
	double			spacing;
	int				i;
	int				j;

	m_val = map_info->model_values;
	spacing = spacing_first_angle(win_info->img, map_info->y_length
			+ (map_info->highest_point + (map_info->lowest_point * -1)));
	reset_model_values(m_val);
	i = 0;
	while (i < map_info->x_length)
	{
		j = 0;
		while (j < map_info->y_length)
		{
			p_matrix[i][j].x_p = p_matrix[i][j].y_o * spacing;
			p_matrix[i][j].y_p = (p_matrix[i][j].z_o * -1) * spacing;
			p_matrix[i][j].z_p = p_matrix[i][j].x_o;
			set_model_values(m_val, p_matrix[i][j].x_p, p_matrix[i][j].y_p);
			j++;
		}
		i++;
	}
	offsets_and_display(win_info, map_info, p_matrix, 2);
}

void	draw_plant_view(t_window *win_info, t_map_info *map_info,
		t_coordinates **p_matrix)
{
	t_model_values	*m_val;
	double			spacing;
	int				i;
	int				j;

	m_val = map_info->model_values;
	spacing = spacing_first_angle(win_info->img, map_info->y_length
			+ map_info->x_length);
	reset_model_values(m_val);
	i = 0;
	while (i < map_info->x_length)
	{
		j = 0;
		while (j < map_info->y_length)
		{
			p_matrix[i][j].x_p = p_matrix[i][j].y_o * spacing;
			p_matrix[i][j].y_p = p_matrix[i][j].x_o * spacing;
			p_matrix[i][j].z_p = p_matrix[i][j].z_o;
			set_model_values(m_val, p_matrix[i][j].x_p, p_matrix[i][j].y_p);
			j++;
		}
		i++;
	}
	offsets_and_display(win_info, map_info, p_matrix, 3);
}
