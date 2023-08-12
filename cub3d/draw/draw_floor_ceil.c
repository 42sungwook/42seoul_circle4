#include "../srcs/cub3d.h"

void    draw_bg(t_data *g)
{
    int i;
    int j;
    int floor;
    int ceil;

    floor = g->map_info->color_f.r << 16 | g->map_info->color_f.g << 8 | g->map_info->color_f.b;
    ceil = g->map_info->color_c.r << 16 | g->map_info->color_c.r << 8 | g->map_info->color_c.r;
    i = 0;
    while (i < HEIGHT / 2)
    {
        j = 0;
        while (j < WIDTH)
        {
            put_pixel_to_screen(g, j, i, floor);
            ++j;
        }
        ++i;
    }
    while (i < HEIGHT)
    {
        j = 0;
        while (j < WIDTH)
        {
            put_pixel_to_screen(g, j, i, ceil);
            ++j;
        }
        ++i;
    }
}