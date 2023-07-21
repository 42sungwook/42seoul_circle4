#include "cub3d.h"

void init_img(t_data *g)
{
	g->imgs = (t_img *)malloc(sizeof(t_img) * IMG_CNT);
	g->imgs[0].img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	g->imgs[0].w = WIDTH;
	g->imgs[0].h = HEIGHT;
	g->imgs[1].img = mlx_xpm_file_to_image(g->mlx, "./asset/tile00.xpm", &g->imgs[1].w, &g->imgs[1].h);
	g->imgs[2].img = mlx_xpm_file_to_image(g->mlx, "./asset/circle.xpm", &g->imgs[2].w, &g->imgs[2].h);
	g->imgs[3].img = mlx_xpm_file_to_image(g->mlx, "./asset/head.xpm", &g->imgs[3].w, &g->imgs[3].h);
	g->imgs[4].img = mlx_xpm_file_to_image(g->mlx, "./asset/tile01.xpm", &g->imgs[4].w, &g->imgs[4].h);
	g->imgs[0].addr = (int *)mlx_get_data_addr(g->imgs[0].img, &g->imgs[0].bpp, \
																			&g->imgs[0].line_len, &g->imgs[0].endian);
	g->imgs[1].addr = (int *)mlx_get_data_addr(g->imgs[1].img, &g->imgs[1].bpp, \
																			&g->imgs[1].line_len, &g->imgs[1].endian);
	g->imgs[2].addr = (int *)mlx_get_data_addr(g->imgs[2].img, &g->imgs[2].bpp, \
																			&g->imgs[2].line_len, &g->imgs[2].endian);
	g->imgs[3].addr = (int *)mlx_get_data_addr(g->imgs[3].img, &g->imgs[3].bpp, \
																			&g->imgs[3].line_len, &g->imgs[3].endian);
	g->imgs[4].addr = (int *)mlx_get_data_addr(g->imgs[4].img, &g->imgs[4].bpp, \
																			&g->imgs[4].line_len, &g->imgs[4].endian);
}
