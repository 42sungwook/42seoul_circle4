#include "./cub3d.h"

int		handle_key_press(int keycode, t_data *data)
{
	if (keycode == 53) // ESC key
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	else if (keycode == 123 || keycode == 0) // Left arrow key or A key
		data->turn_dir = -1;
	else if (keycode == 124 || keycode == 2) // Right arrow key
		data->turn_dir = 1;
	else if (keycode == 125 || keycode == 1) // Down arrow key
		data->walk_dir = -1;
	else if (keycode == 126 || keycode == 13) // Up arrow key
		data->walk_dir = 1;
	return (0);
}

int		handle_key_release(int keycode, t_data *data)
{
	if (keycode == 123 || keycode == 0) // Left arrow key or A key
		data->turn_dir = 0;
	else if (keycode == 124 || keycode == 2) // Right arrow key
		data->turn_dir = 0;
	else if (keycode == 125 || keycode == 1) // Down arrow key
		data->walk_dir = 0;
	else if (keycode == 126 || keycode == 13) // Up arrow key
		data->walk_dir = 0;
	return (0);
}

int		handle_destroy_win(t_data *data)
{
	(void)data;
	exit(0);
	return (0);
}

void my_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int ft_loop(t_data *data)
{
	double	angle_rad;
	mlx_clear_window(data->mlx, data->win);
	if (data->turn_dir != 0)
		data->rotation_angle += data->turn_dir * PI / 180.0;
	if (data->walk_dir != 0)
	{
		data->x += data->walk_dir * cos(data->rotation_angle);
		data->y += data->walk_dir * sin(data->rotation_angle);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, data->x, data->y);
	return (0);
}

void fill_circle(t_data *data, int center_x, int center_y, int radius, int color)
{
    int x = radius;
    int y = 0;
    int radius_error = 1 - x;

    while (x >= y)
    {
        // Draw horizontal lines to fill the circle
        for (int i = center_x - x; i <= center_x + x; i++)
        {
            my_pixel_put(data, i, center_y + y, color);
            my_pixel_put(data, i, center_y - y, color);
        }

        // Draw horizontal lines for the mirrored parts of the circle
        for (int i = center_x - y; i <= center_x + y; i++)
        {
            my_pixel_put(data, i, center_y + x, color);
            my_pixel_put(data, i, center_y - x, color);
        }

        y++;

        if (radius_error < 0)
        {
            radius_error += 2 * y + 1;
        }
        else
        {
            x--;
            radius_error += 2 * (y - x + 1);
        }
    }
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
	data.walk_dir = 0;
	data.turn_dir = 0;
	data.mouse_x = 0;
	data.mouse_y = 0;
	data.rotation_angle = 0;
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	//data.addr[] 배열에 애초에 xpm 파일의 색깔이 지정되어있음.
	data.rotation_angle = PI / 2;
	fill_circle(&data, data.x, data.y, 10, 0x0000FF00);
	mlx_hook(data.win, 2, 0, handle_key_press, &data);
	mlx_hook(data.win, 3, 1, handle_key_release, &data);
	mlx_hook(data.win, 17, 17, handle_destroy_win, &data);
	mlx_loop_hook(data.mlx, ft_loop, &data);
	mlx_loop(data.mlx);
	return (0);
}
