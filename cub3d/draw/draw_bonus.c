/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seulee2 <seulee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:17:08 by seulee2           #+#    #+#             */
/*   Updated: 2023/08/16 14:55:34 by seulee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub3d_bonus.h"

void	put_pixel_to_screen(t_data *g, int x, int y, int color)
{
	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
		return ;
	g->imgs[SCREEN].addr[y * g->imgs[SCREEN].w + x] = color;
}

void	put_img_to_screen(t_data *g, t_img *imgs, int x, int y)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	if (x > WIDTH || y > WIDTH || x < 0 || y < 0)
		return ;
	while (i < imgs->h)
	{
		j = 0;
		while (j < imgs->w)
		{
			color = imgs->addr[i * imgs->w + j];
			if (color != 0)
				put_pixel_to_screen(g, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	put_pixel_to_minimap(t_data *g, int x, int y, int color)
{
	if (x > g->map_info->w * TILE || y > g->map_info->h * TILE || \
		x < 0 || y < 0)
		return ;
	g->imgs[M_MAP].addr[y * g->imgs[M_MAP].w + x] = color;
}

void	put_img_to_minimap(t_data *g, t_img *imgs, int x, int y)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < imgs->h)
	{
		j = 0;
		while (j < imgs->w)
		{
			color = imgs->addr[i * imgs->w + j];
			if (color != 0)
				put_pixel_to_minimap(g, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	put_minimap_to_screen(t_data *g)
{
	int	x;
	int	y;
	int	i;
	int	j;
	int	color_idx;

	i = -1;
	minimap_define_xy(g, &x, &y);
	while (++i < M_HEIGHT / 4)
	{
		j = -1;
		while (++j < M_WIDTH / 4)
		{
			color_idx = (y + i * 4) * g->map_info->w * TILE + x + j * 4;
			if (color_idx < 0 || color_idx > \
				g->imgs[M_MAP].w * g->imgs[M_MAP].h)
				put_pixel_to_screen(g, j, i, 0x000000);
			else
				put_pixel_to_screen(g, j, i, g->imgs[M_MAP].addr[color_idx]);
		}
	}
}
