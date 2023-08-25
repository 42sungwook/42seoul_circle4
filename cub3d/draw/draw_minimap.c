/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seulee2 <seulee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:06:39 by seulee2           #+#    #+#             */
/*   Updated: 2023/08/21 14:05:24 by seulee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub3d.h"

static void	draw_ray_line(t_data *g, t_mini_line *line)
{
	while (1)
	{
		if (g->rays->x0 == g->rays->x1 && g->rays->y0 == g->rays->y1)
			break ;
		put_pixel_to_minimap(g, g->rays->x0, g->rays->y0, 0x00FF00FF);
		line->e2 = line->err;
		if (line->e2 > -line->dx)
		{
			line->err -= line->dy;
			g->rays->x0 += line->sx;
		}
		if (line->e2 < line->dy)
		{
			line->err += line->dx;
			g->rays->y0 += line->sy;
		}
	}
}

void	draw_line(t_data *g)
{
	t_mini_line	line;

	line.dx = abs(g->rays->x1 - g->rays->x0);
	line.dy = abs(g->rays->y1 - g->rays->y0);
	if (g->rays->x0 < g->rays->x1)
		line.sx = 1;
	else
		line.sx = -1;
	if (g->rays->y0 < g->rays->y1)
		line.sy = 1;
	else
		line.sy = -1;
	if (line.dx > line.dy)
		line.err = line.dx / 2;
	else
		line.err = -1 * line.dy / 2;
	draw_ray_line(g, &line);
}

void	draw_minimap(t_data *g)
{
	int	i;
	int	j;

	i = 0;
	while (g->map_info->map[i])
	{
		j = 0;
		while (g->map_info->map[i][j])
		{
			if (g->map_info->map[i][j] == '1')
				put_img_to_minimap(g, &g->imgs[M_WALL], j * TILE, i * TILE);
			else
				put_img_to_minimap(g, &g->imgs[M_PLAIN], j * TILE, i * TILE);
			j++;
		}
		i++;
	}
}

void	revert_minimap(t_data *g)
{
	int	i;
	int	j;

	i = 0;
	while (i < g->imgs[M_MAP].h)
	{
		j = 0;
		while (j < g->imgs[M_MAP].w)
		{
			if (g->imgs[M_MAP].addr[i * g->imgs[M_MAP].w + j] == \
			0x00FF00FF || g->imgs[M_MAP].addr[i * g->imgs[M_MAP].w + j] \
			== 0x9A2EFE)
				g->imgs[M_MAP].addr[i * g->imgs[M_MAP].w + j] = \
				0xFFFFFF;
			j++;
		}
		i++;
	}
}

void	minimap_define_xy(t_data *g, int *x, int *y)
{
	if (g->player->x + P_ERROR < M_WIDTH / 2)
		*x = 0;
	else if (g->player->x + P_ERROR > (g->map_info->w * TILE) - (M_WIDTH / 2))
		*x = (g->map_info->w * TILE) - M_WIDTH;
	else
		*x = g->player->x + P_ERROR - (M_WIDTH / 2);
	if (g->player->y + P_ERROR < M_HEIGHT / 2)
		*y = 0;
	else if (g->player->y + P_ERROR > (g->map_info->h * TILE) - (M_HEIGHT / 2))
		*y = (g->map_info->h * TILE) - M_HEIGHT;
	else
		*y = g->player->y + P_ERROR - (M_HEIGHT / 2);
}
