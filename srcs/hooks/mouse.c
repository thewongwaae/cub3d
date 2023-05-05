#include "cub3d.h"

static void	change_angle( int dx, t_game *g )
{
	g->p.pa -= (double)dx * 0.0025;
	if (g->p.pa < 0)
		g->p.pa += 2 * M_PI;
	if (g->p.pa > 2 * M_PI)
		g->p.pa -= 2 * M_PI;
	g->p.pdx = cos(g->p.pa) * 1.5;
	g->p.pdy = -sin(g->p.pa) * 1.5;
}

/*
	Changes player angle value based on mouse-x
*/
int	mouse_hook( int x, int y, t_game *g )
{
	static int	prev_x = -1;
	int			dx;

	(void) y;
	if (prev_x == -1)
		prev_x = x;
	dx = x - prev_x;
	if (abs(dx) > 5)
	{
		change_angle(dx, g);
		g->moved = true;
		prev_x = x;
	}
	return (0);
}
