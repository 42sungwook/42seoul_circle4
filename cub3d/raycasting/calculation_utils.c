#include "../srcs/cub3d.h"

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

double distanceBetweenPoints(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void rayDir(t_data *g, double rayAngle)
{
    //각도 정규화
    rayAngle = normalizeAngle(rayAngle);

    //레이 방향 상하좌우 중 어디로 향하는지 
    g->rays->isRayFacingDown = rayAngle > 0 && rayAngle < PI;
    g->rays->isRayFacingUp = !g->rays->isRayFacingDown;

    g->rays->isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
    g->rays->isRayFacingLeft = !g->rays->isRayFacingRight;
}