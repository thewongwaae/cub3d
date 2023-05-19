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
	(void) g;
	// if (g->p.door == true && g->ray.perp_dist < 21
	// 	&& (g->p.map_pos.x != g->p.its.x && g->p.map_pos.y != g->p.its.y))
	// {
	// 	if (g->map[g->p.its.y][g->p.its.x] == '2')
	// 		g->map[g->p.its.y][g->p.its.x] = '3';
	// 	if (g->map[g->p.its.y][g->p.its.x] == '3')
	// 		g->map[g->p.its.y][g->p.its.x] = '2';
	// }
}
