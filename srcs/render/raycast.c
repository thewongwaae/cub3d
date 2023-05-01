/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:41:04 by hwong             #+#    #+#             */
/*   Updated: 2023/05/01 16:58:52 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Return which axis has smaller distance
	from player to wall
*/
static float	get_steps( float dx, float dy )
{
	if (fabsf(dx) > fabsf(dy))
		return ((float)fabsf(dx));
	return (fabsf(dy));
}

/*
	Draw a line from specified start point to end point
*/
static void	draw_line( t_vecf p1, t_vecf p2, t_img img, int color )
{
	t_vecf	d;
	t_vecf	inc;
	t_vecf	pixel;
	float	steps;
	int		i;

	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;
	steps = get_steps(d.x, d.y);
	inc.x = d.x / steps;
	inc.y = d.y / steps;
	pixel.x = p1.x;
	pixel.y = p1.y;
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
static t_vecf	get_intersect( t_game *g, float angle )
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
	return ((t_vecf){.x = p.x, .y = p.y});
}

static void	hit_block( t_vec *its, t_vecf block )
{
	t_vec	cell;

	cell.x = roundf(block.x / CELL_SIZE);
	cell.y = roundf(block.y / CELL_SIZE);
	*its = (t_vec){.x = cell.x, .y = cell.y};
}

/*
	Cast rays from center of player character
	Note: its ~ intersect
*/
void	raycast( t_vecf player, t_game *g, int color )
{
	int		i;
	float	angle;
	t_vecf	its;
	float	dist;

	g->p.dist = INT32_MAX;
	i = -1;
	while (++i < g->fovdeg)
	{
		angle = g->p.pa - deg_to_rad(g->fovdeg) / 2 + (float)i
			* deg_to_rad(g->fovdeg) / (float)(g->fovdeg - 1);
		its = get_intersect(g, angle);
		dist = get_dist((t_vecf){.x = g->p.pix_x, .y = g->p.pix_y},
			its);
		if ((int)dist < g->p.dist)
		{
			hit_block(&g->p.its, its);
			g->p.dist = (int)dist;
		}
		if (i == 0 || i == g->fovdeg - 1)
			draw_line(player, its, g->p.img, color);
		cast_3d(g, dist, i, angle);
	}
}

/*
	float lineH = (mapS * 320)/dist; //320 is new 3d screen height, mapS = cellsize
	if (lineH >320)
		lineH = 320;  //maximum wall height

	float lineOff = 160 - lineH / 2; //offset 3d lines to middle of screen

	//every ray (i) is ~8pix wide
*/