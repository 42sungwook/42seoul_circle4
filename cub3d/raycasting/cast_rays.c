#include "../srcs/cub3d.h"
//  배경색 그리기 - 나중에 draw.c로 이동
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
		int tex_w = g->map_info->tex.w;
		int tex_h = g->map_info->tex.h;

		for (int y = wallTopPixel; y < wallBottomPixel; y++) {
				int distanceFromTop = y + (wall_size / 2) - (HEIGHT / 2);
				int textureOffsetY = distanceFromTop * ((float)tex_h / wall_size);
                //동서남북 텍스쳐 결정
                if (g->rays->wasHitVertical)
                {
                    if ((g->rays->isRayFacingLeft))
                        put_pixel_to_screen(g, stripId, y, g->imgs[WEST].addr[(g->imgs[WEST].w * (textureOffsetY + 1 )) - textureOffsetX]);
                    else
                        put_pixel_to_screen(g, stripId, y, g->imgs[EAST].addr[(g->imgs[EAST].w * textureOffsetY) + textureOffsetX]);

                }
                else
                {
                    if ((g->rays->isRayFacingDown))
                        put_pixel_to_screen(g, stripId, y, g->imgs[SOUTH].addr[(g->imgs[SOUTH].w * (textureOffsetY + 1)) - textureOffsetX ]);
                    else
                        put_pixel_to_screen(g, stripId, y, g->imgs[NORTH].addr[(g->imgs[NORTH].w * textureOffsetY) + textureOffsetX]);
                }
}
		}

void	draw_line(t_data *g, int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while (1)
	{
		put_pixel_to_minimap(g, x0, y0, 0x00FF00FF);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}

int mapHasWallAt(t_data *g, double x, double y) {
    int mapGridIndexX = floor(x / MINI_TILE);
    int mapGridIndexY = floor(y / MINI_TILE);
    if (mapGridIndexX < 0 || mapGridIndexX > g->map_info->w || mapGridIndexY < 0 || mapGridIndexY > g->map_info->h) {
        return FALSE;
    }
    if(g->map_info->map[mapGridIndexY][mapGridIndexX] == '1')
				return TRUE;
		return FALSE;
}

double normalizeAngle(double angle) {
	while (angle >= 2 * PI) 
	{
		angle -= 2 * PI;
	}
	while (angle < 0)
	{
			angle += 2 * PI;
	}
	return angle;
}
// 두 점 사이 거리 계산
double distanceBetweenPoints(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void castRay(t_data *g, double rayAngle) {
    //각도 정규화
    rayAngle = normalizeAngle(rayAngle);

    //레이 방향 상하좌우 중 어디로 향하는지 
    g->rays->isRayFacingDown = rayAngle > 0 && rayAngle < PI;
    g->rays->isRayFacingUp = !g->rays->isRayFacingDown;

    g->rays->isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
    g->rays->isRayFacingLeft = !g->rays->isRayFacingRight;

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
    g->map_info->tex.img = mlx_xpm_file_to_image(g->mlx, "./asset/this.xpm",&g->map_info->tex.w, &g->map_info->tex.h);
    g->map_info->tex.addr = (int *)mlx_get_data_addr(g->map_info->tex.img, &g->map_info->tex.bpp, &g->map_info->tex.line_len, &g->map_info->tex.endian);
	for (int col = 0; col < WIDTH; col++) {
		ft_memset(g->rays, 0, sizeof(t_ray));
		rayAngle += fov_angle / WIDTH;
        g->rays->stripId = col;
		castRay(g, rayAngle);
	}
	free(g->rays);
}