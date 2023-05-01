#include "cub3d.h"

/*
	On user input of the "space" bar
	Check whether the player is near to wall/door
	Check whether player is near a door or wall
	If closed door,
		change to opened door
	If opened door,
		chage to closed door

	ISSUE: door interacts when player is 20 pixels or smaller
	near wall after door position coordinates have been taken
	FIX: take note of what block player is currently facing.
	perhaps change use of 'its'
*/
void	open_door( t_game *g )
{
	if (g->p.dist < 21 && (g->map[g->p.its.y][g->p.its.x] == '2'
		|| g->map[g->p.its.y][g->p.its.x] == '3'))
	{
		if (g->map[g->p.its.y][g->p.its.x] == '2')
			g->map[g->p.its.y][g->p.its.x] = '3';
		else if (g->map[g->p.its.y][g->p.its.x] == '3')
			g->map[g->p.its.y][g->p.its.x] = '2';
		g->moved = 1;
		render_minimap(g);
	}
}
