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

static t_vecd correct_intersect(t_vecd p, double angle, t_vec map )
{
    t_vecd    edge;
    double    left;
    double    right;
    double    up;
    double    down;

    edge.x = p.x + 0.01 * cos(angle);
    edge.y = p.y + 0.01 * sin(angle);
    left = ((double)map.x * (double)CELL_SIZE);
    right = (((double)map.x + 1.0) * (double)CELL_SIZE);
    up = ((double)map.y * (double)CELL_SIZE);
    down = (((double)map.y + 1.0) * (double)CELL_SIZE);
    if (edge.x < left)
        edge.x = left;
    else if (edge.x > right)
        edge.x = right;
    if (edge.y < up)
        edge.y = up;
    else if (edge.y > down)
        edge.y = down;
    return (edge);
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
		p.x += d.x;
		p.y += d.y;
		map.x = (int)(p.x / CELL_SIZE);
		map.y = (int)(p.y / CELL_SIZE);
		if (!is_walkable(g->map[map.y][map.x]))
		{
			p = correct_intersect(p, angle, map);
			break ;
		}
		if (g->map[map.y][map.x] == '3')
			g->p.its = (t_vec){.x = map.x, .y = map.y};
	}
	return ((t_vecd){.x = p.x, .y = p.y});
}
