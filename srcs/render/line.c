#include "cub3d.h"

static int	get_steps( int dx, int dy )
{
	if (abs(dx) > abs(dy))
		return (abs(dx));
	return (abs(dy));
}

void	draw_line( t_vec p1, t_vec p2, t_img img, int color )
{
	int		dx;
	int		dy;
	int		steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
	int		i;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	steps = get_steps(dx, dy);
	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;
	x = (float)p1.x;
	y = (float)p1.y;
	i = -1;
	while (++i <= steps)
	{
		my_pp(img, roundf(x), roundf(y), color);
		x += x_inc;
		y += y_inc;
	}
}
