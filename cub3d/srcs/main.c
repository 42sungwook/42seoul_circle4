#include "./cub3d.h"

void	put_pixel_to_screen(t_data *g, int x, int y, int color)
{
	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
		return ;
	g->imgs[0].addr[y * g->imgs[0].w + x] = color;
}

void	put_img_to_screen(t_data *g, t_img *imgs, int x, int y)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	if (x > WIDTH - MINI_TILE || y > WIDTH - MINI_TILE || x < 0 || y < 0)
		return ;
	while (i < imgs->h)
	{
		j = 0;
		while (j < imgs->w)
		{
			color = imgs->addr[i * imgs->w + j];
			if (color != 0)
				put_pixel_to_screen(g, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

int		handle_destroy_win(t_data *data)
{
	(void)data;
	exit(0);
	return (0);
}

int is_wall(t_data *g, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	if (x < 0 || y < 0 || x > g->map_info->w * MINI_TILE || y > g->map_info->h * MINI_TILE)
		return (0);
	x--;
	y--;
	while (i < 18)
	{
		j = 0;
		while (j < 18)
		{
			if (g->map_info->map[(y + i) / MINI_TILE][(x + j) / MINI_TILE] == '1')
				return (1);
			j++;
		} 
		i++;
	}
	return 0;
}

int ft_loop(t_data *g)
{
	mlx_clear_window(g->mlx, g->win);
	draw_minimap(g);
	draw_miniplayer(g);
	cast_rays(g);
	mlx_put_image_to_window(g->mlx, g->win, g->imgs[0].img, 0, 0);
	return (0);
}

int		main(int ac, char **av)
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



//raycasting
//minimap 따로 이미지로
//minimap은 주인공 기준으로 map screen에 원하는 부분에 옮겨줄 것
