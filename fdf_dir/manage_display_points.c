/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_display_points.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ara < jose-ara@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:09:27 by jose-ara          #+#    #+#             */
/*   Updated: 2025/05/02 18:54:46 by jose-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coordinates **free_back_coord(t_coordinates **points_matrix) {
  int i;

  i = 0;
  while (points_matrix[i]) {
    free(points_matrix[i]);
    i++;
  }
  free(points_matrix);
  return (NULL);
}

void add_to_matrix(t_coordinates **p_matrix, char *line, int i,
                   t_map_info *map_info) {
  int j;
  char **splitted;

  j = 0;
  splitted = ft_split(line, ' ');
  while ((j < map_info->y_length) && splitted[j]) {
    p_matrix[i][j].x = i;
    p_matrix[i][j].x_p = i;
    p_matrix[i][j].x_o = i;
    p_matrix[i][j].y = j;
    p_matrix[i][j].y_p = j;
    p_matrix[i][j].y_o = j;
    p_matrix[i][j].z = ft_atoi(splitted[j]);
    p_matrix[i][j].z_p = p_matrix[i][j].z;
    p_matrix[i][j].z_o = p_matrix[i][j].z;
    if (p_matrix[i][j].z > map_info->highest_point)
      map_info->highest_point = p_matrix[i][j].z;
    else if (p_matrix[i][j].z < map_info->lowest_point)
      map_info->lowest_point = p_matrix[i][j].z;
    j++;
  }
  free_back_splitted(splitted);
}

void fill_points_matrix(char *file_in, t_coordinates **p_matrix,
                        t_map_info *map_info) {
  int fd;
  int i;
  char *line;

  i = 0;
  fd = open(file_in, O_RDONLY);
  if (fd == -1)
    exit(EXIT_FAILURE);
  line = get_next_line(fd);
  while ((i < map_info->x_length) && line) {
    printf("%d%%\n", (int)(((i * 1.0) / (map_info->x_length)) * 100));
    add_to_matrix(p_matrix, line, i, map_info);
    free(line);
    line = get_next_line(fd);
    i++;
  }
  close(fd);
}

t_coordinates **init_points_matrix(char *file_in, t_map_info *map_info) {
  t_coordinates **points_matrix;
  int i;

  i = 0;
  points_matrix = (t_coordinates **)ft_calloc(map_info->x_length + 1,
                                              sizeof(t_coordinates *));
  if (!points_matrix)
    return (perror("Error v1 matrix"), NULL);
  while (i < map_info->x_length) {
    points_matrix[i] = (t_coordinates *)ft_calloc(map_info->y_length + 1,
                                                  sizeof(t_coordinates));
    if (!points_matrix[i])
      return (perror("Error v2 matrix"), free_back_coord(points_matrix));
    i++;
  }
  fill_points_matrix(file_in, points_matrix, map_info);
  write(1, "Map read points allocated\n", 27);
  return (points_matrix);
}
