/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seulee2 <seulee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:33:23 by seulee2           #+#    #+#             */
/*   Updated: 2023/08/09 18:41:01 by seulee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub3d.h"

static double	angle_set(char c)
{
	if (c == 'E')
		return (0);
	else if (c == 'W')
		return (PI);
	else if (c == 'S')
		return (PI / 2);
	else
		return (PI + (PI / 2));
}
static void check_map(t_data *g)
{
	int	i;
	int	j;
	int	flag;
	char **map;

	map = g->map_info->map;
	flag = 0;
	j = 0;
	while (j < g->map_info->h)
	{
		i = 0;
		while ( i < g->map_info->w)
		{
			if (map[j][i] == 'E' || map[j][i] == 'W' || map[j][i] == 'S' || map[j][i] == 'N')
			{
				if (flag != 0)
					print_error("Error_currupted map");
				else
				{
					flag = 1;
					g->map_info->character_x = i;
					g->map_info->character_y = j;
					g->map_info->character_angle = angle_set(map[j][i]);
					
				}
			}
			i++;
		}
		j++;
	}

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
	check_map(g);
}

static void init_player(t_data *g)
{
	g->player = malloc(sizeof(t_player));
	g->player->x = MINI_TILE * g->map_info->character_x + MINI_TILE / 2;
	g->player->y = MINI_TILE * g->map_info->character_y + MINI_TILE / 2;
	g->player->walk_dir = STOP;
	g->player->turn_dir = 0;
	g->player->rotation_angle = g->map_info->character_angle;
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
