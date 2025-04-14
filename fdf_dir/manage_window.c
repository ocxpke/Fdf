/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:46:16 by jose-ara          #+#    #+#             */
/*   Updated: 2025/04/14 19:39:54 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	take_window_data(t_window *win_info)
{
	GLFWmonitor	*monitor;

	monitor = glfwGetPrimaryMonitor();
	if (!monitor)
		return (perror("Error monitor"), free(win_info), exit(EXIT_FAILURE));
	glfwGetMonitorWorkarea(monitor, NULL, NULL, &(win_info->init_width),
		&(win_info->init_heigth));
	printf("%d, %d\n", win_info->init_width, win_info->init_heigth);
}

t_window	*init_window_components(void)
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
	reset_user_view(win_info);
	return (win_info);
}
