#include "../srcs/cub3d.h"

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
		put_pixel_to_screen(g, x0, y0, 0x00FF00FF); // white color
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

int mapHasWallAt(t_data *g, float x, float y) {
    int mapGridIndexX = floor(x / MINI_TILE);
    int mapGridIndexY = floor(y / MINI_TILE);
    if (mapGridIndexX < 0 || mapGridIndexX >= g->map_info->w || mapGridIndexY < 0 || mapGridIndexY >= g->map_info->h) {
        return FALSE;
    }
    if(g->map_info->map[mapGridIndexY][mapGridIndexX] == '1')
				return TRUE;
		return FALSE;
}

float normalizeAngle(float angle) {
    angle = remainder(angle, 2 * PI);
    if (angle < 0) {
        angle = 2 * PI + angle;
    }
    return angle;
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void castRay(t_data *g, float rayAngle, int stripId) {
    rayAngle = normalizeAngle(rayAngle);

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
    g->rays[stripId].yintercept = floor(g->player->y / MINI_TILE) * MINI_TILE;
    g->rays[stripId].yintercept += g->rays[stripId].isRayFacingDown ? MINI_TILE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    g->rays[stripId].xintercept = g->player->x + (g->rays[stripId].yintercept - g->player->y) / tan(rayAngle);

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
    g->rays[stripId].xintercept = floor(g->player->x / MINI_TILE) * MINI_TILE;
    g->rays[stripId].xintercept += g->rays[stripId].isRayFacingRight ? MINI_TILE : 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    g->rays[stripId].yintercept = g->player->y + (g->rays[stripId].xintercept - g->player->x) * tan(rayAngle);

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
        ? distanceBetweenPoints(g->player->x, g->player->y, g->rays[stripId].horzWallHitX, g->rays[stripId].horzWallHitY)
        : FLT_MAX;
    g->rays[stripId].vertHitDistance = g->rays[stripId].foundVertWallHit
        ? distanceBetweenPoints(g->player->x, g->player->y, g->rays[stripId].vertWallHitX, g->rays[stripId].vertWallHitY)
        : FLT_MAX;

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
		draw_line(g, g->player->x + 7, g->player->y + 7, g->rays[stripId].wallHitX, g->rays[stripId].wallHitY);
}

void	cast_rays(t_data *g)
{
	float rayAngle = g->player->rotation_angle - (FOV_ANGLE / 2);
	g->rays = (t_ray *)malloc(sizeof(t_ray) * NUM_RAYS);
	for (int col = 0; col < NUM_RAYS; col++) {
			rayAngle += FOV_ANGLE / NUM_RAYS;
			castRay(g, rayAngle, col);
	}
}