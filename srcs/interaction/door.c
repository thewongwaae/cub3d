#include "cub3d.h"

void	set_door( t_game *g, t_vec map_pos )
{
	if (map_pos.x == g->door.pos.x
		&& map_pos.y == g->door.pos.y)
		return ;
	g->door.pos = map_pos;
}

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
	if (g->door.dist == INT16_MAX)
		return ;
	if (g->door.dist < 21)
	{
		if (g->map[g->door.pos.y][g->door.pos.x] == '2')
			g->map[g->door.pos.y][g->door.pos.x] = '3';
		if (g->map[g->door.pos.y][g->door.pos.x] == '3')
			g->map[g->door.pos.y][g->door.pos.x] = '2';
	}
}
