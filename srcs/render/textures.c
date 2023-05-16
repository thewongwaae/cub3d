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

static double	calculate_dist( t_game *g )
{
	double dist;

	if (g->ray.hit == 0)
		dist = g->p.pix_x + g->ray.perp_dist * (g->ray.dir.y * CELL_SIZE);
	else
		dist = g->p.pix_y + g->ray.perp_dist * (g->ray.dir.x * CELL_SIZE);

	dist = (((int)dist % CELL_SIZE) + (dist - floor(dist))) / CELL_SIZE; //what happens if its just this?
	return (dist);
}

void	draw_texture( t_game *g )
{
	char 		*tex_pixel;
	double		dist;
	int			colour;
	t_vec		tex_coord;
	t_vec		to_draw;

	dist = calculate_dist(g);
	to_draw.x = g->ray.line[0].x;
	to_draw.y = g->ray.line[0].y;
	while (to_draw.y++ < g->ray.line[1].y)
	{
		tex_coord.x = (int)(dist * g->current_tex->x); //does dist need typecast?
		tex_coord.y = (int)(((double)(to_draw.y - g->ray.line[0].y)
					/ (double)g->ray.height) * g->current_tex->y);
		tex_pixel = g->current_tex->addr
				+ (tex_coord.y * g->current_tex->line_len
				+ tex_coord.x * (g->current_tex->bpp / 8));
		colour = *(unsigned int *)tex_pixel;

		// if (to_draw.x % 80 == 0 && to_draw.y % 100 == 0)
		// 	printf("to_draw.x = %d\nto_draw.y = %d\ntex_coord.x = %d\ntex_coord.y = %d\n\n", to_draw.x, to_draw.y, tex_coord.x, tex_coord.y);

		my_pp(g->bg, to_draw.x, to_draw.y, colour);
	}

}