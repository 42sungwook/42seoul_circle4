/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seulee2 <seulee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:15:41 by seulee2           #+#    #+#             */
/*   Updated: 2023/08/21 14:04:15 by seulee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define WIDTH 1000
# define HEIGHT 1000
# define M_WIDTH 800
# define M_HEIGHT 800
# define PI 3.141593
# define MOVE_SPEED 10
# define ROT_SPEED 8
# define TILE 64
# define IMG_CNT 9
# define NUM_RAYS 800
# define INT_MAX 2147483647
# define TRUE 1
# define FALSE 0
# define FLT_MAX 3.40282347e+38F
# define P_ERROR 3

enum e_key {
	W = 13,
	A = 0,
	S = 1,
	D = 2,
	LEFT = 123,
	RIGHT = 124,
	ESC = 53,
	MOUSE = 50,
	M_RAY = 5,
};

enum e_dir {
	STOP = -1,
	WALKFORWARD,
	WALKRIGHT,
	WALKBACKWARD,
	WALKLEFT,
	VERTICAL,
	HORIZONTAL
};

enum e_img {
	M_WALL,
	M_PLAIN,
	EAST,
	WEST,
	SOUTH,
	NORTH,
	M_MAP,
	M_PLAYER,
	SCREEN,
};

typedef struct s_color {
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_img {
	void	*img;
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef struct s_map {
	int		w;
	int		h;
	int		mini_ray;
	t_color	color_c;
	t_color	color_f;
	int		character_x;
	int		character_y;
	double	character_angle;
	char	**map;
}	t_map;

typedef struct s_player {
	double	x;
	double	y;
	double	dot_x;
	double	dot_y;
	double	walk_dir;
	double	turn_dir;
	double	rotation_angle;
	int		mouse_mode;
	int		mouse_x;
	int		mouse_y;
}	t_player;

typedef struct s_ray {
	int		strip_id;
	double	ray_angle;
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
	int		was_hit_vertical;
	int		is_ray_up;
	int		is_ray_down;
	int		is_ray_left;
	int		is_ray_right;
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
	int		horz_wall_hit;
	double	horz_wall_hit_x;
	double	horz_wall_hit_y;
	int		vert_wall_hit;
	double	vert_wall_hit_x;
	double	vert_wall_hit_y;
	double	horz_hit_distance;
	double	vert_hit_distance;
	int		x0;
	int		y0;
	int		x1;
	int		y1;
}	t_ray;

typedef struct s_data {
	void		*mlx;
	void		*win;
	t_img		*imgs;
	t_map		*map_info;
	t_player	*player;
	t_ray		*rays;
}	t_data;

typedef struct s_mini_line {
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_mini_line;

// draw
void	put_img_to_screen(t_data *g, t_img *imgs, int x, int y);
void	put_pixel_to_screen(t_data *g, int x, int y, int color);
void	put_img_to_minimap(t_data *g, t_img *imgs, int x, int y);
void	put_pixel_to_minimap(t_data *g, int x, int y, int color);
void	put_minimap_to_screen(t_data *g);
void	draw_minimap(t_data *g);
void	draw_player(t_data *g);
void	draw_line(t_data *g);
void	draw_texture(t_data *g, int wall_size, int wallTopPixel, \
		int wallBottomPixel);
void	revert_minimap(t_data *g);
void	minimap_define_xy(t_data *g, int *x, int *y);

// init
void	init_game(t_data *g, int ac, char **av);
void	init_img(t_data *g);
void	save_map_info(t_data *g, char **av);
void	set_color(t_color *color, char *str_rgb);
int		ft_free(char *str);
void	free_chars(char **chars);
void	print_error(char *str);
int		check_space(char *one_line, char *buff);
void	check_file(t_data *g, char *str, int idx);

// srcs
int		handle_key_press(int keycode, t_data *data);
int		handle_key_release(int keycode, t_data *data);
int		is_wall(t_data *g, int x, int y);

// raycasting
void	cast_rays(t_data *g);
int		map_has_wall_at(t_data *g, double x, double y);
double	distance_between_points(double x1, double y1, double x2, double y2);
void	ray_dir(t_data *g, double ray_angle);
void	compare_hv_distance(t_data *g, double ray_angle);
void	shot_ray(t_data *g);

// valid
int		check_map(t_data *g);
void	draw_bg(t_data *g);

#endif
