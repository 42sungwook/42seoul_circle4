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
	i = 0;
	while (i < HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
		{
			put_pixel_to_screen(g, j, i, floor);
			++j;
		}
		++i;
	}
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			put_pixel_to_screen(g, j, i, ceil);
			++j;
		}
		++i;
	}
}

void	draw_texture(t_data *g, int wall_size, int wall_top_pixel, \
		int wall_bottom_pixel)
{
	int	texture_offset_x;
	int	texture_offset_y;
	int	distance_from_top;
	int	y;

	if (g->rays->was_hit_vertical)
		texture_offset_x = (int)g->rays->wall_hit_y % TILE;
	else
		texture_offset_x = (int)g->rays->wall_hit_x % TILE;
	texture_offset_x *= 200 / TILE;
	y = wall_top_pixel;
	while (y < wall_bottom_pixel)
	{
		distance_from_top = y + (wall_size / 2) - (HEIGHT / 2);
		texture_offset_y = distance_from_top * ((float)200.0 / wall_size);
		if (g->rays->was_hit_vertical)
		{
			if ((g->rays->is_ray_left))
				put_pixel_to_screen(g, g->rays->strip_id, y, \
				g->imgs[WEST].addr[(g->imgs[WEST].w * \
				(texture_offset_y + 1)) - texture_offset_x]);
			else
				put_pixel_to_screen(g, g->rays->strip_id, y, \
				g->imgs[EAST].addr[(g->imgs[EAST].w * \
				texture_offset_y) + texture_offset_x]);
		}
		else
		{
			if ((g->rays->is_ray_down))
				put_pixel_to_screen(g, g->rays->strip_id, y, \
				g->imgs[SOUTH].addr[(g->imgs[SOUTH].w * \
				(texture_offset_y + 1)) - texture_offset_x]);
			else
				put_pixel_to_screen(g, g->rays->strip_id, y, \
				g->imgs[NORTH].addr[(g->imgs[NORTH].w * \
				texture_offset_y) + texture_offset_x]);
		}
		y++;
	}
}