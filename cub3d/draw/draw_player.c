/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_miniplayer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seulee2 <seulee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:09:05 by seulee2           #+#    #+#             */
/*   Updated: 2023/08/14 19:19:19 by seulee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub3d.h"

void	draw_player(t_data *g)
{
	int	new_x;
	int	new_y;

	if (g->player->turn_dir != 0)
		g->player->rotation_angle += \
		g->player->turn_dir * (PI / 180.0) * ROT_SPEED;
	new_x = g->player->x + (int)(cos(g->player->rotation_angle + \
			(PI / 180.0) * 90.0 * g->player->walk_dir) * MOVE_SPEED);
	new_y = g->player->y + (int)(sin(g->player->rotation_angle + \
			(PI / 180.0) * 90.0 * g->player->walk_dir) * MOVE_SPEED);
	if (g->player->walk_dir != STOP && !map_has_wall_at(g, new_x, new_y))
	{
		g->player->x = new_x;
		g->player->y = new_y;
	}
}
