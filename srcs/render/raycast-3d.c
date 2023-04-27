#include "cub3d.h"

static void	draw_3d(t_game *g, int constant, t_vec start, t_vec end)
{
	int ray_w;
	int	ray_h;

	ray_w = start.x;
	while (ray_w < start.x + constant)
	{
		ray_h = start.y;
		while(ray_h <= end.y)
			my_pp(g->bg, ray_w, ray_h++, DGREEN);
		ray_w++;
	}
}

/*
	r = ray count
	lineOff = offset 3d-cast to center of screen
*/
void	cast_3d(t_game *g, int dist, int r)
{
	float	lineH;
	// float	lineOff;
	int		constant;
	t_vec	start;
	t_vec	end;

	constant = g->winsize.x / g->fovdeg;
	lineH = g->winsize.y / dist * 10;
	if (lineH > 320)
		lineH = g->winsize.y;
	// lineOff = (g->winsize.y / 2) - lineH / 2;
	start = (t_vec){.x = (r * constant), .y = 0};
	end = (t_vec){.x = (r * constant), .y = lineH};

	draw_3d(g, constant, start, end);
}