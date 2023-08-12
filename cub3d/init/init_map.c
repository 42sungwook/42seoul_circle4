#include "../srcs/cub3d.h"

static char	*get_new_map(t_map *map_info, char *one_line, char *buff)
{
	char	*temp;
	int		len;

	if (buff[0] != ' ')
	{
		len = (int)ft_strlen(buff);
		if (len == 0)
			print_error("Error empty line");
	}
	else
		len = (int)ft_strlen(buff) - 1;
	if (map_info->w < len)
		map_info->w = len;
	map_info->h++;
	temp = ft_strjoin(one_line, buff);
	free(buff);
	free(one_line);
	return (temp);
}

static int	set_map_setting(t_data *g, char **key_value)
{
	if (ft_strlen(key_value[0]) == 2
		&& !ft_strncmp(key_value[0], "NO", 2) && g->imgs[NORTH].img == NULL)
		g->imgs[NORTH].img = mlx_xpm_file_to_image(g->mlx, key_value[1], \
		&g->imgs[NORTH].w, &g->imgs[NORTH].h);
	else if (ft_strlen(key_value[0]) == 2
		&& !ft_strncmp(key_value[0], "SO", 2) && g->imgs[SOUTH].img == NULL)
		g->imgs[SOUTH].img = mlx_xpm_file_to_image(g->mlx, key_value[1], \
		&g->imgs[SOUTH].w, &g->imgs[SOUTH].h);
	else if (ft_strlen(key_value[0]) == 2
		&& !ft_strncmp(key_value[0], "WE", 2) && g->imgs[WEST].img == NULL)
		g->imgs[WEST].img = mlx_xpm_file_to_image(g->mlx, key_value[1], \
		&g->imgs[WEST].w, &g->imgs[WEST].h);
	else if (ft_strlen(key_value[0]) == 2
		&& !ft_strncmp(key_value[0], "EA", 2) && g->imgs[EAST].img == NULL)
		g->imgs[EAST].img = mlx_xpm_file_to_image(g->mlx, key_value[1], \
		&g->imgs[EAST].w, &g->imgs[EAST].h);
	else if (ft_strlen(key_value[0]) == 1
		&& !ft_strncmp(key_value[0], "F", 1) && g->map_info->color_f.r == -1)
		set_color(&g->map_info->color_f, key_value[1]);
	else if (ft_strlen(key_value[0]) == 1
		&& !ft_strncmp(key_value[0], "C", 1) && g->map_info->color_c.r == -1)
		set_color(&g->map_info->color_c, key_value[1]);
	else
		print_error("Input Error\n");
	return (0);
}

static void	make_map_rec(t_map *map_info, char *one_line)
{
	int		i;
	int		len;
	char	*space_line;
	char	*temp;

	i = 0;
	map_info->map = ft_split(one_line, '\n');
	free(one_line);
	while (i < map_info->h)
	{
		len = map_info->w - ft_strlen(map_info->map[i]);
		if (len > 0)
		{
			space_line = malloc(len + 1);
			space_line[len] = 0;
			ft_memset(space_line, ' ', len);
			temp = ft_strjoin(map_info->map[i], space_line);
			free(map_info->map[i]);
			free(space_line);
			map_info->map[i] = temp;
		}
		i++;
	}
}

static int	get_map_setting(t_data *g, int fd)
{
	int		line_cnt;
	int		len_value;
	char	*line;
	char	**key_value;

	line_cnt = 0;
	while (line_cnt < 6)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[0] == '\n' && ft_free(line))
			continue ;
		key_value = ft_split(line, ' ');
		if (*(key_value + 1) == NULL)
			print_error("Invalid Input\n");
		len_value = ft_strlen(key_value[1]);
		if (key_value[1][len_value - 1] == '\n')
			key_value[1][len_value - 1] = '\0';
		if (!set_map_setting(g, key_value))
			line_cnt++;
		free_chars(key_value);
		free(line);
	}
	return (0);
}

void	save_map_info(t_data *g, char **av)
{
	int		fd;
	char	*buff;
	char	*one_line;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		print_error("Opening File");
	get_map_setting(g, fd);
	one_line = malloc(1);
	one_line[0] = 0;
	while (fd >= 0)
	{
		buff = get_next_line(fd);
		if (buff == NULL)
			break ;
		if (check_space(one_line, buff))
			continue ;
		one_line = get_new_map(g->map_info, one_line, buff);
	}
	make_map_rec(g->map_info, one_line);
}