#include "cub3d.h"

int	move( int keycode, t_game *game )
{
	if (keycode == 13 || keycode == 126)
		forward();
	else if (keycode == 0 || keycode == 123)
		left();
	else if (keycode == 1 || keycode == 125)
		backward();
	else if (keycode == 2 || keycode == 124)
		right();
	else if (keycode == 53)
		endgame();
	return (0);
}
