/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seulee2 <seulee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:15:53 by seulee2           #+#    #+#             */
/*   Updated: 2023/08/14 18:15:54 by seulee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int	handle_key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	else if (keycode == W)
		data->player->walk_dir = WALKFORWARD;
	else if (keycode == S)
		data->player->walk_dir = WALKBACKWARD;
	else if (keycode == A)
		data->player->walk_dir = WALKLEFT;
	else if (keycode == D)
		data->player->walk_dir = WALKRIGHT;
	else if (keycode == LEFT)
		data->player->turn_dir = -1;
	else if (keycode == RIGHT)
		data->player->turn_dir = 1;
	return (0);
}

int	handle_key_release(int keycode, t_data *data)
{
	if (keycode == W || keycode == S || keycode == A || keycode == D)
		data->player->walk_dir = STOP;
	else if (keycode == LEFT || keycode == RIGHT)
		data->player->turn_dir = 0;
	return (0);
}
