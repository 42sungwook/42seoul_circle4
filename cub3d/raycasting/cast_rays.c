#include "../srcs/cub3d.h"

void    shot_ray(t_data *g, int stripId)
{
    double wall_size = HEIGHT / g->rays->distance;
    wall_size *= 60;
    int wallTopPixel = (HEIGHT / 2) - (wall_size / 2);
    wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

    int wallBottomPixel = (HEIGHT / 2) + (wall_size / 2);
    wallBottomPixel = wallBottomPixel > HEIGHT ? HEIGHT : wallBottomPixel;

    double put_start = HEIGHT / 2 - wall_size / 2 - 2;

    int textureOffsetX;
    if (g->rays->wasHitVertical)
        textureOffsetX = (int)g->rays->wallHitY % MINI_TILE;
    else
        textureOffsetX = (int)g->rays->wallHitX % MINI_TILE;
    textureOffsetX *= 200 / MINI_TILE;

    for (int y = wallTopPixel; y < wallBottomPixel; y++)
    {
        int distanceFromTop = y + (wall_size / 2) - (HEIGHT / 2);
        int textureOffsetY = distanceFromTop * ((float)200.0 / wall_size);
        // 동서남북 텍스쳐 결정
        if (g->rays->wasHitVertical)
        {
            if ((g->rays->isRayFacingLeft))
                put_pixel_to_screen(g, stripId, y, g->imgs[WEST].addr[(g->imgs[WEST].w * (textureOffsetY + 1)) - textureOffsetX]);
            else
                put_pixel_to_screen(g, stripId, y, g->imgs[EAST].addr[(g->imgs[EAST].w * textureOffsetY) + textureOffsetX]);
        }
        else
        {
            if ((g->rays->isRayFacingDown))
                put_pixel_to_screen(g, stripId, y, g->imgs[SOUTH].addr[(g->imgs[SOUTH].w * (textureOffsetY + 1)) - textureOffsetX]);
            else
                put_pixel_to_screen(g, stripId, y, g->imgs[NORTH].addr[(g->imgs[NORTH].w * textureOffsetY) + textureOffsetX]);
        }
    }
}

void calHorRay(t_data *g, double rayAngle)
{
    // Find the y-coordinate of the closest horizontal grid intersection
		if (g->rays->isRayFacingDown)
    	g->rays->yintercept = floor((g->player->y + P_ERROR) / MINI_TILE) * MINI_TILE + MINI_TILE;
		else
			g->rays->yintercept = floor((g->player->y + P_ERROR) / MINI_TILE) * MINI_TILE;
    // Find the x-coordinate of the closest horizontal grid intersection
    g->rays->xintercept = (g->player->x + P_ERROR) + (g->rays->yintercept - (g->player->y + P_ERROR)) / tan(rayAngle);
    // Calculate the increment xstep and ystep
		g->rays->ystep = MINI_TILE;
		if (g->rays->isRayFacingUp)
				g->rays->ystep *= -1;
		g->rays->xstep = MINI_TILE / tan(rayAngle);
		if (g->rays->isRayFacingLeft && g->rays->xstep > 0)
				g->rays->xstep *= -1;
		if (g->rays->isRayFacingRight && g->rays->xstep < 0)
				g->rays->xstep *= -1;
    // Increment xstep and ystep until we find a wall
    while (g->rays->xintercept >= 0 && g->rays->xintercept < g->map_info->w * MINI_TILE && g->rays->yintercept >= 0 && g->rays->yintercept < g->map_info->h * MINI_TILE)
		{
        if (mapHasWallAt(g, g->rays->xintercept, g->rays->yintercept - g->rays->isRayFacingUp)) {
            // found a wall hit
            g->rays->horzWallHitX = g->rays->xintercept;
            g->rays->horzWallHitY = g->rays->yintercept;
            g->rays->foundHorzWallHit = TRUE;
            break;
        } else {
            g->rays->xintercept += g->rays->xstep;
            g->rays->yintercept += g->rays->ystep;
        }
    }
}

void calVerRay(t_data *g, double rayAngle)
{
    // Find the x-coordinate of the closest horizontal grid intersection
		if (g->rays->isRayFacingRight)
    	g->rays->xintercept = floor((g->player->x + P_ERROR) / MINI_TILE) * MINI_TILE + MINI_TILE;
		else
			g->rays->xintercept = floor((g->player->x + P_ERROR) / MINI_TILE) * MINI_TILE;
    // Find the y-coordinate of the closest horizontal grid intersection
    g->rays->yintercept = (g->player->y + P_ERROR) + (g->rays->xintercept - (g->player->x + P_ERROR)) * tan(rayAngle);
    // Calculate the increment xstep and ystep
    g->rays->xstep = MINI_TILE;
		if (g->rays->isRayFacingLeft)
    	g->rays->xstep *= -1;
    g->rays->ystep = MINI_TILE * tan(rayAngle);
		if (g->rays->isRayFacingUp && g->rays->ystep > 0)
			g->rays->ystep *= -1;
		if (g->rays->isRayFacingDown && g->rays->ystep < 0)
			g->rays->ystep *= -1;
    // Increment xstep and ystep until we find a wall
    while (g->rays->xintercept >= 0 && g->rays->xintercept < g->map_info->w * MINI_TILE && g->rays->yintercept >= 0 && g->rays->yintercept < g->map_info->h * MINI_TILE) {
        if (mapHasWallAt(g, g->rays->xintercept - g->rays->isRayFacingLeft, g->rays->yintercept)) {
            // found a wall hit
            g->rays->vertWallHitX = g->rays->xintercept;
            g->rays->vertWallHitY = g->rays->yintercept;
            g->rays->foundVertWallHit = TRUE;
            break;
        } else {
            g->rays->xintercept += g->rays->xstep;
            g->rays->yintercept += g->rays->ystep;
        }
    }
}

void castRay(t_data *g, double rayAngle) {
	rayDir(g, rayAngle);
	calHorRay(g, rayAngle);
	calVerRay(g, rayAngle);
	compare_hv_distance(g, rayAngle);
  shot_ray(g, g->rays->stripId);
  draw_line(g, (g->player->x + P_ERROR), (g->player->y + P_ERROR), g->rays->wallHitX, g->rays->wallHitY);
}

void	cast_rays(t_data *g)
{
	double fov_angle = (50 * (PI / 180));
	double rayAngle = g->player->rotation_angle - (fov_angle / 2);
	g->rays = (t_ray *)malloc(sizeof(t_ray));
    draw_bg(g);
	for (int col = 0; col < WIDTH; col++) {
		ft_memset(g->rays, 0, sizeof(t_ray));
		rayAngle += fov_angle / WIDTH;
        g->rays->stripId = col;
		castRay(g, rayAngle);
	}
	free(g->rays);
}