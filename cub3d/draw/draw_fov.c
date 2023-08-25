/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seulee2 <seulee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:21:48 by seulee2           #+#    #+#             */
/*   Updated: 2023/08/25 15:35:53 by seulee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub3d.h"

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
			put_pixel_to_screen(g, j, i, ceil);
	}
	while (i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			put_pixel_to_screen(g, j, i, floor);
		++i;
	}
}

static int	check_valid_addr(t_data *g, int idx, int addr)
{
	if (addr < 0 || addr > g->imgs[idx].w * g->imgs[idx].h)
		return (0);
	return (1);
}

static void	draw_direction(t_data *g, int off_x, int off_y, int y)
{
	if (g->rays->was_hit_vertical)
	{
		if ((g->rays->is_ray_left) && check_valid_addr(g, WEST, \
			(g->imgs[WEST].w * (off_y + 1)) - off_x))
			put_pixel_to_screen(g, g->rays->strip_id, y, \
			g->imgs[WEST].addr[(g->imgs[WEST].w * \
			(off_y + 1)) - off_x]);
		else if (check_valid_addr(g, EAST, (g->imgs[EAST].w * \
			off_y) + off_x))
			put_pixel_to_screen(g, g->rays->strip_id, y, \
			g->imgs[EAST].addr[(g->imgs[EAST].w * off_y) + off_x]);
	}
	else
	{
		if ((g->rays->is_ray_down) && check_valid_addr(g, SOUTH, \
			(g->imgs[SOUTH].w * (off_y + 1)) - off_x))
			put_pixel_to_screen(g, g->rays->strip_id, y, \
			g->imgs[SOUTH].addr[(g->imgs[SOUTH].w * \
			(off_y + 1)) - off_x]);
		else if (check_valid_addr(g, NORTH, (g->imgs[NORTH].w * \
			off_y) + off_x))
			put_pixel_to_screen(g, g->rays->strip_id, y, \
			g->imgs[NORTH].addr[(g->imgs[NORTH].w * off_y) + off_x]);
	}
}

void	draw_texture(t_data *g, int wall_size, int wall_top_pixel, \
		int wall_bottom_pixel)
{
	int	tex_off_x;
	int	tex_off_y;
	int	distance_from_top;
	int	y;

	if (g->rays->was_hit_vertical)
		tex_off_x = (int)g->rays->wall_hit_y % TILE;
	else
		tex_off_x = (int)g->rays->wall_hit_x % TILE;
	tex_off_x *= 200 / TILE;
	y = wall_top_pixel;
	while (y < wall_bottom_pixel)
	{
		distance_from_top = y + (wall_size / 2) - (HEIGHT / 2);
		tex_off_y = distance_from_top * ((float)200.0 / wall_size);
		draw_direction(g, tex_off_x, tex_off_y, y);
		y++;
	}
}
