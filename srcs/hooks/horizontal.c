/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:28:56 by hwong             #+#    #+#             */
/*   Updated: 2023/05/24 15:30:01 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Changes the player angle anti-clockwise
	and recalculates pdx and pdy for
	forward/backward movement
*/
void	left( t_game *g )
{
	double	old_pdir_x;
	double	old_plane_x;

	if (g->key.left == true)
	{
		old_pdir_x = g->p.pdir.x;
		g->p.pdir.x = g->p.pdir.x * cos(g->sens) - g->p.pdir.y * sin(g->sens);
		g->p.pdir.y = old_pdir_x * sin(g->sens) + g->p.pdir.y * cos(g->sens);
		old_plane_x = g->p.plane.x;
		g->p.plane.x = g->p.plane.x * cos(g->sens)
			- g->p.plane.y * sin(g->sens);
		g->p.plane.y = old_plane_x * sin(g->sens) + g->p.plane.y * cos(g->sens);
		g->moved = true;
	}
}

void	strafe_left( t_game *g )
{
	t_vecd	new;
	t_vec	new_map;

	if (g->key.sleft == true)
	{
		new.x = g->p.pix.x - g->p.plane.x * 2;
		new_map.x = (int)(new.x / CELL_SIZE);
		new.y = g->p.pix.y - g->p.plane.y * 2;
		new_map.y = (int)(new.y / CELL_SIZE);
		if (is_walkable(g->map[new_map.y][new_map.x]))
		{
			g->p.pix.y = new.y;
			g->p.pix.x = new.x;
			g->p.map_pos.y = new_map.y;
			g->p.map_pos.x = new_map.x;
			g->moved = true;
			return ;
		}
		g->audio[COLLIDE].play = true;
	}
}

/*
	Changes the player angle clockwise
	and recalculates pdx and pdy for
	forward/backward movement
*/
void	right( t_game *g )
{
	double	old_pdir_x;
	double	old_plane_x;

	if (g->key.right == true)
	{
		old_pdir_x = g->p.pdir.x;
		g->p.pdir.x = g->p.pdir.x * cos(-g->sens) - g->p.pdir.y * sin(-g->sens);
		g->p.pdir.y = old_pdir_x * sin(-g->sens) + g->p.pdir.y * cos(-g->sens);
		old_plane_x = g->p.plane.x;
		g->p.plane.x = g->p.plane.x * cos(-g->sens)
			- g->p.plane.y * sin(-g->sens);
		g->p.plane.y = old_plane_x * sin(-g->sens)
			+ g->p.plane.y * cos(-g->sens);
		g->moved = true;
	}
}

void	strafe_right( t_game *g )
{
	t_vecd	new;
	t_vec	new_map;

	if (g->key.sright == true)
	{
		new.x = g->p.pix.x + g->p.plane.x * 2;
		new_map.x = (int)(new.x / CELL_SIZE);
		new.y = g->p.pix.y + g->p.plane.y * 2;
		new_map.y = (int)(new.y / CELL_SIZE);
		if (is_walkable(g->map[new_map.y][new_map.x]))
		{
			g->p.pix.y = new.y;
			g->p.pix.x = new.x;
			g->p.map_pos.y = new_map.y;
			g->p.map_pos.x = new_map.x;
			g->moved = true;
			return ;
		}
		g->audio[COLLIDE].play = true;
	}
}
