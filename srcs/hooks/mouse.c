#include "cub3d.h"

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
		mlx_mouse_hide();
		g->p.pa += dx * 0.005;
		if (g->p.pa < 0)
			g->p.pa += 2 * M_PI;
		if (g->p.pa > 2 * M_PI)
			g->p.pa -= 2 * M_PI;
		g->p.pdx = cos(g->p.pa) * 3;
		g->p.pdy = -sin(g->p.pa) * 3;
		g->moved = true;
		prev_x = x;
		mlx_mouse_move(g->win, g->winsize.x / 2, g->winsize.y / 2);
	}
	return (0);
}
