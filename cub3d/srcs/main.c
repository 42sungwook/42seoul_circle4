/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seulee2 <seulee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:15:08 by seulee2           #+#    #+#             */
/*   Updated: 2023/08/25 12:28:05 by seulee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int	handle_destroy_win(t_data *data)
{
	(void)data;
	exit(0);
}

int	ft_loop(t_data *g)
{
	mlx_clear_window(g->mlx, g->win);
	draw_player(g);
	cast_rays(g);
	mlx_put_image_to_window(g->mlx, g->win, g->imgs[0].img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*g;

	g = (t_data *)malloc(sizeof(t_data));
	init_game(g, ac, av);
	mlx_hook(g->win, 2, 0, handle_key_press, g);
	mlx_hook(g->win, 3, 1, handle_key_release, g);
	mlx_hook(g->win, 17, 17, handle_destroy_win, g);
	mlx_loop_hook(g->mlx, ft_loop, g);
	mlx_loop(g->mlx);
	exit(0);
}
