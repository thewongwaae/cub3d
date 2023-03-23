#include "cub3d.h"

int	move( int keycode, t_game *game )
{
	if (keycode == 13 || keycode == 126)
		// handle for up / forward
		forward();
	else if (keycode == 0 || keycode == 123)
		// handle left
		left();
	else if (keycode == 1 || keycode == 125)
		// handle down / backwards
		backward();
	else if (keycode == 2 || keycode == 124)
		// handle right
		right();
	else if (keycode == 53)
		// handle end
		endgame();
	return (0);
}
