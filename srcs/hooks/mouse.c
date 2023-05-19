/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:13:13 by hwong             #+#    #+#             */
/*   Updated: 2023/05/19 17:13:45 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	change_angle( int dx, t_game *g )
{
	double	old_pdir_x;
	double	old_plane_x;
	double	rot_spd;

	rot_spd = dx * 0.005;
	old_pdir_x = g->p.pdir.x;
	g->p.pdir.x = g->p.pdir.x * cos(rot_spd) - g->p.pdir.y * sin(rot_spd);
	g->p.pdir.y = old_pdir_x * sin(rot_spd) + g->p.pdir.y * cos(rot_spd);
	old_plane_x = g->p.plane.x;
	g->p.plane.x = g->p.plane.x * cos(rot_spd) - g->p.plane.y * sin(rot_spd);
	g->p.plane.y = old_plane_x * sin(rot_spd) + g->p.plane.y * cos(rot_spd);
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
