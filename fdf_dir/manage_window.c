/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:46:16 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/21 23:05:13 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief	Displays the image with all the instructions needed for the user
 *
 * @param win_info	The struct with all our window information
 *
 * @return	Void
 */
static void	display_help(t_window *win_info)
{
	win_info->leyend_texture = mlx_load_png("./img/leyenda.png");
	win_info->leyend_img = mlx_texture_to_image(win_info->window,
			win_info->leyend_texture);
	mlx_image_to_window(win_info->window, win_info->leyend_img,
		win_info->init_width - 501, 0);
}

/**
 * @brief	Takes the monitor workarea dimensions and the sets
 * those values on our map_info
 *
 * @param win_info	The struct with all our window information
 *
 * @return	Void
 */
static void	take_window_data(t_window *win_info)
{
	GLFWmonitor	*monitor;

	monitor = glfwGetPrimaryMonitor();
	if (!monitor)
		return (perror("Error monitor"), free(win_info), exit(EXIT_FAILURE));
	glfwGetMonitorWorkarea(monitor, NULL, NULL, &(win_info->init_width),
		&(win_info->init_heigth));
	printf("%d, %d\n", win_info->init_width, win_info->init_heigth);
}

t_window	*init_window_components(char *argv)
{
	t_window	*win_info;

	win_info = (t_window *)ft_calloc(1, sizeof(t_window));
	if (!win_info)
		return (perror("Error with init t_window"), NULL);
	mlx_set_setting(MLX_MAXIMIZED, 1);
	win_info->window = mlx_init(500, 500, "Fdf", true);
	take_window_data(win_info);
	win_info->img = mlx_new_image(win_info->window, round(win_info->init_width
				* 0.95), round(win_info->init_heigth * 0.95));
	mlx_image_to_window(win_info->window, win_info->img, win_info->init_width
		* 0.025, win_info->init_heigth * 0.005);
	display_help(win_info);
	mlx_put_string(win_info->window, argv, win_info->init_width - 480, 10);
	mlx_put_string(win_info->window, "Press 'o' to show/hide help | ESC to end",
		win_info->init_width - 480, 40);
	reset_user_view(win_info);
	return (win_info);
}
