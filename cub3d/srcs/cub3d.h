#ifndef CUB3D_H
#define CUB3D_H

#include <fcntl.h>
#include <math.h>
#include <stdio.h>

#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"
#include "../mlx/mlx.h"

#define WIDTH 800
#define HEIGHT 800
#define MINI_WIDTH 200
#define MINI_HEIGHT 200
#define PI 3.141593
#define MOVE_SPEED 16
#define ROT_SPEED 8
#define MINI_TILE 64
#define IMG_CNT 9
#define NUM_RAYS 800
#define INT_MAX 2147483647
#define TRUE 1
#define FALSE 0
#define FLT_MAX 3.40282347e+38F
#define P_ERROR 3

enum e_key { W = 13, A = 0, S = 1, D = 2, LEFT = 123, RIGHT = 124, ESC = 53 };

enum e_dir {
  STOP = -1,
  WALKFORWARD,
  WALKRIGHT,
  WALKBACKWARD,
  WALKLEFT,
};

enum e_img {
  SCREEN,
  MINI_MAP,
  MINI_WALL,
  MINI_PLAIN,
  MINI_PLAYER,
  EAST,
  WEST,
  SOUTH,
  NORTH,
};

typedef struct s_color {
  int r;
  int g;
  int b;
} t_color;

typedef struct s_img {
  void *img;
  int *addr;
  int bpp;
  int line_len;
  int endian;
  int w;
  int h;
} t_img;

typedef struct s_map {
  int w;
  int h;
  t_color color_c;
  t_color color_f;
  int character_x;
  int character_y;
  double  character_angle;
  char **map;
} t_map;

typedef struct s_player {
  double x;
  double y;
  double dot_x;
  double dot_y;
  double walk_dir;
  double turn_dir;
  double rotation_angle;
} t_player;

typedef struct s_ray {
  int stripId;
  double rayAngle;
  double wallHitX;
  double wallHitY;
  double distance;
  int wasHitVertical;
  int isRayFacingUp;
  int isRayFacingDown;
  int isRayFacingLeft;
  int isRayFacingRight;
  int wallHitContent;
  double xintercept;
  double yintercept;
  double xstep;
  double ystep;
  int foundHorzWallHit;
  double horzWallHitX;
  double horzWallHitY;
  int horzWallContent;
  int foundVertWallHit;
  double vertWallHitX;
  double vertWallHitY;
  int vertWallContent;
  double nextHorzTouchX;
  double nextHorzTouchY;
  double nextVertTouchX;
  double nextVertTouchY;
  double xToCheck;
  double yToCheck;
  double horzHitDistance;
  double vertHitDistance;
} t_ray;

typedef struct s_data {
  void *mlx;
  void *win;
  t_img *imgs;
  t_map *map_info;
  t_player *player;
  t_ray *rays;
} t_data;


// draw
void put_img_to_screen(t_data *g, t_img *imgs, int x, int y);
void put_pixel_to_screen(t_data *g, int x, int y, int color);
void put_img_to_minimap(t_data *g, t_img *imgs, int x, int y);
void put_pixel_to_minimap(t_data *g, int x, int y, int color);
void put_minimap_to_screen(t_data *g);
void draw_minimap(t_data *g);
void draw_miniplayer(t_data *g);

// init
void init_game(t_data *g, int ac, char **av);
void init_img(t_data *g);
void save_map_info(t_data *g, char **av);
void set_color(t_color *color, char *str_rgb);
int ft_free(char *str);
void free_chars(char **chars);
void print_error(char *str);
int check_space(char *one_line, char *buff);

// srcs
int handle_key_press(int keycode, t_data *data);
int handle_key_release(int keycode, t_data *data);
int is_wall(t_data *g, int x, int y);

// raycasting
void cast_rays(t_data *g);

// valid
int check_map(t_data *g);

void draw_bg(t_data *g);
#endif
