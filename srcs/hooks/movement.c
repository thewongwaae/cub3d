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
		new.x = g->p.pix_x + (g->p.pdir.x * (3 + 0.1));
		new_map.x = (int)(new.x / CELL_SIZE);
		new.y = g->p.pix_y + (g->p.pdir.y * (3 + 0.1));
		new_map.y = (int)(new.y / CELL_SIZE);
		if (is_walkable(g->map[new_map.x][g->p.map_pos.y]))
			g->p.pix_x = new.x;
		if (is_walkable(g->map[g->p.map_pos.x][new_map.y]))
			g->p.pix_y = new.y;
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
		new.x = g->p.pix_x - (g->p.pdir.x * (3 + 0.1));
		new_map.x = (int)(new.x / CELL_SIZE);
		new.y = g->p.pix_y - (g->p.pdir.y * (3 + 0.1));
		new_map.y = (int)(new.y / CELL_SIZE);
		if (is_walkable(g->map[new_map.x][g->p.map_pos.y]))
			g->p.pix_x = new.x;
		if (is_walkable(g->map[g->p.map_pos.x][new_map.y]))
			g->p.pix_y = new.y;
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
	double rot_speed = 0.05;

	old_pdir_x = g->p.pdir.x;
	g->p.pdir.x = g->p.pdir.x * cos(-rot_speed) - g->p.pdir.y * sin(-rot_speed);
	g->p.pdir.y = old_pdir_x * sin(-rot_speed) + g->p.pdir.y * cos(-rot_speed);
	old_plane_x = g->p.plane.x;
	g->p.plane.x = g->p.plane.x * cos(-rot_speed) - g->p.plane.y * sin(-rot_speed);
	g->p.plane.y = old_plane_x * sin(-rot_speed) + g->p.plane.y * cos(-rot_speed);
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
	double rot_speed = 0.05;

	old_pdir_x = g->p.pdir.x;
	g->p.pdir.x = g->p.pdir.x * cos(rot_speed) - g->p.pdir.y * sin(rot_speed);
	g->p.pdir.y = old_pdir_x * sin(rot_speed) + g->p.pdir.y * cos(rot_speed);
	old_plane_x = g->p.plane.x;
	g->p.plane.x = g->p.plane.x * cos(rot_speed) - g->p.plane.y * sin(rot_speed);
	g->p.plane.y = old_plane_x * sin(rot_speed) + g->p.plane.y * cos(rot_speed);
}
