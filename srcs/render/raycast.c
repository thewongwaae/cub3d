/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:41:04 by hwong             #+#    #+#             */
/*   Updated: 2023/05/03 19:18:02 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Return which axis has smaller distance
	from player to wall
*/
static double	get_steps( double dx, double dy )
{
	if (fabs(dx) > fabs(dy))
		return (fabs(dx));
	return (fabs(dy));
}

/*
	Draw a line from specified start point to end point
*/
static void	draw_line( t_vecd p1, t_vecd p2, t_img img, int color )
{
	t_vecd	d;
	t_vecd	inc;
	t_vecd	pixel;
	double	steps;
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

static void	hit_block( t_vec *its, t_vecd block )
{
	t_vec	cell;

	cell.x = round(block.x / CELL_SIZE);
	cell.y = round(block.y / CELL_SIZE);
	*its = (t_vec){.x = cell.x, .y = cell.y};
}

/*
	Cast rays from center of player character
	Note: its ~ intersect
*/
void	raycast( t_vecd player, t_game *g, int color )
{
	int		i;
	double	angle;
	t_vecd	its;
	double	dist;

	g->p.dist = INT32_MAX;
	i = -1;
	while (++i < g->winsize.x)
	{
		angle = g->p.pa - deg_to_rad(g->fovdeg) / 2.0 + (double)i
			* deg_to_rad(g->fovdeg) / (double)g->winsize.x;
		its = get_intersect(g, angle);
		dist = get_dist((t_vecd){.x = g->p.pix_x, .y = g->p.pix_y},
			its);
		if (dist < g->p.dist)
		{
			hit_block(&g->p.its, its);
			g->p.dist = dist;
		}
		if (i == g->winsize.x / 2)
			draw_line(player, its, g->p.img, color);
		cast_3d(g, dist, i, angle);
	}
}
