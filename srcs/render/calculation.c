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

/*
	need handle for when intersect falls short or
	passes through wall due to step size
*/
// static t_vecd correct_intersect(t_vecd p, t_vec map)
// {
//     t_vecd edge;
//     double dist_top, dist_bottom, dist_left, dist_right, min_dist;

//     dist_top = fabs(p.y - (map.y * CELL_SIZE));
//     dist_bottom = fabs(p.y - ((map.y + 1) * CELL_SIZE));
//     dist_left = fabs(p.x - (map.x * CELL_SIZE));
//     dist_right = fabs(p.x - ((map.x + 1) * CELL_SIZE));
//     min_dist = fmin(fmin(dist_top, dist_bottom), fmin(dist_left, dist_right));
//     if (min_dist == dist_top)
//     {
//         edge.x = p.x;
//         edge.y = map.y * CELL_SIZE;
//     }
//     else if (min_dist == dist_bottom)
//     {
//         edge.x = p.x;
//         edge.y = (map.y + 1) * CELL_SIZE;
//     }
//     else if (min_dist == dist_left)
//     {
//         edge.x = map.x * CELL_SIZE;
//         edge.y = p.y;
//     }
//     else
//     {
//         edge.x = (map.x + 1) * CELL_SIZE;
//         edge.y = p.y;
//     }
//     return (edge);
// }

static t_vecd correct_intersect(t_vecd p, double angle, t_vec map )
{
    t_vecd edge;
    double step_size = 0.01;

    edge.x = p.x + step_size * cos(angle);
    edge.y = p.y + step_size * sin(angle);
    if (edge.x < map.x * CELL_SIZE)
        edge.x = map.x * CELL_SIZE;
    else if (edge.x > (map.x + 1) * CELL_SIZE)
        edge.x = (map.x + 1) * CELL_SIZE;
    if (edge.y < map.y * CELL_SIZE)
        edge.y = map.y * CELL_SIZE;
    else if (edge.y > (map.y + 1) * CELL_SIZE)
        edge.y = (map.y + 1) * CELL_SIZE;
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
