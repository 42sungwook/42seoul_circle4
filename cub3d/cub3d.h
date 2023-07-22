#ifndef CUB3D_H
#define CUB3D_H

#include "./mlx/mlx.h"
#include "./libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include <stdio.h>
#include <math.h>
#include <fcntl.h>

#define WIDTH 1000
#define HEIGHT 1000
#define PI 3.14159265
#define MOVE_SPEED 2
#define ROT_SPEED 4
#define TILE_SIZE 32
#define IMG_CNT 5

enum e_key
{
	W = 13,
	A = 0,
	S = 1,
	D = 2,
	LEFT = 123,
	RIGHT = 124,
	ESC = 53
};

enum e_dir
{
	STOP = -1,
	WALKFORWARD,
	WALKRIGHT,
	WALKBACKWARD,
	WALKLEFT,
};

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

typedef struct s_img
{
	void *img;
	int *addr;
	int bpp;
	int line_len;
	int endian;
	int w;
	int h;
} t_img;

typedef struct s_map
{
	int w;
	int h;
	t_color color_c;
	t_color color_f;
	void *tex_n;
	void *tex_e;
	void *tex_w;
	void *tex_s;
	char **map;
} t_map;

typedef struct s_player
{
	double x;
	double y;
	double dot_x;
	double dot_y;
	double walk_dir;
	double turn_dir;
	double rotation_angle;
} t_player;

typedef struct s_data
{
	void *mlx;
	void *win;
	t_img *imgs;
	t_map *map_info;
	t_player *player;
} t_data;

// init
void	init_game(t_data *g, int ac, char **av);
void	init_img(t_data *g);
void	save_map_info(t_data *g, char **av);
void	set_color(t_color *color, char *str_rgb);
int		ft_free(char *str);
void	free_chars(char **chars);
void	print_error(char *str);



#endif
