#include "cub3d.h"

/*
	Moves player forward taking into consideration
	the current player angle
*/
void	forward( t_game *g )
{
	t_vecd	new;
	t_vec	new_map;

	if (g->key.up == true)
	{
		new.x = g->p.pix.x + g->p.pdir.x * 2;
		new_map.x = (int)(new.x / CELL_SIZE);
		new.y = g->p.pix.y + g->p.pdir.y * 2;
		new_map.y = (int)(new.y / CELL_SIZE);
		if (is_walkable(g->map[new_map.y][new_map.x]))
		{
			g->p.pix.y = new.y;
			g->p.pix.x = new.x;
			g->moved = true;
		}
	}
}

/*
	Moves player backward taking into consideration
	the current player angle
*/
void	backward( t_game *g )
{
	t_vecd	new;
	t_vec	new_map;

	if (g->key.down == true)
	{
		new.x = g->p.pix.x - g->p.pdir.x * 2;
		new_map.x = (int)(new.x / CELL_SIZE);
		new.y = g->p.pix.y - g->p.pdir.y * 2;
		new_map.y = (int)(new.y / CELL_SIZE);
		if (is_walkable(g->map[new_map.y][new_map.x]))
		{
			g->p.pix.y = new.y;
			g->p.pix.x = new.x;
			g->moved = true;
		}
	}
}

/*
	Changes the player angle anti-clockwise
	and recalculates pdx and pdy for
	forward/backward movement
*/
void	left( t_game *g )
{
	double old_pdir_x;
	double old_plane_x;

	if (g->key.left == true)
	{
		old_pdir_x = g->p.pdir.x;
		g->p.pdir.x = g->p.pdir.x * cos(g->sens) - g->p.pdir.y * sin(g->sens);
		g->p.pdir.y = old_pdir_x * sin(g->sens) + g->p.pdir.y * cos(g->sens);
		old_plane_x = g->p.plane.x;
		g->p.plane.x = g->p.plane.x * cos(g->sens) - g->p.plane.y * sin(g->sens);
		g->p.plane.y = old_plane_x * sin(g->sens) + g->p.plane.y * cos(g->sens);
		g->moved = true;
	}
}

/*
	Changes the player angle clockwise
	and recalculates pdx and pdy for
	forward/backward movement
*/
void	right( t_game *g )
{
	double old_pdir_x;
	double old_plane_x;

	if (g->key.right == true)
	{
		old_pdir_x = g->p.pdir.x;
		g->p.pdir.x = g->p.pdir.x * cos(-g->sens) - g->p.pdir.y * sin(-g->sens);
		g->p.pdir.y = old_pdir_x * sin(-g->sens) + g->p.pdir.y * cos(-g->sens);
		old_plane_x = g->p.plane.x;
		g->p.plane.x = g->p.plane.x * cos(-g->sens) - g->p.plane.y * sin(-g->sens);
		g->p.plane.y = old_plane_x * sin(-g->sens) + g->p.plane.y * cos(-g->sens);
		g->moved = true;
	}
}
 