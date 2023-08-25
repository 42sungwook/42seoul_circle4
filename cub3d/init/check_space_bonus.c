/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seulee2 <seulee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:16:40 by seulee2           #+#    #+#             */
/*   Updated: 2023/08/14 18:17:09 by seulee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub3d_bonus.h"

int	check_space(char *one_line, char *buff)
{
	int	i;

	i = 0;
	if (one_line[0] == 0 && buff[0] == '\n')
	{
		free(buff);
		return (1);
	}
	while (buff[i])
	{
		if (buff[i] == '0' || buff[i] == '1')
			return (0);
		else if (buff[i] == '\n' && one_line[0] != 0)
			return (0);
		i++;
	}
	return (1);
}
