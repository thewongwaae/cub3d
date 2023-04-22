#include "cub3d.h"

/*
	a twist on Pythagorus
*/
int	get_dist( t_vec p1, t_vec p2 )
{
	t_vec	d;

	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;
	return (sqrtf(d.x * d.x + d.y * d.y));
}
