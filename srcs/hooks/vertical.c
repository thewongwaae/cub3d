/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:28:59 by hwong             #+#    #+#             */
/*   Updated: 2023/05/24 15:29:00 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			g->p.map_pos.y = new_map.y;
			g->p.map_pos.x = new_map.x;
			g->moved = true;
			return ;
		}
		g->audio[COLLIDE].play = true;
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
			g->p.map_pos.y = new_map.y;
			g->p.map_pos.x = new_map.x;
			g->moved = true;
			return ;
		}
		g->audio[COLLIDE].play = true;
	}
}
