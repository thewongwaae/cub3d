#include "cub3d.h"

void	ft_free( char *var )
{
	if (var)
		free(var);
}

void	free_tab( char **tab )
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}
