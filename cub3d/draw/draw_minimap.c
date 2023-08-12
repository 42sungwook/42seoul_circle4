#include "../srcs/cub3d.h"


void	draw_line(t_data *g, int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while (1)
	{
		put_pixel_to_minimap(g, x0, y0, 0x00FF00FF);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void draw_minimap(t_data *g)
{
	int i;
	int j;
	int tile_x;
	int tile_y;
	int tile_color;

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



//플레이어 주변맵을 확인
//주변 기준으로 끝이 나온다면 처리-> 그냥 맵의 앞부분부터 그려야함