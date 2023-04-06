#include "cub3d.h"

static void	flood( int y, int x, t_game *game, char **map )
{
	if (game->leak != 0)
		return ;
	if (y < 0 || x < 0 || y >= game->mapsize.y || x >= ft_strlen(map[y]))
	{
		game->leak = 1;
		return ;
	}
	if (map[y][x] == '1')
		return ;
	if (map[y][x] == 'v')
		return ;
	map[y][x] = 'v';
	flood(y - 1, x, game, map);
	flood(y + 1, x, game, map);
	flood(y, x - 1, game, map);
	flood(y, x + 1, game, map);
}

static char	**copy_tab( char **tab )
{
	char	**copy;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	copy = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (tab[i])
	{
		copy[i] = ft_strdup(tab[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

/*
	Find player position
	Start flood from player position
*/
void	check_map( t_game *game )
{
	char	**copy;

	while (game->map[game->player.y])
	{
		while (game->map[game->player.y][game->player.x])
		{
			if (game->map[game->player.y][game->player.x] != 'N'
				|| game->map[game->player.y][game->player.x] != 'S'
				|| game->map[game->player.y][game->player.x] != 'W'
				|| game->map[game->player.y][game->player.x] != 'E')
				break ;
			game->player.x++;
		}
		game->player.y++;
	}
	copy = copy_tab(game->map);
	flood(game->player.y, game->player.x, game, copy);
	free_tab(copy);
}
