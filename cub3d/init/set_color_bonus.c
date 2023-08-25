/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seulee2 <seulee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:16:54 by seulee2           #+#    #+#             */
/*   Updated: 2023/08/16 14:31:20 by seulee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub3d_bonus.h"

void	set_color(t_color *color, char *str_rgb)
{
	int		color_cnt;
	char	**rgb;
	char	**tmp_rgb;

	rgb = ft_split(str_rgb, ',');
	tmp_rgb = rgb;
	color_cnt = 0;
	while (*(tmp_rgb++))
		color_cnt++;
	if (color_cnt != 3)
		print_error("INVALID COLOR");
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (color->r < 0 || color->r > 255)
		print_error("INVALID COLOR");
	if (color->g < 0 || color->g > 255)
		print_error("INVALID COLOR");
	if (color->b < 0 || color->b > 255)
		print_error("INVALID COLOR");
	free_chars(rgb);
}
