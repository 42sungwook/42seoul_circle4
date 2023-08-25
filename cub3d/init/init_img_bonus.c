/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seulee2 <seulee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:16:49 by seulee2           #+#    #+#             */
/*   Updated: 2023/08/16 14:37:58 by seulee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub3d_bonus.h"

void	check_file(t_data *g, char *str, int idx)
{
	if (open(str, O_RDONLY) == -1)
		print_error("FILE OPEN");
	g->imgs[idx].img = mlx_xpm_file_to_image(g->mlx, str, \
		&g->imgs[idx].w, &g->imgs[idx].h);
}

static void	init_addr(t_data *g)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		g->imgs[i].addr = (int *)mlx_get_data_addr(g->imgs[i].img, \
		&g->imgs[i].bpp, &g->imgs[i].line_len, &g->imgs[i].endian);
		i++;
	}
}

static void	init_mini_player(t_data *g)
{
	int	i;
	int	j;

	i = 0;
	while (i < g->imgs[M_PLAYER].h)
	{
		j = 0;
		while (j < g->imgs[M_PLAYER].w)
		{
			g->imgs[M_PLAYER].addr[i * g->imgs[M_PLAYER].w + j] = \
			0x9A2EFE;
			j++;
		}
		i++;
	}
}

void	init_img(t_data *g)
{
	g->imgs[SCREEN].img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	g->imgs[SCREEN].w = WIDTH;
	g->imgs[SCREEN].h = HEIGHT;
	g->imgs[M_MAP].img = mlx_new_image(g->mlx, (g->map_info->w) * TILE, \
	(g->map_info->h) * TILE);
	g->imgs[M_MAP].w = g->map_info->w * TILE;
	g->imgs[M_MAP].h = g->map_info->h * TILE;
	g->imgs[M_PLAYER].img = mlx_new_image(g->mlx, 7, 7);
	g->imgs[M_PLAYER].w = 7;
	g->imgs[M_PLAYER].h = 7;
	check_file(g, "./asset/tile00.xpm", M_WALL);
	check_file(g, "./asset/tile01.xpm", M_PLAIN);
	init_addr(g);
	init_mini_player(g);
}
