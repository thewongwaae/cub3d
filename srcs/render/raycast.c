/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:41:04 by hwong             #+#    #+#             */
/*   Updated: 2023/05/02 20:19:01 by hwong            ###   ########.fr       */
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
	while (++i < g->winsize.x)
	{
		angle = g->p.pa - deg_to_rad(g->fovdeg) / 2 + (float)i
			* deg_to_rad(g->fovdeg) / g->winsize.x;
		its = get_intersect(g, angle);
		dist = get_dist((t_vecf){.x = g->p.pix_x, .y = g->p.pix_y},
			its);
		if ((int)dist < g->p.dist)
		{
			hit_block(&g->p.its, its);
			g->p.dist = (int)dist;
		}
		if (i == 0 || i == g->winsize.x - 1)
			draw_line(player, its, g->p.img, color);
		cast_3d(g, dist, i, angle);
	}
}
