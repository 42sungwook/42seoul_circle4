#include "./cub3d.h"

void	put_img_to_screen(t_data *g, t_img *imgs, int x, int y)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < imgs->h)
	{
		j = 0;
		while (j < imgs->w)
		{
			color = imgs->addr[i * imgs->w + j];
			if (color != 0)
				g->imgs[0].addr[(y + i) * g->imgs[0].w + (x + j)] = color;
			j++;
		}
		i++;
	}
}

int		handle_key_press(int keycode, t_data *data)
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

int		handle_key_release(int keycode, t_data *data)
{
	if (keycode == W || keycode == S || keycode == A || keycode == D)
		data->player->walk_dir = STOP;
	else if (keycode == LEFT || keycode == RIGHT)
		data->player->turn_dir = 0;
	return (0);
}

int		handle_destroy_win(t_data *data)
{
	(void)data;
	exit(0);
	return (0);
}

int is_wall(t_data *data, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	x--;
	y--;
	while (i < 18)
	{
		j = 0;
		while (j < 18)
		{
			if (data->map_info->map[(x + i) / TILE_SIZE][(y + j) / TILE_SIZE] == '1')
				return (1);
			j++;
		} 
		i++;
	}
	return 0;
}

void draw_dot(t_data *g)
{
	int	new_x;
	int	new_y;

	if (g->player->turn_dir != 0)
	{
		g->player->rotation_angle += g->player->turn_dir * (PI / 180.0) * ROT_SPEED;
		g->player->dot_x += cos(g->player->rotation_angle);
		g->player->dot_y += sin(g->player->rotation_angle);
	}
	new_x = g->player->x + (int)(cos(g->player->rotation_angle + (PI / 180.0) * 90.0 * g->player->walk_dir) * MOVE_SPEED);
	new_y = g->player->y + (int)(sin(g->player->rotation_angle + (PI / 180.0) * 90.0 * g->player->walk_dir) * MOVE_SPEED);

	if (g->player->walk_dir != STOP && !is_wall(g, new_x, new_y))
	{
		g->player->x = new_x;
		g->player->y = new_y;
	}
	g->player->dot_x = g->player->x + 8 + 5 * cos(g->player->rotation_angle);
	g->player->dot_y = g->player->y + 8 + 5 * sin(g->player->rotation_angle);
	put_img_to_screen(g, &g->imgs[2], g->player->x, g->player->y);
	put_img_to_screen(g, &g->imgs[3], g->player->dot_x, g->player->dot_y);
}

void draw_map(t_data *g)
{
	int i;
	int j;
	int tile_x;
	int tile_y;
	int tile_color;

	i = 0;
	while (g->map_info->map[i])
	{
		j = 0;
		while (g->map_info->map[i][j])
		{
			if (g->map_info->map[i][j] == '1')
				put_img_to_screen(g, &g->imgs[1], i * TILE_SIZE, j * TILE_SIZE);
			else
				put_img_to_screen(g, &g->imgs[4], i * TILE_SIZE, j * TILE_SIZE);
			j++;
		}
		i++;
	}
}


int ft_loop(t_data *g)
{
	mlx_clear_window(g->mlx, g->win);
	draw_map(g);
	draw_dot(g);
	mlx_put_image_to_window(g->mlx, g->win, g->imgs[0].img, 0, 0);
	return (0);
}

int		main(int ac, char **av)
{
	t_data	*g;
	int		w;
	int		h;

	g = (t_data *)malloc(sizeof(t_data));
	init_game(g, ac, av);
	mlx_hook(g->win, 2, 0, handle_key_press, g);
	mlx_hook(g->win, 3, 1, handle_key_release, g);
	mlx_hook(g->win, 17, 17, handle_destroy_win, g);
	mlx_loop_hook(g->mlx, ft_loop, g);
	mlx_loop(g->mlx);
	exit(0);
}
