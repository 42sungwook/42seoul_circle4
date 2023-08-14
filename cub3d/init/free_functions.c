/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seulee2 <seulee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:16:16 by seulee2           #+#    #+#             */
/*   Updated: 2023/08/14 18:17:21 by seulee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub3d.h"

int	ft_free(char *str)
{
	if (!str)
		return (0);
	free(str);
	str = 0;
	return (1);
}

void	free_chars(char **chars)
{
	int	i;

	i = 0;
	while (chars[i])
	{
		free(chars[i]);
		i++;
	}
	free(chars);
	chars = 0;
}

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}
