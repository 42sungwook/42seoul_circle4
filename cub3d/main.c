#include "./cub3d.h"

int		handle_key_press(int keycode, t_data *data)
{
	if (keycode == 53) // ESC key
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	else if (keycode == 123 || keycode == 0) // Left arrow key or A key
		data->dir_x = -1;
	else if (keycode == 124 || keycode == 2) // Right arrow key
		data->dir_x = 1;
	else if (keycode == 125 || keycode == 1) // Down arrow key
		data->dir_y = 1;
	else if (keycode == 126 || keycode == 13) // Up arrow key
		data->dir_y = -1;
	return (0);
}

int		handle_key_release(int keycode, t_data *data)
{
	if (keycode == 123 || keycode == 0) // Left arrow key or A key
		data->dir_x = 0;
	else if (keycode == 124 || keycode == 2) // Right arrow key
		data->dir_x = 0;
	else if (keycode == 125 || keycode == 1) // Down arrow key
		data->dir_y = 0;
	else if (keycode == 126 || keycode == 13) // Up arrow key
		data->dir_y = 0;
	return (0);
}

int	handle_mouse_move(int x, int y, t_data *data)
{
	(void)y;
	data->mouse_x = x % 100 - 5;
	return (0);
}

int		handle_destroy_win(t_data *data)
{
	(void)data;
	exit(0);
	return (0);
}

int ft_loop(t_data *data)
{
	double	angle_rad;
	mlx_clear_window(data->mlx, data->win);
	//if (data->mouse_x != 0)
	//{
	//	data->rotation_angle += data->mouse_x;
	//	if (data->rotation_angle >= 360)
	//		data->rotation_angle -= 360;
	//	else if (data->rotation_angle < 0)
	//		data->rotation_angle += 360;
	//}
	//angle_rad = data->rotation_angle * M_PI / 360.0;
	if (data->dir_x != 0)
		data->x += data->dir_x;
	if (data->dir_y != 0)
		data->y += data->dir_y;
	mlx_put_image_to_window(data->mlx, data->win, data->img, data->x, data->y);
	return (0);
}

int		main(void)
{
	t_data	data;
	int		w;
	int		h;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Moving Circle");
	data.x = 60;
	data.y = 60;
	data.dir_x = 0;
	data.dir_y = 0;
	data.mouse_x = 0;
	data.mouse_y = 0;
	data.rotation_angle = 0;
	data.img = mlx_xpm_file_to_image(data.mlx, "./asset/tile00.xpm", &w, &h);
	mlx_hook(data.win, 2, 0, handle_key_press, &data);
	mlx_hook(data.win, 3, 1, handle_key_release, &data);
	mlx_hook(data.win, 17, 17, handle_destroy_win, &data);
	mlx_hook(data.win, 6, 0, handle_mouse_move, &data); // mouse click event
	mlx_loop_hook(data.mlx, ft_loop, &data);
	mlx_loop(data.mlx);
	return (0);
}
