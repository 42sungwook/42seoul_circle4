/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seulee2 <seulee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:21:48 by seulee2           #+#    #+#             */
/*   Updated: 2023/08/14 20:51:06 by seulee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub3d_bonus.h"

void	draw_bg(t_data *g)
{
	int	i;
	int	j;
	int	floor;
	int	ceil;

	floor = g->map_info->color_f.r << 16 | g->map_info->color_f.g << 8 | \
	g->map_info->color_f.b;
	ceil = g->map_info->color_c.r << 16 | g->map_info->color_c.r << 8 | \
	g->map_info->color_c.r;
	i = -1;
	while (++i < HEIGHT / 2)
	{
		j = -1;
		while (++j < WIDTH)
			put_pixel_to_screen(g, j, i, floor);
	}
	while (i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			put_pixel_to_screen(g, j, i, ceil);
		++i;
	}
}

static void	draw_direction(t_data *g, int offset_x, int offset_y, int y)
{
	if (g->rays->was_hit_vertical)
	{
		if ((g->rays->is_ray_left))
			put_pixel_to_screen(g, g->rays->strip_id, y, \
			g->imgs[WEST].addr[(g->imgs[WEST].w * \
			(offset_y + 1)) - offset_x]);
		else
			put_pixel_to_screen(g, g->rays->strip_id, y, \
			g->imgs[EAST].addr[(g->imgs[EAST].w * \
			offset_y) + offset_x]);
	}
	else
	{
		if ((g->rays->is_ray_down))
			put_pixel_to_screen(g, g->rays->strip_id, y, \
			g->imgs[SOUTH].addr[(g->imgs[SOUTH].w * \
			(offset_y + 1)) - offset_x]);
		else
			put_pixel_to_screen(g, g->rays->strip_id, y, \
			g->imgs[NORTH].addr[(g->imgs[NORTH].w * \
			offset_y) + offset_x]);
	}
}

void	draw_texture(t_data *g, int wall_size, int wall_top_pixel, \
		int wall_bottom_pixel)
{
	int	tex_offset_x;
	int	tex_offset_y;
	int	distance_from_top;
	int	y;

	if (g->rays->was_hit_vertical)
		tex_offset_x = (int)g->rays->wall_hit_y % TILE;
	else
		tex_offset_x = (int)g->rays->wall_hit_x % TILE;
	tex_offset_x *= 200 / TILE;
	y = wall_top_pixel;
	while (y < wall_bottom_pixel)
	{
		distance_from_top = y + (wall_size / 2) - (HEIGHT / 2);
		tex_offset_y = distance_from_top * ((float)200.0 / wall_size);
		draw_direction(g, tex_offset_x, tex_offset_y, y);
		y++;
	}
}
