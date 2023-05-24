/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnorazma <nnorazma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:22:36 by nnorazma          #+#    #+#             */
/*   Updated: 2023/05/24 14:39:09 by nnorazma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_perp_dist( t_game *g )
{
	if (g->ray.hit == 0)
		g->ray.perp_dist = g->ray.side.x - g->ray.delta.x;
	else
		g->ray.perp_dist = g->ray.side.y - g->ray.delta.y;
}

void	set_door( t_game *g, t_vec map_pos )
{
	g->door.dist = g->ray.perp_dist;
	if (map_pos.x == g->door.pos.x
		&& map_pos.y == g->door.pos.y)
		return ;
	g->door.pos = map_pos;
}

void	open_door( t_game *g )
{
	if (g->door.dist == INT16_MAX)
		return ;
	if (g->door.dist < 1)
	{
		if (g->map[g->door.pos.y][g->door.pos.x] == '2')
		{
			g->map[g->door.pos.y][g->door.pos.x] = '3';
			g->boom = true;
			g->audio[OPEN].play = true;
		}
		else if (g->map[g->door.pos.y][g->door.pos.x] == '3')
		{
			g->map[g->door.pos.y][g->door.pos.x] = '2';
			g->boom = true;
			g->audio[CLOSE].play = true;
		}
		render_minimap(g);
		g->moved = true;
	}
}
