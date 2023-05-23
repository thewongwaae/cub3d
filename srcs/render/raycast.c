/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:41:04 by hwong             #+#    #+#             */
/*   Updated: 2023/05/23 15:00:20 by hwong            ###   ########.fr       */
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
			* ((g->p.pix.x / CELL_SIZE) - g->p.map_pos.x);
	}
	else
	{
		step->x = 1;
		g->ray.side.x = g->ray.delta.x
			* (g->p.map_pos.x + 1.0 - (g->p.pix.x / CELL_SIZE));
	}
	if (g->ray.dir.y < 0)
	{
		step->y = -1;
		g->ray.side.y = g->ray.delta.y
			* ((g->p.pix.y / CELL_SIZE) - g->p.map_pos.y);
	}
	else
	{
		step->y = 1;
		g->ray.side.y = g->ray.delta.y
			* (g->p.map_pos.y + 1.0 - (g->p.pix.y / CELL_SIZE));
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
		if (!g->door.met && (g->hit == '2' || g->hit == '3'))
		{
			set_door(g, map_pos);
			g->door.met = true;
		}
	}
	calc_perp_dist(g);
}

/*
	sets coordinates of the ray lines to draw on screen
	line[0].y = top of line
	line[0].y = bottom of line

	if statement to prevent out of bounds,
	but is it necessary?
*/
static void	set_line( t_game *g, int ray )
{
	int	offset;

	offset = (WINSIZE_Y / 2) - (g->ray.height / 2);
	g->ray.line[0].x = ray;
	g->ray.line[0].y = offset;
	g->ray.line[1].y = g->ray.height + offset;
	if (g->ray.line[1].y >= WINSIZE_Y)
		g->ray.line[1].y = WINSIZE_Y;
}

void	raycast( t_game *g )
{
	int		ray;
	double	cam_x;
	t_vec	step;

	ray = -1;
	g->door.dist = INT16_MAX;
	g->door.met = false;
	while (++ray < WINSIZE_X)
	{
		cam_x = 2.0 * ray / (double)WINSIZE_X - 1.0;
		g->ray.dir.x = g->p.pdir.x - g->p.plane.x * cam_x;
		g->ray.dir.y = g->p.pdir.y - g->p.plane.y * cam_x;
		get_delta(g);
		get_side(g, &step);
		get_perp_dist(g, step, g->p.map_pos);
		g->ray.height = (int)(WINSIZE_Y / g->ray.perp_dist);
		set_line(g, ray);
		set_current_tex(g, step);
		draw_texture(g);
	}
}
