#include "../srcs/cub3d.h"

void    draw_bg(t_data *g)
{
    int i;
    int j;

    i = 0;
    while (i < HEIGHT / 2)
    {
        j = 0;
        while (j < WIDTH)
        {
            put_pixel_to_screen(g, j, i, 0XddFFFF);
            ++j;
        }
        ++i;
    }
    while (i < HEIGHT)
    {
        j = 0;
        while (j < WIDTH)
        {
            put_pixel_to_screen(g, j, i, 0X22BB44);
            ++j;
        }
        ++i;
    }
}

void    shot_ray(t_data *g, int stripId)
{
    double wall_size = HEIGHT / g->rays[stripId].distance;
    wall_size *= 10;
		int wallTopPixel = (HEIGHT / 2) - (wall_size / 2);
		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

		int wallBottomPixel = (HEIGHT / 2) + (wall_size / 2);
		wallBottomPixel = wallBottomPixel > HEIGHT ? HEIGHT : wallBottomPixel;


    double put_start = HEIGHT / 2 - wall_size / 2 - 2;

		int textureOffsetX;
		if (g->rays[stripId].wasHitVertical)
			textureOffsetX = (int)g->rays[stripId].wallHitY % MINI_TILE;
		else
			textureOffsetX = (int)g->rays[stripId].wallHitX % MINI_TILE;
		textureOffsetX *= 200 / MINI_TILE;
		int tex_w = g->map_info->tex.w;
		int tex_h = g->map_info->tex.h;

		for (int y = wallTopPixel; y < wallBottomPixel; y++) {
				int distanceFromTop = y + (wall_size / 2) - (HEIGHT / 2);
				int textureOffsetY = distanceFromTop * ((float)tex_h / wall_size);
				put_pixel_to_screen(g, stripId, y, g->map_info->tex.addr[(tex_w * textureOffsetY) + textureOffsetX]);
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
    if (mapGridIndexX < 0 || mapGridIndexX >= g->map_info->w || mapGridIndexY < 0 || mapGridIndexY >= g->map_info->h) {
        return FALSE;
    }
    if(g->map_info->map[mapGridIndexY][mapGridIndexX] == '1')
				return TRUE;
		return FALSE;
}
// 
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

void castRay(t_data *g, double rayAngle, int stripId) {
    //각도 정규화
    rayAngle = normalizeAngle(rayAngle);

    //레이 방향 상하좌우 중 어디로 향하는지 
    g->rays[stripId].isRayFacingDown = rayAngle > 0 && rayAngle < PI;
    g->rays[stripId].isRayFacingUp = !g->rays[stripId].isRayFacingDown;

    g->rays[stripId].isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
    g->rays[stripId].isRayFacingLeft = !g->rays[stripId].isRayFacingRight;

    ///////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    g->rays[stripId].foundHorzWallHit = FALSE;
    g->rays[stripId].horzWallHitX = 0;
    g->rays[stripId].horzWallHitY = 0;
    g->rays[stripId].horzWallContent = 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    g->rays[stripId].yintercept = floor((g->player->y + P_ERROR) / MINI_TILE) * MINI_TILE;
    g->rays[stripId].yintercept += g->rays[stripId].isRayFacingDown ? MINI_TILE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    g->rays[stripId].xintercept = (g->player->x + P_ERROR) + (g->rays[stripId].yintercept - (g->player->y + P_ERROR)) / tan(rayAngle);

    // Calculate the increment xstep and ystep
    g->rays[stripId].ystep = MINI_TILE;
    g->rays[stripId].ystep *= g->rays[stripId].isRayFacingUp ? -1 : 1;

    g->rays[stripId].xstep = MINI_TILE / tan(rayAngle);
    g->rays[stripId].xstep *= (g->rays[stripId].isRayFacingLeft && g->rays[stripId].xstep > 0) ? -1 : 1;
    g->rays[stripId].xstep *= (g->rays[stripId].isRayFacingRight && g->rays[stripId].xstep < 0) ? -1 : 1;

    g->rays[stripId].nextHorzTouchX = g->rays[stripId].xintercept;
    g->rays[stripId].nextHorzTouchY = g->rays[stripId].yintercept;

    // Increment xstep and ystep until we find a wall
    while (g->rays[stripId].nextHorzTouchX >= 0 && g->rays[stripId].nextHorzTouchX <= WIDTH && g->rays[stripId].nextHorzTouchY >= 0 && g->rays[stripId].nextHorzTouchY <= HEIGHT) {
        g->rays[stripId].xToCheck = g->rays[stripId].nextHorzTouchX;
        g->rays[stripId].yToCheck = g->rays[stripId].nextHorzTouchY + (g->rays[stripId].isRayFacingUp ? -1 : 0);

        if (mapHasWallAt(g, g->rays[stripId].xToCheck, g->rays[stripId].yToCheck)) {
            // found a wall hit
            g->rays[stripId].horzWallHitX = g->rays[stripId].nextHorzTouchX;
            g->rays[stripId].horzWallHitY = g->rays[stripId].nextHorzTouchY;
            g->rays[stripId].horzWallContent = g->map_info->map[(int)floor(g->rays[stripId].yToCheck / MINI_TILE)][(int)floor(g->rays[stripId].xToCheck / MINI_TILE)];
            g->rays[stripId].foundHorzWallHit = TRUE;
            break;
        } else {
            g->rays[stripId].nextHorzTouchX += g->rays[stripId].xstep;
            g->rays[stripId].nextHorzTouchY += g->rays[stripId].ystep;
        }
    }

    ///////////////////////////////////////////
    // VERTICAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////

    // Find the x-coordinate of the closest horizontal grid intersection
    g->rays[stripId].xintercept = floor((g->player->x + P_ERROR) / MINI_TILE) * MINI_TILE;
    g->rays[stripId].xintercept += g->rays[stripId].isRayFacingRight ? MINI_TILE : 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    g->rays[stripId].yintercept = (g->player->y + P_ERROR) + (g->rays[stripId].xintercept - (g->player->x + P_ERROR)) * tan(rayAngle);

    // Calculate the increment xstep and ystep
    g->rays[stripId].xstep = MINI_TILE;
    g->rays[stripId].xstep *= g->rays[stripId].isRayFacingLeft ? -1 : 1;

    g->rays[stripId].ystep = MINI_TILE * tan(rayAngle);
    g->rays[stripId].ystep *= (g->rays[stripId].isRayFacingUp && g->rays[stripId].ystep > 0) ? -1 : 1;
    g->rays[stripId].ystep *= (g->rays[stripId].isRayFacingDown && g->rays[stripId].ystep < 0) ? -1 : 1;

    g->rays[stripId].nextVertTouchX = g->rays[stripId].xintercept;
    g->rays[stripId].nextVertTouchY = g->rays[stripId].yintercept;

    // Increment xstep and ystep until we find a wall
    while (g->rays[stripId].nextVertTouchX >= 0 && g->rays[stripId].nextVertTouchX <= WIDTH && g->rays[stripId].nextVertTouchY >= 0 && g->rays[stripId].nextVertTouchY <= HEIGHT) {
        g->rays[stripId].xToCheck = g->rays[stripId].nextVertTouchX + (g->rays[stripId].isRayFacingLeft ? -1 : 0);
        g->rays[stripId].yToCheck = g->rays[stripId].nextVertTouchY;

        if (mapHasWallAt(g, g->rays[stripId].xToCheck, g->rays[stripId].yToCheck)) {
            // found a wall hit
            g->rays[stripId].vertWallHitX = g->rays[stripId].nextVertTouchX;
            g->rays[stripId].vertWallHitY = g->rays[stripId].nextVertTouchY;
            g->rays[stripId].vertWallContent = g->map_info->map[(int)floor(g->rays[stripId].yToCheck / MINI_TILE)][(int)floor(g->rays[stripId].xToCheck / MINI_TILE)];
            g->rays[stripId].foundVertWallHit = TRUE;
            break;
        } else {
            g->rays[stripId].nextVertTouchX += g->rays[stripId].xstep;
            g->rays[stripId].nextVertTouchY += g->rays[stripId].ystep;
        }
    }

    // Calculate both horizontal and vertical hit distances and choose the smallest one
		g->rays[stripId].horzHitDistance = g->rays[stripId].foundHorzWallHit
				? distanceBetweenPoints((g->player->x + P_ERROR), (g->player->y + P_ERROR), g->rays[stripId].horzWallHitX, g->rays[stripId].horzWallHitY)
				: FLT_MAX;
		g->rays[stripId].horzHitDistance *= cos(rayAngle - g->player->rotation_angle);

		g->rays[stripId].vertHitDistance = g->rays[stripId].foundVertWallHit
				? distanceBetweenPoints((g->player->x + P_ERROR), (g->player->y + P_ERROR), g->rays[stripId].vertWallHitX, g->rays[stripId].vertWallHitY)
				: FLT_MAX;
		g->rays[stripId].vertHitDistance *= cos(rayAngle - g->player->rotation_angle);


    if (g->rays[stripId].vertHitDistance < g->rays[stripId].horzHitDistance) {
        g->rays[stripId].distance = g->rays[stripId].vertHitDistance;
        g->rays[stripId].wallHitX = g->rays[stripId].vertWallHitX;
        g->rays[stripId].wallHitY = g->rays[stripId].vertWallHitY;
        g->rays[stripId].wallHitContent = g->rays[stripId].vertWallContent;
        g->rays[stripId].wasHitVertical = TRUE;
    } else {
        g->rays[stripId].distance = g->rays[stripId].horzHitDistance;
        g->rays[stripId].wallHitX = g->rays[stripId].horzWallHitX;
        g->rays[stripId].wallHitY = g->rays[stripId].horzWallHitY;
        g->rays[stripId].wallHitContent = g->rays[stripId].horzWallContent;
        g->rays[stripId].wasHitVertical = FALSE;
    }
    g->rays[stripId].rayAngle = rayAngle;
    g->rays[stripId].isRayFacingDown = g->rays[stripId].isRayFacingDown;
    g->rays[stripId].isRayFacingUp = g->rays[stripId].isRayFacingUp;
    g->rays[stripId].isRayFacingLeft = g->rays[stripId].isRayFacingLeft;
    g->rays[stripId].isRayFacingRight = g->rays[stripId].isRayFacingRight;
        shot_ray(g, stripId);
        draw_line(g, (g->player->x + P_ERROR), (g->player->y + P_ERROR), g->rays[stripId].wallHitX, g->rays[stripId].wallHitY);
}

void	cast_rays(t_data *g)
{
	double fov_angle = (50 * (PI / 180));
	double rayAngle = g->player->rotation_angle - (fov_angle / 2);
	g->rays = (t_ray *)malloc(sizeof(t_ray) * NUM_RAYS);
    	draw_bg(g);
    g->map_info->tex.img = mlx_xpm_file_to_image(g->mlx, "./asset/this.xpm",&g->map_info->tex.w, &g->map_info->tex.h);
    g->map_info->tex.addr = (int *)mlx_get_data_addr(g->map_info->tex.img, &g->map_info->tex.bpp, &g->map_info->tex.line_len, &g->map_info->tex.endian);
	for (int col = 0; col < WIDTH; col++) {
		rayAngle += fov_angle / WIDTH;
		castRay(g, rayAngle, col);
	}
}