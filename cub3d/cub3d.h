#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# define WIDTH 1000
# define HEIGHT 1000
# define PI 3.14159265

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	double	x;
	double	y;
	double	walk_dir;
	double	turn_dir;
	double	mouse_x;
	double	mouse_y;
	float		rotation_angle;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

char	*ft_itoa(int n);

#endif
