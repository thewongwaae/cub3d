/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:41:04 by hwong             #+#    #+#             */
/*   Updated: 2023/04/22 17:11:40 by hwong            ###   ########.fr       */
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
	}
	return ((t_vec){.x = p.x, .y = p.y});
}

/*
	Cast rays from center of player character
*/
void	raycast( t_vec player, t_game *game, int color )
{
	float	fov;
	float	step_angle;
	int		i;
	float	angle;
	t_vec	intersect;

	fov = deg_to_rad(game->fovdeg);
	step_angle = fov / game->fovdeg;
	i = -1;
	while (++i < game->fovdeg)
	{
		angle = game->p.pa - fov / 2 + i * step_angle;
		intersect = get_intersect(game, angle);
		draw_line(player, intersect, game->p.img, color);
	}
}
