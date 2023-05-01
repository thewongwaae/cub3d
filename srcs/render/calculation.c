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
