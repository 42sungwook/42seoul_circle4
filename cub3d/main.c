#include "./cub3d.h"

int		handle_key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	else if (keycode == W)
		data->walk_dir = WALKFORWARD;
	else if (keycode == S)
		data->walk_dir = WALKBACKWARD;
	else if (keycode == A)
		data->walk_dir = WALKLEFT;
	else if (keycode == D)
		data->walk_dir = WALKRIGHT;
	else if (keycode == LEFT)
		data->turn_dir = -1;
	else if (keycode == RIGHT)
		data->turn_dir = 1;
	return (0);
}

int		handle_key_release(int keycode, t_data *data)
{
	if (keycode == W || keycode == S || keycode == A || keycode == D)
		data->walk_dir = STOP;
	else if (keycode == LEFT || keycode == RIGHT)
		data->turn_dir = 0;
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
			if (data->map[(x + i) / TILE_SIZE][(y + j) / TILE_SIZE] == '1')
				return (1);
			j++;
		} 
		i++;
	}
	return 0;
}

void draw_dot(t_data *data)
{
	int	new_x;
	int	new_y;

	if (data->turn_dir != 0)
		data->rotation_angle += data->turn_dir * PI / 180.0 * ROT_SPEED;
	new_x = data->x + cos(data->rotation_angle + (PI / 180.0) * 90 * data->walk_dir) * MOVE_SPEED;
	new_y = data->y + sin(data->rotation_angle + (PI / 180.0) * 90 * data->walk_dir) * MOVE_SPEED;
	if (data->walk_dir != 0 && !is_wall(data, new_x, new_y))
	{
		data->x = new_x;
		data->y = new_y;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->dot, data->x, data->y);
}

void draw_map(t_data *data)
{
	int i;
	int j;
	int tile_x;
	int tile_y;
	int tile_color;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->map_tile, i * TILE_SIZE, j * TILE_SIZE);
			j++;
		}
		i++;
	}
}


int ft_loop(t_data *data)
{
	double	angle_rad;
	mlx_clear_window(data->mlx, data->win);
	draw_map(data);
	draw_dot(data);

	return (0);
}

int		main(int ac, char **av)
{
	t_data	data;
	int		w;
	int		h;

	if (ac < 2)
		return (0);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Moving Circle");
	data.x = 40;
	data.y = 40;
	data.center_x = data.x;
	data.center_y = data.y;
	data.radius = 10;
	data.color = 0x0000FF00;
	data.walk_dir = 0;
	data.turn_dir = 0;
	data.mouse_x = 0;
	data.mouse_y = 0;
	data.rotation_angle = 0;
	//data.addr[] 배열에 애초에 xpm 파일의 색깔이 지정되어있음.
	data.rotation_angle = PI / 2;
	parse_map(av, &data);

	data.dot = mlx_xpm_file_to_image(data.mlx, "./asset/circle.xpm", &w, &h);
	data.map_tile = mlx_xpm_file_to_image(data.mlx, "./asset/tile00.xpm", &w, &h);
	mlx_hook(data.win, 2, 0, handle_key_press, &data);
	mlx_hook(data.win, 3, 1, handle_key_release, &data);
	mlx_hook(data.win, 17, 17, handle_destroy_win, &data);
	mlx_loop_hook(data.mlx, ft_loop, &data);
	mlx_loop(data.mlx);
	exit(0);
}
