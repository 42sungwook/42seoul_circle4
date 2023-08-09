#include "../srcs/cub3d.h"
static void check_map(t_map	*map_info)
{
	;
}
static void init_map(t_data *g, char **av)
{
	g->imgs = (t_img *)malloc(sizeof(t_img) * IMG_CNT);
	g->map_info = malloc(sizeof(t_map));
	g->map_info->w = -1;
	g->map_info->h = 0;
	g->map_info->color_c.r = -1;
	g->map_info->color_f.r = -1;
	g->imgs[EAST].img = NULL;
	g->imgs[WEST].img = NULL;
	g->imgs[SOUTH].img = NULL;
	g->imgs[NORTH].img = NULL;
	save_map_info(g, av);
	check_map(g->map_info);
}

static void init_player(t_data *g)
{
	g->player = malloc(sizeof(t_player));
	g->player->x = 130;
	g->player->y = 110;
	g->player->walk_dir = STOP;
	g->player->turn_dir = 0;
	g->player->rotation_angle = 0;
}

void init_game(t_data *g, int ac, char **av)
{
	if (ac != 2)
		print_error("NEED ONE ARGUMENT\n");
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
		print_error("ARGUMENT NOT CUB FILE\n");
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "cub3d");
	init_map(g, av);
	init_player(g);
	init_img(g);
}
