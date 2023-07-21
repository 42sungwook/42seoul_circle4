#include "../cub3d.h"

void init_base(t_data *g)
{
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "cub3d");
	g->x = 40;
	g->y = 40;
	g->walk_dir = STOP;
	g->turn_dir = 0;
	g->rotation_angle = 0;
}
