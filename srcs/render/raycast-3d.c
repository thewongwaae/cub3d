#include "cub3d.h"

static double	fix_fisheye(t_game *g, double angle, double dist)
{
	double	fisheye;
	double	new_dist;

	fisheye = g->p.pa - angle;
	if (fisheye < 0)
		fisheye += 2.0 * M_PI;
	if (fisheye > 2.0 * M_PI)
		fisheye -= 2.0 * M_PI;
	new_dist = dist * cos(fisheye);
	return (new_dist);
}

//need to fix, crash when trying to fill screen.
static void	draw_3d(t_game *g, t_vecd start, t_vecd end)
{
	double	ray_w;
	double	ray_h;
	double	ray_w_end;

	ray_w = start.x;
	ray_w_end = start.x + 1.0;
	while (ray_w < ray_w_end)
	{
		ray_h = start.y;
		while(ray_h <= end.y)
		{
			my_pp(g->bg, (int)(ray_w), (int)(ray_h), PURPLE);
			ray_h += 1.0;
		}
		ray_w += 1.0;
	}
}

/*
	r = ray count
	lineOff = offset 3d-cast to center of screen
*/
void	cast_3d(t_game *g, double dist, int r, double angle)
{
	double	lineH;
	double	lineOff;
	t_vecd	start;
	t_vecd	end;

	dist = fix_fisheye(g, angle, dist);
	lineH = ((double)g->winsize.y * (double)CELL_SIZE) / (double)dist;
	if (lineH > (double)g->winsize.y)
		lineH = (double)g->winsize.y;
	lineOff = ((double)g->winsize.y / 2.0) - lineH / 2.0;
	start = (t_vecd){.x = (double)r, .y = lineOff};
	end = (t_vecd){.x = (double)r, .y = lineOff + lineH};
	draw_3d(g, start, end);
}
