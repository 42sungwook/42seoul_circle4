#include "../srcs/cub3d.h"

void draw_miniplayer(t_data *g)
{
	int	new_x;
	int	new_y;

	if (g->player->turn_dir != 0)
	{
		g->player->rotation_angle += g->player->turn_dir * (PI / 180.0) * ROT_SPEED;
		g->player->dot_x += cos(g->player->rotation_angle);
		g->player->dot_y += sin(g->player->rotation_angle);
	}
	new_x = g->player->x + (int)(cos(g->player->rotation_angle + (PI / 180.0) * 90.0 * g->player->walk_dir) * MOVE_SPEED);
	new_y = g->player->y + (int)(sin(g->player->rotation_angle + (PI / 180.0) * 90.0 * g->player->walk_dir) * MOVE_SPEED);

	if (g->player->walk_dir != STOP && !is_wall(g, new_x, new_y))
	{
		g->player->x = new_x;
		g->player->y = new_y;
	}
	g->player->dot_x = g->player->x + 8 + 5 * cos(g->player->rotation_angle);
	g->player->dot_y = g->player->y + 8 + 5 * sin(g->player->rotation_angle);
	put_img_to_screen(g, &g->imgs[2], g->player->x, g->player->y);
	put_img_to_screen(g, &g->imgs[3], g->player->dot_x, g->player->dot_y);
}
