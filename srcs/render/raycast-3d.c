#include "cub3d.h"

static float	fix_fisheye(t_game *g, float angle, int dist)
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
static void	draw_3d(t_game *g, int constant, t_vec start, t_vec end)
{
	int ray_w;
	int	ray_h;
	int	ray_w_end;

	ray_w = start.x;
	ray_w_end = (int)(start.x + constant + 0.5f);
	while (ray_w < ray_w_end)
	{
		ray_h = start.y;
		while(ray_h <= end.y)
			my_pp(g->bg, ray_w, ray_h++, PURPLE);
		ray_w++;
	}
}

static void	check_bounds( t_vec winsize, t_vec *p )
{
	if (p->x < 0)
		p->x = 0;
	if (p->y < 0)
		p->y = 0;
	if (p->x > winsize.x)
		p->x = winsize.x;
	if (p->y > winsize.y)
		p->y = winsize.y;
}

/*
	r = ray count
	lineOff = offset 3d-cast to center of screen
*/
void	cast_3d(t_game *g, int dist, int r, float angle)
{
	float	lineH;
	float	lineOff;
	float		constant;
	t_vec	start;
	t_vec	end;

	(void) angle;
	dist = fix_fisheye(g, angle, dist);
	/*
		missing one ray because dividing normally doesnt return whole value,
		and will round down.
	*/
	constant = ((float)g->winsize.x / (float)g->fovdeg);
	lineH = ((float)g->winsize.y * (float)CELL_SIZE) / (float)dist;
	if (lineH > g->winsize.y)
		lineH = g->winsize.y;
	lineOff = ((float)g->winsize.y / 2.0f) - lineH / 2;
	start = (t_vec){.x = (int)(r * constant), .y = (int)lineOff};
	check_bounds(g->winsize, &start);
	end = (t_vec){.x = (int)(r * constant), .y = (int)(lineOff + lineH)};
	check_bounds(g->winsize, &end);
	draw_3d(g, (int)(constant + 0.5f), start, end);
}