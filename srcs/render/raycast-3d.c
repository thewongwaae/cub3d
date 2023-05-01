#include "cub3d.h"

static float	fix_fisheye(t_game *g, float angle, float dist)
{
	float	fisheye;
	float	new_dist;

	fisheye = g->p.pa - angle;
	if (fisheye < 0)
		fisheye += 2 * M_PI;
	if (fisheye > 2 * M_PI)
		fisheye -= 2 * M_PI;
	new_dist = dist * cos(fisheye);
	return (new_dist);
}

//need to fix, crash when trying to fill screen.
static void	draw_3d(t_game *g, float constant, t_vecf start, t_vecf end)
{
	float	ray_w;
	float	ray_h;
	float	ray_w_end;

	ray_w = start.x;
	ray_w_end = start.x + constant;
	while (ray_w < ray_w_end)
	{
		ray_h = start.y;
		while(ray_h <= end.y)
		{
			my_pp(g->bg, roundf(ray_w), roundf(ray_h), PURPLE);
			ray_h += 1.0f;
		}
		ray_w += 1.0f;
	}
}

/*
	r = ray count
	lineOff = offset 3d-cast to center of screen
*/
void	cast_3d(t_game *g, float dist, int r, float angle)
{
	float	lineH;
	float	lineOff;
	float	constant;
	t_vecf	start;
	t_vecf	end;

	dist = fix_fisheye(g, angle, dist);
	constant = (float)g->winsize.x / (float)g->fovdeg;
	lineH = ((float)g->winsize.y * (float)CELL_SIZE) / (float)dist;
	if (lineH > (float)g->winsize.y)
		lineH = (float)g->winsize.y;
	lineOff = ((float)g->winsize.y / 2.0f) - lineH / 2.0f;
	start = (t_vecf){.x = (float)r * constant, .y = lineOff};
	end = (t_vecf){.x = (float)r * constant, .y = lineOff + lineH};
	draw_3d(g, constant, start, end);
}
