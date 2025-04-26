/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_bresenham.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:55:01 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/18 00:51:25 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief	We set the color of the line that we are going to draw,
 * depending on his height
 *
 * @param z0	The height of the first point
 * @param z1	The height of the second point
 * @param min	The minimum value of the map
 * @param pensection	The result of dividing the total height by five
 *
 * @return	Void
 */
inline static uint32_t assign_color(int z0, int z1, int min,
                                    double pensection) {
  double real_value;

  real_value = ((double)(z0 + (min * -1)) + (z1 + (min * -1))) / 2;
  if (real_value <= pensection)
    return (0x0000FFFF);
  else if ((real_value > pensection) && (real_value <= (pensection * 2)))
    return (0x00FFFFFF);
  else if ((real_value > (pensection * 2)) && (real_value <= (pensection * 3)))
    return (0x00FF00FF);
  else if ((real_value > (pensection * 3)) && (real_value <= (pensection * 4)))
    return (0xFFFF00FF);
  else
    return (0xFF0000FF);
}

void set_colors(t_model_values *model_values, t_bresenham *data) {
  double pensection;

  if (!model_values || model_values->max_z == model_values->min_z) {
    data->color_print = DEFAULT_COLOR;
    return;
  }
  pensection = ((double)model_values->max_z + (model_values->min_z * -1)) / 5;
  data->color_print =
      assign_color(data->z0, data->z1, model_values->min_z, pensection);
}

int point_in_field(int x, int y, mlx_image_t *img) {
  if (x <= 0 || y <= 0)
    return (0);
  if (x >= INT32_MAX || y >= INT32_MAX)
    return (0);
  if ((((y < (int)img->height) && (y > 0)) &&
       ((x < (int)img->width) && (x > 0))))
    return (1);
  return (0);
}

inline void set_bresenham(t_bresenham *data, t_model_values *model_values,
                          t_coordinates v0, t_coordinates v1) {
  if (!model_values) {
    data->x0 = v0.x;
    data->x1 = v1.x;
    data->y0 = v0.y;
    data->y1 = v1.y;
  } else {
    data->x0 = v0.x + model_values->offset_x + model_values->center_x_axis;
    data->x1 = v1.x + model_values->offset_x + model_values->center_x_axis;
    data->y0 = v0.y + model_values->offset_y + model_values->center_y_axis;
    data->y1 = v1.y + model_values->offset_y + model_values->center_y_axis;
  }
  data->z0 = v0.z;
  data->z1 = v1.z;
}
