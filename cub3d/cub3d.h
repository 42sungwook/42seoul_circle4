#ifndef CUB3D_H
#define CUB3D_H

#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>

#define WIDTH 1000
#define HEIGHT 1000
#define PI 3.14159265
#define MOVE_SPEED 5
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

typedef struct s_data
{
	void *mlx;
	void *win;
	char **map;
	t_img *imgs;
	float x;
	float y;
	float dot_x;
	float dot_y;
	float walk_dir;
	float turn_dir;
	float rotation_angle;
} t_data;

char *ft_itoa(int n);
char **ft_split(char const *s, char c);
void parse_map(char **av, t_data *data);

// init
void init_img(t_data *g);
void init_base(t_data *g);

#endif
