#include "cub3d.h"

int	mouse_hook( int x, int y, t_game *game )
{
	static int	prev_x = -1;
	int			dx;

	(void) y;
	if (prev_x == -1)
		prev_x = x;
	dx = x - prev_x;
	if (abs(dx) > 5)
	{
		game->p.pa += dx * 0.0005;
		if (game->p.pa < 0)
			game->p.pa += 2 * M_PI;
		if (game->p.pa > 2 * M_PI)
			game->p.pa -= 2 * M_PI;
		game->p.pdx = cos(game->p.pa) * 3;
		game->p.pdy = -sin(game->p.pa) * 3;
		game->moved = 1;
		prev_x = x;
	}
	return (0);
}