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

void draw_texture(t_data *g, int wall_size, int wallTopPixel, int wallBottomPixel)
{
    int textureOffsetX;
    if (g->rays->wasHitVertical)
        textureOffsetX = (int)g->rays->wallHitY % TILE;
    else
        textureOffsetX = (int)g->rays->wallHitX % TILE;
    textureOffsetX *= 200 / TILE;

    for (int y = wallTopPixel; y < wallBottomPixel; y++)
    {
        int distanceFromTop = y + (wall_size / 2) - (HEIGHT / 2);
        int textureOffsetY = distanceFromTop * ((float)200.0 / wall_size);
        // 동서남북 텍스쳐 결정
        if (g->rays->wasHitVertical)
        {
            if ((g->rays->isRayFacingLeft))
                put_pixel_to_screen(g, g->rays->stripId, y, g->imgs[WEST].addr[(g->imgs[WEST].w * (textureOffsetY + 1)) - textureOffsetX]);
            else
                put_pixel_to_screen(g, g->rays->stripId, y, g->imgs[EAST].addr[(g->imgs[EAST].w * textureOffsetY) + textureOffsetX]);
        }
        else
        {
            if ((g->rays->isRayFacingDown))
                put_pixel_to_screen(g, g->rays->stripId, y, g->imgs[SOUTH].addr[(g->imgs[SOUTH].w * (textureOffsetY + 1)) - textureOffsetX]);
            else
                put_pixel_to_screen(g, g->rays->stripId, y, g->imgs[NORTH].addr[(g->imgs[NORTH].w * textureOffsetY) + textureOffsetX]);
        }
    }

}