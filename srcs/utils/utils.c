#include "cub3d.h"

int	get_center( int start, int end )
{
	return (end - ((end - start) / 2));
}

float	deg_to_rad( int a )
{
	return (a * M_PI / 180);
}
