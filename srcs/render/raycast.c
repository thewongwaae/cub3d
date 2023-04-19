/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:41:04 by hwong             #+#    #+#             */
/*   Updated: 2023/04/19 11:21:49 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_steps( int dx, int dy )
{
	if (abs(dx) > abs(dy))
		return (abs(dx));
	return (abs(dy));
}

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

static t_vec	get_intersect( t_game *g, float angle )
{
	float	dx;
	float	dy;
	float	x;
	float	y;
	t_vec	map;

	dx = cos(angle);
	dy = -sin(angle);
	x = g->p.pix_x;
	y = g->p.pix_y;
	while (1)
	{
		x += dx;
		y += dy;
		map.x = (int)(x / CELL_SIZE);
		map.y = (int)(y / CELL_SIZE);
		if (map.x < 0 || map.y < 0 || map.x >= g->msize.x
			|| map.y >= g->msize.y)
			break ;
		if (!is_walkable(g->map[map.y][map.x]))
			break ;
	}
	return ((t_vec){.x = x, .y = y});
}

void	raycast( t_vec player, t_game *game, int color )
{
	float	fov;
	float	step_angle;
	int		i;
	float	angle;
	t_vec	intersect;

	fov = M_PI / 3;
	step_angle = fov / 60;
	i = -1;
	while (++i < 60)
	{
		angle = game->p.pa - fov / 2 + i * step_angle;
		intersect = get_intersect(game, angle);
		draw_line(player, intersect, game->p.img, color);
	}
}
