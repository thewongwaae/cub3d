#include "cub3d.h"

/*
	On user input of the "space" bar
	Check whether the player is near to wall/door
	Check whether player is near a door or wall
	If door,
		change 
*/
void	open_door( t_game *g )
{
	if (g->p.dist < 21)
	{
		if (g->map[g->p.its.y][g->p.its.x] == '2')
			g->map[g->p.its.y][g->p.its.x] = '3';
		else if (g->map[g->p.its.y][g->p.its.x] == '3')
			g->map[g->p.its.y][g->p.its.x] = '2';
		printf("door interacted\n");
		g->moved = 1;
		render_minimap(g);
	}
}
