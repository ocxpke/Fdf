#include "fdf.h"

void swap_map(t_fdf_data *fdf_data) {
  t_window *win_info = fdf_data->win_info;
  char *full_name;
  int ok = 0;

  if (!win_info->map_dir)
    return;

  while (!ok) {
    win_info->act_file = readdir(win_info->map_dir);
    if (!win_info->act_file)
      win_info->map_dir = opendir("../test_maps");
    else if (win_info->act_file->d_type == 8)
      ok = 1;
  }

  full_name = ft_calloc(1, 13 + ft_strlen(win_info->act_file->d_name) + 1);
  ft_strlcat(full_name, "../test_maps/", 13 + 1);
  ft_strlcat(full_name, win_info->act_file->d_name,
             13 + ft_strlen(win_info->act_file->d_name) + 1);
  printf("%s %d\n", full_name, win_info->act_file->d_type);
  init_map_info(full_name, fdf_data->map_info);
  free_back_coord(fdf_data->dis_points);
  fdf_data->dis_points = init_points_matrix(full_name, fdf_data->map_info);
  reset_model_values(fdf_data->map_info->model_values);
  reset_user_values(fdf_data);
  fdf_data->map_info->model_values->max_z = fdf_data->map_info->highest_point;
  fdf_data->map_info->model_values->min_z = fdf_data->map_info->lowest_point;
  set_window_title(full_name, fdf_data->win_info);
  reset_user_view(win_info);
  calculate_main_projection(fdf_data->win_info, fdf_data->map_info,
                            fdf_data->dis_points);
  display_main_projection(fdf_data->win_info, fdf_data->map_info,
                          fdf_data->dis_points);
  free(full_name);
}
