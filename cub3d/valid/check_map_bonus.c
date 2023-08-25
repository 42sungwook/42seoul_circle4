/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seulee2 <seulee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:49:22 by seulee2           #+#    #+#             */
/*   Updated: 2023/08/21 14:04:53 by seulee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub3d_bonus.h"

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

static int	check_ver(t_data *g, int j, int i, int x)
{
	while (i >= 0)
	{
		if (g->map_info->map[j][i] == ' ')
			return (1);
		if (g->map_info->map[j][i] == '1')
			break ;
		i--;
	}
	if (i < 0)
		return (1);
	i = x;
	while (g->map_info->map[j][i])
	{
		if (g->map_info->map[j][i] == ' ')
			return (1);
		if (g->map_info->map[j][i] == '1')
			break ;
		i++;
	}
	if (!g->map_info->map[j][i])
		return (1);
	return (0);
}

static int	check_hor(t_data *g, int j, int i, int y)
{
	while (j >= 0)
	{
		if (g->map_info->map[j][i] == ' ')
			return (1);
		if (g->map_info->map[j][i] == '1')
			break ;
		j--;
	}
	if (j < 0)
		return (1);
	j = y;
	while (g->map_info->map[j])
	{
		if (g->map_info->map[j][i] == ' ')
			return (1);
		if (g->map_info->map[j][i] == '1')
			break ;
		j++;
	}
	if (!g->map_info->map[j])
		return (1);
	return (0);
}

static int	valid_check(t_data *g, int j, int i)
{
	int		flag;
	char	**map;

	flag = 0;
	map = g->map_info->map;
	if (map[j][i] == '0' || map[j][i] == 'E' || map[j][i] == 'W' || \
		map[j][i] == 'S' || map[j][i] == 'N')
	{
		if (check_ver(g, j, i, i) || check_hor(g, j, i, j))
			return (1);
	}
	if (map[j][i] == 'E' || map[j][i] == 'W' || \
		map[j][i] == 'S' || map[j][i] == 'N')
	{
		if (flag == 1)
			return (1);
			flag = 1;
			g->map_info->character_x = i;
			g->map_info->character_y = j;
			g->map_info->character_angle = angle_set(map[j][i]);
	}
	return (0);
}

int	check_map(t_data *g)
{
	int		i;
	int		j;
	char	**map;

	map = g->map_info->map;
	g->map_info->character_angle = -1;
	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (valid_check(g, j, i))
				return (1);
			i++;
		}
		j++;
	}
	if (g->map_info->character_angle == -1)
		return (1);
	return (0);
}
