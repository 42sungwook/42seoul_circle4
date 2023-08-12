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
    ///////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    g->rays->foundHorzWallHit = FALSE;
    g->rays->horzWallHitX = 0;
    g->rays->horzWallHitY = 0;
    g->rays->horzWallContent = 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    g->rays->yintercept = floor((g->player->y + P_ERROR) / MINI_TILE) * MINI_TILE;
    g->rays->yintercept += g->rays->isRayFacingDown ? MINI_TILE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    g->rays->xintercept = (g->player->x + P_ERROR) + (g->rays->yintercept - (g->player->y + P_ERROR)) / tan(rayAngle);

    // Calculate the increment xstep and ystep
    g->rays->ystep = MINI_TILE;
    g->rays->ystep *= g->rays->isRayFacingUp ? -1 : 1;

    g->rays->xstep = MINI_TILE / tan(rayAngle);
    g->rays->xstep *= (g->rays->isRayFacingLeft && g->rays->xstep > 0) ? -1 : 1;
    g->rays->xstep *= (g->rays->isRayFacingRight && g->rays->xstep < 0) ? -1 : 1;

    g->rays->nextHorzTouchX = g->rays->xintercept;
    g->rays->nextHorzTouchY = g->rays->yintercept;

    // Increment xstep and ystep until we find a wall
    while (g->rays->nextHorzTouchX >= 0 && g->rays->nextHorzTouchX < g->map_info->w * MINI_TILE && g->rays->nextHorzTouchY >= 0 && g->rays->nextHorzTouchY < g->map_info->h * MINI_TILE) {
        g->rays->xToCheck = g->rays->nextHorzTouchX;
        g->rays->yToCheck = g->rays->nextHorzTouchY + (g->rays->isRayFacingUp ? -1 : 0);

        if (mapHasWallAt(g, g->rays->xToCheck, g->rays->yToCheck)) {
            // found a wall hit
            g->rays->horzWallHitX = g->rays->nextHorzTouchX;
            g->rays->horzWallHitY = g->rays->nextHorzTouchY;
            g->rays->horzWallContent = g->map_info->map[(int)floor(g->rays->yToCheck / MINI_TILE)][(int)floor(g->rays->xToCheck / MINI_TILE)];
            g->rays->foundHorzWallHit = TRUE;
            break;
        } else {
            g->rays->nextHorzTouchX += g->rays->xstep;
            g->rays->nextHorzTouchY += g->rays->ystep;
        }
    }
}

void calVerRay(t_data *g, double rayAngle)
{
    ///////////////////////////////////////////
    // VERTICAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////

    // Find the x-coordinate of the closest horizontal grid intersection
    g->rays->xintercept = floor((g->player->x + P_ERROR) / MINI_TILE) * MINI_TILE;
    g->rays->xintercept += g->rays->isRayFacingRight ? MINI_TILE : 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    g->rays->yintercept = (g->player->y + P_ERROR) + (g->rays->xintercept - (g->player->x + P_ERROR)) * tan(rayAngle);

    // Calculate the increment xstep and ystep
    g->rays->xstep = MINI_TILE;
    g->rays->xstep *= g->rays->isRayFacingLeft ? -1 : 1;

    g->rays->ystep = MINI_TILE * tan(rayAngle);
    g->rays->ystep *= (g->rays->isRayFacingUp && g->rays->ystep > 0) ? -1 : 1;
    g->rays->ystep *= (g->rays->isRayFacingDown && g->rays->ystep < 0) ? -1 : 1;

    g->rays->nextVertTouchX = g->rays->xintercept;
    g->rays->nextVertTouchY = g->rays->yintercept;

    // Increment xstep and ystep until we find a wall
    while (g->rays->nextVertTouchX >= 0 && g->rays->nextVertTouchX < g->map_info->w * MINI_TILE && g->rays->nextVertTouchY >= 0 && g->rays->nextVertTouchY < g->map_info->h * MINI_TILE) {
        g->rays->xToCheck = g->rays->nextVertTouchX + (g->rays->isRayFacingLeft ? -1 : 0);
        g->rays->yToCheck = g->rays->nextVertTouchY;

        if (mapHasWallAt(g, g->rays->xToCheck, g->rays->yToCheck)) {
            // found a wall hit
            g->rays->vertWallHitX = g->rays->nextVertTouchX;
            g->rays->vertWallHitY = g->rays->nextVertTouchY;
            g->rays->vertWallContent = g->map_info->map[(int)floor(g->rays->yToCheck / MINI_TILE)][(int)floor(g->rays->xToCheck / MINI_TILE)];
            g->rays->foundVertWallHit = TRUE;
            break;
        } else {
            g->rays->nextVertTouchX += g->rays->xstep;
            g->rays->nextVertTouchY += g->rays->ystep;
        }
    }
}

void castRay(t_data *g, double rayAngle) {
	rayDir(g, rayAngle);
	calHorRay(g, rayAngle);
	calVerRay(g, rayAngle);
    // Calculate both horizontal and vertical hit distances and choose the smallest one
		g->rays->horzHitDistance = g->rays->foundHorzWallHit
				? distanceBetweenPoints((g->player->x + P_ERROR), (g->player->y + P_ERROR), g->rays->horzWallHitX, g->rays->horzWallHitY)
				: FLT_MAX;
		g->rays->horzHitDistance *= cos(rayAngle - g->player->rotation_angle);

		g->rays->vertHitDistance = g->rays->foundVertWallHit
				? distanceBetweenPoints((g->player->x + P_ERROR), (g->player->y + P_ERROR), g->rays->vertWallHitX, g->rays->vertWallHitY)
				: FLT_MAX;
		g->rays->vertHitDistance *= cos(rayAngle - g->player->rotation_angle);
    if (g->rays->vertHitDistance < g->rays->horzHitDistance) {
        g->rays->distance = g->rays->vertHitDistance;
        g->rays->wallHitX = g->rays->vertWallHitX;
        g->rays->wallHitY = g->rays->vertWallHitY;
        g->rays->wallHitContent = g->rays->vertWallContent;
        g->rays->wasHitVertical = TRUE;
    } else {
        g->rays->distance = g->rays->horzHitDistance;
        g->rays->wallHitX = g->rays->horzWallHitX;
        g->rays->wallHitY = g->rays->horzWallHitY;
        g->rays->wallHitContent = g->rays->horzWallContent;
        g->rays->wasHitVertical = FALSE;
    }
    g->rays->rayAngle = rayAngle;
    g->rays->isRayFacingDown = g->rays->isRayFacingDown;
    g->rays->isRayFacingUp = g->rays->isRayFacingUp;
    g->rays->isRayFacingLeft = g->rays->isRayFacingLeft;
    g->rays->isRayFacingRight = g->rays->isRayFacingRight;
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