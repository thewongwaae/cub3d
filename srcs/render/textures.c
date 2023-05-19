/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnorazma <nnorazma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:12:52 by nnorazma          #+#    #+#             */
/*   Updated: 2023/05/19 17:32:02 by nnorazma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_current_tex( t_game *g, t_vec step )
{
	if (g->ray.hit == 0)
	{
		if (step.x == 1)
			g->current_tex = &(g->tex->east);
		else
			g->current_tex = &(g->tex->west);
	}
	else
	{
		if (step.y == 1)
			g->current_tex = &(g->tex->north);
		else
			g->current_tex = &(g->tex->south);
	}
}

static double	get_wall_hit( t_game *g )
{
	double	hit;

	if (g->ray.hit == 0)
		hit = g->p.pix.y + g->ray.perp_dist * (g->ray.dir.y * CELL_SIZE);
	else
		hit = g->p.pix.x + g->ray.perp_dist * (g->ray.dir.x * CELL_SIZE);
	hit = (((int)hit % CELL_SIZE) + (hit - floor(hit))) / CELL_SIZE;
	return (hit);
}

void	draw_texture( t_game *g )
{
	char		*tex_pixel;
	double		wall_hit;
	int			colour;
	t_vec		tex_coord;
	t_vec		to_draw;

	wall_hit = get_wall_hit(g);
	to_draw.x = g->ray.line[0].x;
	to_draw.y = g->ray.line[0].y - 1;
	while (++to_draw.y < g->ray.line[1].y)
	{
		tex_coord.x = (int)(wall_hit * g->current_tex->x);
		tex_coord.y = (int)(((double)(to_draw.y - g->ray.line[0].y)
					/ (double)g->ray.height) * g->current_tex->y);
		tex_pixel = g->current_tex->addr
			+ (tex_coord.y * g->current_tex->line_len
				+ tex_coord.x * (g->current_tex->bpp / 8));
		colour = *(unsigned int *)tex_pixel;
		my_pp(g->bg, to_draw.x, to_draw.y, colour);
	}
}
