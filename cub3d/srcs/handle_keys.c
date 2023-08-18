/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seulee2 <seulee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:15:53 by seulee2           #+#    #+#             */
/*   Updated: 2023/08/18 15:52:38 by seulee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

static int	handle_mouse_move(int x, int y, t_data *g)
{
	double	tmp_x;

	if (g->player->mouse_mode > 0)
	{
		mlx_mouse_move(g->win, WIDTH / 2, HEIGHT / 2);
		g->player->mouse_y = y;
		tmp_x = x;
		mlx_mouse_get_pos(g->win, &g->player->mouse_x, &g->player->mouse_y);
		tmp_x -= g->player->mouse_x;
		printf("%d, %d, %f\n", x, g->player->mouse_x, tmp_x / (PI * 80));
		g->player->rotation_angle += tmp_x / (PI * 80);
	}
	return (0);
}

static void	change_mouse_mode(t_data *g)
{
	if (g->player->mouse_mode == 0)
	{
		g->player->mouse_mode = 1;
		mlx_mouse_hide();
		mlx_hook(g->win, 6, 0, handle_mouse_move, g);
	}
	else
	{
		g->player->mouse_mode = 0;
		g->player->turn_dir = 0;
		mlx_mouse_show();
	}
}

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
	else if (keycode == MOUSE)
		change_mouse_mode(data);
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
