/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_first_angle_projection.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:53:24 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/18 01:23:09 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_cross(t_fdf_data *fdf_data)
{
	mlx_image_t		*img;
	t_coordinates	v0;
	t_coordinates	v1;

	reset_model_values(fdf_data->map_info->model_values);
	img = fdf_data->win_info->img;
	v0.x = 1;
	v0.y = (img->height / 2);
	v0.z = 0;
	v1.x = img->width - 1;
	v1.y = (img->height / 2);
	v1.z = 0;
	draw_line(img, NULL, v0, v1);
	v0.x = (img->width / 2);
	v0.y = 1;
	v0.z = 0;
	v1.x = (img->width / 2);
	v1.y = img->height - 1;
	v1.z = 0;
	draw_line(img, NULL, v0, v1);
}

double	spacing_first_angle(mlx_image_t *img, double sum)
{
	if (img->width <= img->height)
		return ((img->width / 2) / sum);
	else
		return ((img->height / 2) / sum);
}

void	center_view_in_quadrant(mlx_image_t *img, t_model_values *model_values,
		int quadrant)
{
	int	model_width;
	int	model_height;

	model_width = model_values->max_x + model_values->min_x;
	model_height = model_values->max_y + model_values->min_y;
	if (quadrant == 1)
	{
		model_values->center_x_axis = 0;
		model_values->center_y_axis = 0;
	}
	else if (quadrant == 2)
	{
		model_values->center_x_axis = img->width / 2;
		model_values->center_y_axis = 0;
	}
	else
	{
		model_values->center_x_axis = img->width / 2;
		model_values->center_y_axis = img->height / 2;
	}
	model_values->center_x_axis += ((img->width / 2) - model_width) / 2;
	model_values->center_y_axis += ((img->height / 2) - model_height) / 2;
}

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

void	project_first_angle_view(t_fdf_data *fdf_data)
{
	t_model_values	*model_values;

	model_values = fdf_data->map_info->model_values;
	if (model_values->first_angle)
		return (reset_user_values(fdf_data));
	model_values->first_angle = true;
	model_values->auto_rot = false;
	reset_user_view(fdf_data->win_info);
	draw_cross(fdf_data);
	draw_raised_view(fdf_data->win_info, fdf_data->map_info,
		fdf_data->dis_points);
	draw_profile_view(fdf_data->win_info, fdf_data->map_info,
		fdf_data->dis_points);
	draw_plant_view(fdf_data->win_info, fdf_data->map_info,
		fdf_data->dis_points);
}
