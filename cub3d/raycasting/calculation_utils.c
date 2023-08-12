#include "../srcs/cub3d.h"

int	map_has_wall_at(t_data *g, double x, double y)
{
	int	map_grid_idx_x;
	int	map_grid_idx_y;

	map_grid_idx_x = floor(x / TILE);
	map_grid_idx_y = floor(y / TILE);
	if (map_grid_idx_x < 0 || map_grid_idx_x > g->map_info->w || \
	map_grid_idx_y < 0 || map_grid_idx_y > g->map_info->h)
		return (FALSE);
	if (g->map_info->map[map_grid_idx_y][map_grid_idx_x] == '1')
		return (TRUE);
	return (FALSE);
}

double	normalize_angle(double angle)
{
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	while (angle < 0)
		angle += 2 * PI;
	return (angle);
}

double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	ray_dir(t_data *g, double ray_angle)
{
	ray_angle = normalize_angle(ray_angle);
	if (ray_angle > 0 && ray_angle < PI)
		g->rays->is_ray_down = TRUE;
	else
		g->rays->is_ray_down = FALSE;
	g->rays->is_ray_up = !g->rays->is_ray_down;
	if (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI)
		g->rays->is_ray_right = TRUE;
	else
		g->rays->is_ray_right = FALSE;
	g->rays->is_ray_left = !g->rays->is_ray_right;
}

void	compare_hv_distance(t_data *g, double ray_angle)
{
	if (g->rays->horz_wall_hit)
		g->rays->horz_hit_distance = distanceBetweenPoints((g->player->x \
		+ P_ERROR), (g->player->y + P_ERROR), g->rays->horz_wall_hit_x, \
		g->rays->horz_wall_hit_y);
	else
		g->rays->horz_hit_distance = FLT_MAX;
	if (g->rays->vert_wall_hit)
		g->rays->vert_hit_distance = distanceBetweenPoints((g->player->x \
		+ P_ERROR), (g->player->y + P_ERROR), g->rays->vert_wall_hit_x, \
		g->rays->vert_wall_hit_y);
	else
		g->rays->vert_hit_distance = FLT_MAX;
	g->rays->horz_hit_distance *= cos(ray_angle - g->player->rotation_angle);
	g->rays->vert_hit_distance *= cos(ray_angle - g->player->rotation_angle);
	if (g->rays->vert_hit_distance < g->rays->horz_hit_distance)
	{
		g->rays->distance = g->rays->vert_hit_distance;
		g->rays->wall_hit_x = g->rays->vert_wall_hit_x;
		g->rays->wall_hit_y = g->rays->vert_wall_hit_y;
		g->rays->was_hit_vertical = TRUE;
	}
	else
	{
		g->rays->distance = g->rays->horz_hit_distance;
		g->rays->wall_hit_x = g->rays->horz_wall_hit_x;
		g->rays->wall_hit_y = g->rays->horz_wall_hit_y;
		g->rays->was_hit_vertical = FALSE;
	}
}