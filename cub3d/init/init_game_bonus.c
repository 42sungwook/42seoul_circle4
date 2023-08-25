/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seulee2 <seulee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:33:23 by seulee2           #+#    #+#             */
/*   Updated: 2023/08/25 12:56:25 by seulee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub3d_bonus.h"

static void	init_map(t_data *g, char **av)
{
	g->imgs = (t_img *)malloc(sizeof(t_img) * IMG_CNT);
	g->map_info = malloc(sizeof(t_map));
	g->map_info->w = -1;
	g->map_info->h = 0;
	g->map_info->color_c.r = -1;
	g->map_info->color_f.r = -1;
	g->map_info->mini_ray = 1;
	g->imgs[EAST].img = NULL;
	g->imgs[WEST].img = NULL;
	g->imgs[SOUTH].img = NULL;
	g->imgs[NORTH].img = NULL;
	save_map_info(g, av);
	if (check_map(g))
		print_error("INVALID MAP");
}

static void	init_player(t_data *g)
{
	g->player = malloc(sizeof(t_player));
	g->player->x = TILE * g->map_info->character_x + TILE / 2;
	g->player->y = TILE * g->map_info->character_y + TILE / 2;
	g->player->walk_dir = STOP;
	g->player->turn_dir = 0;
	g->player->rotation_angle = g->map_info->character_angle;
	g->player->mouse_mode = 0;
}

void	init_game(t_data *g, int ac, char **av)
{
	if (ac != 2)
		print_error("NEED ONE ARGUMENT");
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
		print_error("ARGUMENT NOT CUB FILE");
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "cub3d");
	init_map(g, av);
	init_player(g);
	init_img(g);
}