#include "cub3d.h"

void	seele_init( t_game *g )
{
	char	*seele = NULL;
	int		i;

	i = -1;
	while (++i < 118)
	{
		
	}
}

void	seele_ult( t_game *g )
{
	int	i;

	i = -1;
	while (++i < 118)
		mlx_put_image_to_window(g->mlx, g->win, g->seele[i], 0, 0);
	g->door = true;
}