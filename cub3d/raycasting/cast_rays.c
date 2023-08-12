#include "../srcs/cub3d.h"

static void	shot_ray(t_data *g, int strip_id)
{
	double	wall_size;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	double	put_start;

	wall_size = HEIGHT / g->rays->distance;
	wall_size *= 60;
	wall_top_pixel = (HEIGHT / 2) - (wall_size / 2);
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	wall_bottom_pixel = (HEIGHT / 2) + (wall_size / 2);
	if (wall_bottom_pixel > HEIGHT)
		wall_bottom_pixel = HEIGHT;
	put_start = HEIGHT / 2 - wall_size / 2 - 2;
	draw_texture(g, wall_size, wall_top_pixel, wall_bottom_pixel);
}

static void	cal_hor_ray(t_data *g, double ray_angle)
{
	if (g->rays->is_ray_down)
		g->rays->yintercept = floor((g->player->y + P_ERROR) / \
		TILE) * TILE + TILE;
	else
		g->rays->yintercept = floor((g->player->y + P_ERROR) / TILE) * TILE;
	g->rays->xintercept = (g->player->x + P_ERROR) + \
	(g->rays->yintercept - (g->player->y + P_ERROR)) / tan(ray_angle);
		g->rays->ystep = TILE;
	if (g->rays->is_ray_up)
		g->rays->ystep *= -1;
	g->rays->xstep = TILE / tan(ray_angle);
	if (g->rays->is_ray_left && g->rays->xstep > 0)
		g->rays->xstep *= -1;
	if (g->rays->is_ray_right && g->rays->xstep < 0)
		g->rays->xstep *= -1;
	while (g->rays->xintercept >= 0 && g->rays->xintercept < \
	g->map_info->w * TILE && g->rays->yintercept >= 0 && \
	g->rays->yintercept < g->map_info->h * TILE)
	{
		if (map_has_wall_at(g, g->rays->xintercept, \
		g->rays->yintercept - g->rays->is_ray_up))
		{
			g->rays->horz_wall_hit_x = g->rays->xintercept;
			g->rays->horz_wall_hit_y = g->rays->yintercept;
			g->rays->horz_wall_hit = TRUE;
			break ;
		}
		else
		{
			g->rays->xintercept += g->rays->xstep;
			g->rays->yintercept += g->rays->ystep;
		}
	}
}

static void	cal_ver_ray(t_data *g, double ray_angle)
{
	if (g->rays->is_ray_right)
		g->rays->xintercept = floor((g->player->x + P_ERROR) / \
		TILE) * TILE + TILE;
	else
		g->rays->xintercept = floor((g->player->x + P_ERROR) / TILE) * TILE;
	g->rays->yintercept = (g->player->y + P_ERROR) + \
	(g->rays->xintercept - (g->player->x + P_ERROR)) * tan(ray_angle);
	g->rays->xstep = TILE;
	if (g->rays->is_ray_left)
		g->rays->xstep *= -1;
	g->rays->ystep = TILE * tan(ray_angle);
	if (g->rays->is_ray_up && g->rays->ystep > 0)
		g->rays->ystep *= -1;
	if (g->rays->is_ray_down && g->rays->ystep < 0)
		g->rays->ystep *= -1;
	while (g->rays->xintercept >= 0 && g->rays->xintercept < \
	g->map_info->w * TILE && g->rays->yintercept >= 0 && \
	g->rays->yintercept < g->map_info->h * TILE)
	{
		if (map_has_wall_at(g, g->rays->xintercept - \
		g->rays->is_ray_left, g->rays->yintercept))
		{
			g->rays->vert_wall_hit_x = g->rays->xintercept;
			g->rays->vert_wall_hit_y = g->rays->yintercept;
			g->rays->vert_wall_hit = TRUE;
			break ;
		}
		else
		{
			g->rays->xintercept += g->rays->xstep;
			g->rays->yintercept += g->rays->ystep;
		}
	}
}

static void	cast_ray(t_data *g, double ray_angle)
{
	ray_dir(g, ray_angle);
	cal_hor_ray(g, ray_angle);
	cal_ver_ray(g, ray_angle);
	compare_hv_distance(g, ray_angle);
	shot_ray(g, g->rays->strip_id);
	draw_line(g, (g->player->x + P_ERROR), (g->player->y + P_ERROR), \
	g->rays->wall_hit_x, g->rays->wall_hit_y);
}

void	cast_rays(t_data *g)
{
	double	fov_angle;
	double	ray_angle;
	int		col;

	g->rays = (t_ray *)malloc(sizeof(t_ray));
	fov_angle = (50 * (PI / 180));
	ray_angle = g->player->rotation_angle - (fov_angle / 2);
	draw_bg(g);
	col = 0;
	while (col < WIDTH)
	{
		ft_memset(g->rays, 0, sizeof(t_ray));
		ray_angle += fov_angle / WIDTH;
		g->rays->strip_id = col;
		cast_ray(g, ray_angle);
		col++;
	}
	free(g->rays);
}