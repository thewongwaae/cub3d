#include "cub3d.h"

void	set_current_tex( t_game *g, t_vec step )
{
	if (g->ray.hit == 0) //horizontal
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

double	calculate_dist( t_game *g )
{
	double dist;

	if (g->ray.hit == 0)
		dist = g->p.pix_x + g->ray.perp_dist * (g->ray.dir.y * CELL_SIZE);
	else
		dist = g->p.pix_y + g->ray.perp_dist * (g->ray.dir.x * CELL_SIZE);

	dist -= floor(dist); //what happens if its just this?
	return (dist);
}

void	draw_texture( t_game *g )
{
	char 		*tex_pixel;
	double		dist;
	t_vec		tex_coord;
	t_vec		to_draw;

	dist = calculate_dist(g);
	to_draw.x = g->ray.line[0].x;
	to_draw.y = g->ray.line[0].y;
	while (to_draw.y++ < g->ray.line[1].y)
	{
		
	}

}