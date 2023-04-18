/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:41:04 by hwong             #+#    #+#             */
/*   Updated: 2023/04/18 18:55:09 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_steps( int dx, int dy )
{
	if (abs(dx) > abs(dy))
		return (abs(dx));
	return (abs(dy));
}

void	draw_line( t_vec p1, t_vec p2, t_img img, int color )
{
	int		dx;
	int		dy;
	int		steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
	int		i;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	steps = get_steps(dx, dy);
	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;
	x = (float)p1.x;
	y = (float)p1.y;
	i = -1;
	while (++i <= steps)
	{
		my_pp(img, roundf(x), roundf(y), color);
		x += x_inc;
		y += y_inc;
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
		printf("%f\n", angle);
		intersect = get_intersect(game, angle);
		draw_line(player, intersect, game->p.img, color);
	}
}
