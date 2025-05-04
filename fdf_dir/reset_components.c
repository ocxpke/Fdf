/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_components.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:00:00 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/02 18:10:39 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void reset_model_components(t_coordinates **p_points, t_map_info *map_info) {
  int i;
  int j;

  i = 0;
  while (i < map_info->x_length) {
    j = 0;
    while (j < map_info->y_length) {
      p_points[i][j].x = p_points[i][j].x_o;
      p_points[i][j].y = p_points[i][j].y_o;
      p_points[i][j].z = p_points[i][j].z_o;
      p_points[i][j].x_p = p_points[i][j].x_o;
      p_points[i][j].y_p = p_points[i][j].y_o;
      p_points[i][j].z_p = p_points[i][j].z_o;
      j++;
    }
    i++;
  }
}

void reset_user_values(t_fdf_data *fdf_data) {
  t_model_values *model_values;

  model_values = fdf_data->map_info->model_values;
  model_values->first_angle = false;
  model_values->user_x_pos = 0;
  model_values->user_y_pos = 0;
  model_values->zoom = 1;
  model_values->rotation_angle_x = 0;
  model_values->rotation_angle_y = 0;
  model_values->rotation_angle_z = 0;
  model_values->auto_rot = 0;
  reset_user_view(fdf_data->win_info);
  reset_model_components(fdf_data->dis_points, fdf_data->map_info);
  redraw_projection(fdf_data);
}

inline void reset_user_view(t_window *win_info) {
  memset(win_info->img->pixels, BACKGROUND_COLOR,
         win_info->img->width * win_info->img->height * sizeof(int32_t));
}
