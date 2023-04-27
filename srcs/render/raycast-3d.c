#include "cub3d.h"

//need to fix, crash when trying to fill screen.
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
	float	lineOff;
	float		constant;
	t_vec	start;
	t_vec	end;

	/*
		missing one ray because dividing normally doesnt return whole value,
		and will round down.
	*/
	constant = (g->winsize.x / g->fovdeg) + 0.67; //WTF WHY .675
	printf("\nconstant %f\n", constant);
	lineH = (g->winsize.y * CELL_SIZE) / dist;
	if (lineH > g->winsize.y)
		lineH = g->winsize.y;
	lineOff = (g->winsize.y / 2) - lineH / 2;
	start = (t_vec){.x = (r * constant), .y = lineOff};
	printf("start: %d, %d\n", start.x, start.y);
	end = (t_vec){.x = (r * constant), .y = lineOff + lineH};
	printf("end: %d, %d\n", end.x, end.y);

	draw_3d(g, roundf(constant), start, end);
}