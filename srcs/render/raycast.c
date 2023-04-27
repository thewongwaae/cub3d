/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:41:04 by hwong             #+#    #+#             */
/*   Updated: 2023/04/27 17:37:33 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Return which axis has smaller distance
	from player to wall
*/
static int	get_steps( int dx, int dy )
{
	if (abs(dx) > abs(dy))
		return (abs(dx));
	return (abs(dy));
}

/*
	Draw a line from specified start point to end point
*/
static void	draw_line( t_vec p1, t_vec p2, t_img img, int color )
{
	t_vec	d;
	t_vecf	inc;
	t_vecf	pixel;
	int		steps;
	int		i;

	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;
	steps = get_steps(d.x, d.y);
	inc.x = d.x / (float)steps;
	inc.y = d.y / (float)steps;
	pixel.x = (float)p1.x;
	pixel.y = (float)p1.y;
	i = -1;
	while (++i <= steps)
	{
		my_pp(img, roundf(pixel.x), roundf(pixel.y), color);
		pixel.x += inc.x;
		pixel.y += inc.y;
	}
}

/*
	Calculate end point of ray if casted from player
	at specified angle
*/
static t_vec	get_intersect( t_game *g, float angle )
{
	t_vecf	d;
	t_vecf	p;
	t_vec	map;

	d.x = cos(angle);
	d.y = -sin(angle);
	p.x = g->p.pix_x;
	p.y = g->p.pix_y;
	while (1)
	{
		p.x += d.x;
		p.y += d.y;
		map.x = (int)(p.x / CELL_SIZE);
		map.y = (int)(p.y / CELL_SIZE);
		if (map.x < 0 || map.y < 0 || map.x >= g->msize.x
			|| map.y >= g->msize.y)
			break ;
		if (!is_walkable(g->map[map.y][map.x]))
			break ;
		if (g->map[map.y][map.x] == '3')
			g->p.its = (t_vec){.x = map.x, .y = map.y};
	}
	return ((t_vec){.x = p.x, .y = p.y});
}

static void	hit_door( t_vec *its, char **map, t_vec block )
{
	t_vec	cell;

	cell.x = (int)(block.x / CELL_SIZE);
	cell.y = (int)(block.y / CELL_SIZE);
	if (map[cell.y][cell.x] == '2'
		|| map[cell.y][cell.x] == '3')
		*its = (t_vec){.x = cell.x, .y = cell.y};
}

/*
	Cast rays from center of player character
	Note: its ~ intersect
*/
void	raycast( t_vec player, t_game *g, int color )
{
	float	step_angle;
	int		i;
	float	angle;
	t_vec	its;
	int		dist;

	step_angle = deg_to_rad(g->fovdeg) / g->fovdeg;
	g->p.dist = INT32_MAX;
	i = -1;
	while (++i < g->fovdeg)
	{
		angle = g->p.pa - deg_to_rad(g->fovdeg)
			/ 2 + i * step_angle;
		its = get_intersect(g, angle);
		dist = get_dist((t_vec){.x = g->p.pix_x, .y = g->p.pix_y},
			its);
		if (dist < g->p.dist)
		{
			hit_door(&g->p.its, g->map, its);
			g->p.dist = dist;
		}
		draw_line(player, its, g->p.img, color);

		//=====//
		cast_3d(g, dist, i);
		//=====//
	}
}

/*
	float lineH = (mapS * 320)/dist; //320 is new 3d screen height, mapS = cellsize
	if (lineH >320)
		lineH = 320;  //maximum wall height

	float lineOff = 160 - lineH / 2; //offset 3d lines to middle of screen

	//every ray (i) is ~8pix wide
*/