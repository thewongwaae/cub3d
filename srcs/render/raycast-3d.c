#include "cub3d.h"

/*
	Apply a simple formula to fix the fisheye effect caused by
	purely using raycast distance
*/
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

/*
	Draw a 1 pixel wide column with specified
	start and end pixel coordinates
*/
static void	draw_line(t_game *g, t_vecd start, t_vecd end)
{
	while(start.y <= end.y)
	{
		my_pp(g->bg, (int)(start.x), (int)(start.y), PURPLE);
		start.y += 1.0;
	}
}

/*
	r = ray count
	lineOff = offset 3d-cast to center of screen
*/
void	draw_column(t_game *g, double dist, int r, double angle)
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
	draw_line(g, start, end);
}
