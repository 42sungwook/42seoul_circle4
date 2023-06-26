#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# define WIDTH 1000
# define HEIGHT 1000

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	mouse_x;
	double	mouse_y;
	float		rotation_angle;
}				t_data;

char	*ft_itoa(int n);

#endif
