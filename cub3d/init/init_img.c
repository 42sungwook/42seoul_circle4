#include "../srcs/cub3d.h"

void init_img(t_data *g)
{
	//g->imgs = (t_img *)malloc(sizeof(t_img) * IMG_CNT);
	g->imgs[SCREEN].img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	g->imgs[SCREEN].w = WIDTH;
	g->imgs[SCREEN].h = HEIGHT;
	g->imgs[MINI_MAP].img = mlx_new_image(g->mlx, (g->map_info->w) * TILE, (g->map_info->h) * TILE);
	g->imgs[MINI_MAP].w = g->map_info->w * TILE;
	g->imgs[MINI_MAP].h = g->map_info->h * TILE;
	g->imgs[MINI_WALL].img = mlx_xpm_file_to_image(g->mlx, "./asset/tile00.xpm", &g->imgs[MINI_WALL].w, &g->imgs[MINI_WALL].h);
	g->imgs[MINI_PLAIN].img = mlx_xpm_file_to_image(g->mlx, "./asset/tile01.xpm", &g->imgs[MINI_PLAIN].w, &g->imgs[MINI_PLAIN].h);
	g->imgs[MINI_PLAYER].img = mlx_xpm_file_to_image(g->mlx, "./asset/circle.xpm", &g->imgs[MINI_PLAYER].w, &g->imgs[MINI_PLAYER].h);
	g->imgs[SCREEN].addr = (int *)mlx_get_data_addr(g->imgs[SCREEN].img, &g->imgs[SCREEN].bpp, \
																			&g->imgs[SCREEN].line_len, &g->imgs[SCREEN].endian);
	g->imgs[MINI_MAP].addr = (int *)mlx_get_data_addr(g->imgs[MINI_MAP].img, &g->imgs[MINI_MAP].bpp, \
																			&g->imgs[MINI_MAP].line_len, &g->imgs[MINI_MAP].endian);
	g->imgs[MINI_WALL].addr = (int *)mlx_get_data_addr(g->imgs[MINI_WALL].img, &g->imgs[MINI_WALL].bpp, \
																			&g->imgs[MINI_WALL].line_len, &g->imgs[MINI_WALL].endian);
	g->imgs[MINI_PLAIN].addr = (int *)mlx_get_data_addr(g->imgs[MINI_PLAIN].img, &g->imgs[MINI_PLAIN].bpp, \
																			&g->imgs[MINI_PLAIN].line_len, &g->imgs[MINI_PLAIN].endian);
	g->imgs[MINI_PLAYER].addr = (int *)mlx_get_data_addr(g->imgs[MINI_PLAYER].img, &g->imgs[MINI_PLAYER].bpp, \
																			&g->imgs[MINI_PLAYER].line_len, &g->imgs[MINI_PLAYER].endian);
	g->imgs[SOUTH].addr = (int *)mlx_get_data_addr(g->imgs[SOUTH].img, &g->imgs[SOUTH].bpp, \
																			&g->imgs[SOUTH].line_len, &g->imgs[SOUTH].endian);
	g->imgs[NORTH].addr = (int *)mlx_get_data_addr(g->imgs[NORTH].img, &g->imgs[NORTH].bpp, \
																			&g->imgs[NORTH].line_len, &g->imgs[NORTH].endian);																																						
	g->imgs[EAST].addr = (int *)mlx_get_data_addr(g->imgs[EAST].img, &g->imgs[EAST].bpp, \
																			&g->imgs[EAST].line_len, &g->imgs[EAST].endian);
	g->imgs[WEST].addr = (int *)mlx_get_data_addr(g->imgs[WEST].img, &g->imgs[WEST].bpp, \
																			&g->imgs[WEST].line_len, &g->imgs[WEST].endian);
}
