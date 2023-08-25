/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_ray_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seulee2 <seulee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:02:44 by seulee2           #+#    #+#             */
/*   Updated: 2023/08/25 15:49:20 by seulee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub3d_bonus.h"

void	shot_ray(t_data *g)
{
	double	wall_size;
	int		wall_top_pixel;
	int		wall_bottom_pixel;

	wall_size = HEIGHT / g->rays->distance;
	wall_size *= 60;
	wall_top_pixel = (HEIGHT / 2) - (wall_size / 2);
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	wall_bottom_pixel = (HEIGHT / 2) + (wall_size / 2);
	if (wall_bottom_pixel > HEIGHT)
		wall_bottom_pixel = HEIGHT;
	draw_texture(g, wall_size, wall_top_pixel, wall_bottom_pixel);
}