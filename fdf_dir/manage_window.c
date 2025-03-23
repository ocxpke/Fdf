/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:46:16 by jose-ara          #+#    #+#             */
/*   Updated: 2025/03/21 20:14:44 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int init_window_components(t_window *win_info) {
  mlx_set_setting(MLX_MAXIMIZED, 1);
  win_info->window = mlx_init(1, 1, "Fdf", false);
  mlx_get_monitor_size(0, &win_info->init_width, &win_info->init_heigth);
  win_info->img =
      mlx_new_image(win_info->window, round(win_info->init_width * 0.95),
                    round(win_info->init_heigth * 0.85));
  mlx_image_to_window(win_info->window, win_info->img,
                      round(win_info->init_width * 0.025),
                      round(win_info->init_heigth * 0.01));
  return (0);
}
