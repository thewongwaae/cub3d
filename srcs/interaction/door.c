#include "cub3d.h"

void	open_door( t_game *g )
{
	if (g->p.dist < 16)
	{
		// open the door nearest to the player
		g->moved = 1;
	}
}
