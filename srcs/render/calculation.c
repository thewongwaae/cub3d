#include "cub3d.h"

/*
	a twist on Pythagorus
*/
float	get_dist( t_vecf p1, t_vecf p2 )
{
	t_vec	d;

	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;
	return (sqrt(d.x * d.x + d.y * d.y));
}

/*
	need handle for when intersect falls short or
	passes through wall due to step size
*/
static t_vecf correct_intersect(t_vecf p, t_vec map)
{
    t_vecf edge;
    float dist_top, dist_bottom, dist_left, dist_right, min_dist;

    dist_top = fabsf(p.y - (map.y * CELL_SIZE));
    dist_bottom = fabsf(p.y - ((map.y + 1) * CELL_SIZE));
    dist_left = fabsf(p.x - (map.x * CELL_SIZE));
    dist_right = fabsf(p.x - ((map.x + 1) * CELL_SIZE));
    min_dist = fminf(fminf(dist_top, dist_bottom), fminf(dist_left, dist_right));
    if (min_dist == dist_top)
    {
        edge.x = p.x;
        edge.y = map.y * CELL_SIZE;
    }
    else if (min_dist == dist_bottom)
    {
        edge.x = p.x;
        edge.y = (map.y + 1) * CELL_SIZE;
    }
    else if (min_dist == dist_left)
    {
        edge.x = map.x * CELL_SIZE;
        edge.y = p.y;
    }
    else
    {
        edge.x = (map.x + 1) * CELL_SIZE;
        edge.y = p.y;
    }
    return edge;
}

t_vecf	get_intersect( t_game *g, float angle )
{
	t_vecf	d;
	t_vecf	p;
	t_vec	map;

	d.x = cos(angle) * 0.2;
	d.y = -sin(angle) * 0.2;
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
			p = correct_intersect(p, map);
			break ;
		}
		if (g->map[map.y][map.x] == '3')
			g->p.its = (t_vec){.x = map.x, .y = map.y};
	}
	return ((t_vecf){.x = p.x, .y = p.y});
}
