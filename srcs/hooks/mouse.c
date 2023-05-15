#include "cub3d.h"

static void	change_angle( int dx, t_game *g )
{
	double	old_pdir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = dx * 0.01;
	old_pdir_x = g->p.pdir.x;
	g->p.pdir.x = g->p.pdir.x * cos(rot_speed) - g->p.pdir.y * sin(rot_speed);
	g->p.pdir.y = old_pdir_x * sin(rot_speed) + g->p.pdir.y * cos(rot_speed);
	old_plane_x = g->p.plane.x;
	g->p.plane.x = g->p.plane.x * cos(rot_speed) - g->p.plane.y * sin(rot_speed);
	g->p.plane.y = old_plane_x * sin(rot_speed) + g->p.plane.y * cos(rot_speed);
}

/*
	Changes player angle value based on mouse-x
*/
int	mouse_hook( int x, int y, t_game *g )
{
	static int	prev_x = -1;
	int			dx;

	(void) y;
	if (prev_x == -1)
		prev_x = x;
	dx = x - prev_x;
	if (abs(dx) > 5)
	{
		change_angle(dx, g);
		g->moved = true;
		prev_x = x;
	}
	return (0);
}
