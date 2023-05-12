#include "cub3d.h"

/*
	a twist on Pythagorus
*/
double	get_dist( t_vecd p1, t_vecd p2 )
{
	t_vecd	d;

	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;
	return (sqrt(d.x * d.x + d.y * d.y));
}

t_vecd	get_intersect( t_game *g, double angle )
{
	t_vecd	d;
	t_vecd	p;
	t_vec	map;

	d.x = cos(angle) * 0.1;
	d.y = -sin(angle) * 0.1;
	p.x = g->p.pix_x;
	p.y = g->p.pix_y;
	while (1)
	{
		map.x = (int)(p.x / CELL_SIZE);
		map.y = (int)(p.y / CELL_SIZE);
		if (!is_walkable(g->map[map.y][map.x]))
			break ;
		if (g->map[map.y][map.x] == '3')
			g->p.its = (t_vec){.x = map.x, .y = map.y};
		p.x += d.x;
		p.y += d.y;
	}
	return ((t_vecd){.x = p.x, .y = p.y});
}
