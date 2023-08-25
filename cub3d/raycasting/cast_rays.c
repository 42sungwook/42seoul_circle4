/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seulee2 <seulee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:28:46 by seulee2           #+#    #+#             */
/*   Updated: 2023/08/21 14:04:26 by seulee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub3d.h"

static int	find_wall_at(t_data *g, int is_horz)
{
	while (g->rays->xintercept >= 0 && g->rays->xintercept < \
	g->map_info->w * TILE && g->rays->yintercept >= 0 && \
	g->rays->yintercept < g->map_info->h * TILE)
	{
		if (is_horz == TRUE)
		{
			if (map_has_wall_at(g, g->rays->xintercept, \
			g->rays->yintercept - g->rays->is_ray_up))
				return (1);
		}
		else
		{
			if (map_has_wall_at(g, g->rays->xintercept - \
			g->rays->is_ray_left, g->rays->yintercept))
				return (1);
		}
		g->rays->xintercept += g->rays->xstep;
		g->rays->yintercept += g->rays->ystep;
	}
	return (0);
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
	if (find_wall_at(g, TRUE))
	{
		g->rays->horz_wall_hit_x = g->rays->xintercept;
		g->rays->horz_wall_hit_y = g->rays->yintercept;
		g->rays->horz_wall_hit = TRUE;
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
	if ((g->rays->is_ray_up && g->rays->ystep > 0) || \
		(g->rays->is_ray_down && g->rays->ystep < 0))
		g->rays->ystep *= -1;
	if (find_wall_at(g, FALSE))
	{
		g->rays->vert_wall_hit_x = g->rays->xintercept;
		g->rays->vert_wall_hit_y = g->rays->yintercept;
		g->rays->vert_wall_hit = TRUE;
	}
}

static void	cast_ray(t_data *g, double ray_angle)
{
	ray_dir(g, ray_angle);
	cal_hor_ray(g, ray_angle);
	cal_ver_ray(g, ray_angle);
	compare_hv_distance(g, ray_angle);
	shot_ray(g);
	g->rays->x0 = g->player->x + P_ERROR;
	g->rays->y0 = g->player->y + P_ERROR;
	g->rays->x1 = g->rays->wall_hit_x;
	g->rays->y1 = g->rays->wall_hit_y;
	draw_line(g);
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
