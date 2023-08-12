#include "../srcs/cub3d.h"


void	draw_line(t_data *g, int color)
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
	while (1)
	{
		put_pixel_to_minimap(g, g->rays->x0, g->rays->y0, color);
		if (g->rays->x0 == g->rays->x1 && g->rays->y0 == g->rays->y1)
			break ;
		line.e2 = line.err;
		if (line.e2 > -line.dx)
		{
			line.err -= line.dy;
			g->rays->x0 += line.sx;
		}
		if (line.e2 < line.dy)
		{
			line.err += line.dx;
			g->rays->y0 += line.sy;
		}
	}
}

void	draw_minimap(t_data *g)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (g->map_info->map[i])
	{
		j = 0;
		while (g->map_info->map[i][j])
		{
			if (g->map_info->map[i][j] == '1')
				put_img_to_minimap(g, &g->imgs[MINI_WALL], j * TILE, i * TILE);
			else
				put_img_to_minimap(g, &g->imgs[MINI_PLAIN], j * TILE, i * TILE);
			j++;
		}
		i++;
	}
}

void revert_minimap(t_data *g)
{

}