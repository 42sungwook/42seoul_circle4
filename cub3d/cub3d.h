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
#define MOVE_SPEED 4
#define ROT_SPEED 4
#define TILE_SIZE 32

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
	STOP,
	WALKFORWARD,
	WALKRIGHT,
	WALKBACKWARD,
	WALKLEFT
};

typedef struct s_data
{
	void *mlx;
	void *win;
	char **map;
	void *map_tile;
	void *dot;
	double x;
	double y;
	double walk_dir;
	double turn_dir;
	double mouse_x;
	double mouse_y;
	float rotation_angle;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	// fill circle
	int center_x;
	int center_y;
	int radius;
	int radius_error;
	int color;
} t_data;

char *ft_itoa(int n);
char **ft_split(char const *s, char c);
void parse_map(char **av, t_data *data);

#endif
