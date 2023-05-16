/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnorazma <nnorazma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:41:04 by hwong             #+#    #+#             */
/*   Updated: 2023/05/16 13:34:56 by nnorazma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_delta( t_game *g )
{
	if (g->ray.dir.x == 0)
		g->ray.delta.x = 1e30;
	else
		g->ray.delta.x = fabs(1.0 / g->ray.dir.x);
	if (g->ray.dir.y == 0)
		g->ray.delta.y = 1e30;
	else
		g->ray.delta.y = fabs(1.0 / g->ray.dir.y);	
}

static void	get_side( t_game *g, t_vec *step )
{
	if (g->ray.dir.x < 0)
	{
		step->x = -1;
		g->ray.side.x = g->ray.delta.x
			* ((g->p.pix_x / CELL_SIZE) - g->p.map_pos.x);
	}
	else
	{
		step->x = 1;
		g->ray.side.x = g->ray.delta.x
			* (g->p.map_pos.x + 1.0 - (g->p.pix_x / CELL_SIZE));
	}
	if (g->ray.dir.y < 0)
	{
		step->y = -1;
		g->ray.side.y = g->ray.delta.y
			* ((g->p.pix_y / CELL_SIZE) - g->p.map_pos.y);
	}
	else
	{
		step->y = 1;
		g->ray.side.y = g->ray.delta.y
			* (g->p.map_pos.y + 1.0 - (g->p.pix_y / CELL_SIZE));
	}
}

static void	get_perp_dist( t_game *g, t_vec step, t_vec map_pos )
{
	while (is_walkable(g->map[map_pos.y][map_pos.x]))
	{
		if (g->ray.side.x < g->ray.side.y)
		{
			g->ray.side.x += g->ray.delta.x;
			map_pos.x += step.x;
			g->ray.hit = 0;
		}
		else
		{
			g->ray.side.y += g->ray.delta.y;
			map_pos.y += step.y;
			g->ray.hit = 1;
		}
		g->hit = g->map[map_pos.y][map_pos.x];
	}
	if (g->ray.hit == 0)
		g->ray.perp_dist = g->ray.side.x - g->ray.delta.x;
	else if (g->ray.hit == 1)
		g->ray.perp_dist = g->ray.side.y - g->ray.delta.y;
}

/*
	sets coordinates of the ray lines to draw on screen
	line[0].y = top of line
	line[0].y = bottom of line

	if statement to prevent out of bounds,
	but is it necessary?
*/
static void set_line( t_game *g, int ray )
{
	g->ray.line[0].x = ray;
	g->ray.line[0].y = g->ray.height / -2 + g->winsize.y;
	g->ray.line[1].y = g->ray.height / 2 + g->winsize.y;
	if (g->ray.line[1].y >= g->winsize.y)
		g->ray.line[1].y = g->winsize.y;
}

// static void	draw_column( int ray, t_game *g )
// {
// 	double	offset;
// 	t_vecd	start;
// 	t_vecd	end;

// 	if (g->ray.height > (double)g->winsize.y)
// 		g->ray.height = (double)g->winsize.y;
// 	offset = ((double)g->winsize.y / 2.0) - g->ray.height / 2.0;
// 	start = (t_vecd){(double)ray, offset};
// 	end = (t_vecd){(double)ray, offset + g->ray.height};
// 	while(start.y <= end.y)
// 	{
// 		my_pp(g->bg, (int)(start.x), (int)(start.y), PURPLE);
// 		start.y += 1.0;
// 	}
// }

void	raycast( t_game *g )
{
	int		ray;
	double	camX;
	t_vec	step;

	ray = -1;
	while (++ray < g->winsize.x)
	{
		camX = 2.0 * ray / (double)g->winsize.x - 1.0;
		g->ray.dir.x = g->p.pdir.x - g->p.plane.x * camX;
		g->ray.dir.y = g->p.pdir.y - g->p.plane.y * camX;
		get_delta(g);
		get_side(g, &step);
		get_perp_dist(g, step, g->p.map_pos);
		g->ray.height = (int)(g->winsize.y / g->ray.perp_dist);
		set_line(g, ray);
		set_current_tex(g, step);
		draw_texture(g);
		// draw_column(ray, g);
	}
}
