/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:11:45 by hwong             #+#    #+#             */
/*   Updated: 2023/04/08 02:29:32 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	flood_recurse( int y, int x, t_game *game, char **map )
{
	if (game->leak > 0)
		return ;
	if (y <= 0 || x <= 0 || y >= game->msize.y || x >= ft_slen(map[y]))
	{
		game->leak = 1;
		return ;
	}
	if (map[y][x] == '1')
		return ;
	if (map[y][x] == 'v')
		return ;
	map[y][x] = 'v';
	flood_recurse(y - 1, x, game, map);
	flood_recurse(y + 1, x, game, map);
	flood_recurse(y, x - 1, game, map);
	flood_recurse(y, x + 1, game, map);
}

/*
	Do stupid shit to conform to norminette
*/
// static void	init_iter( int y, int x, t_vec *xy, t_queue **q )
// {
// 	xy->x = x;
// 	xy->y = y;
// 	*q = init_queue();
// }

// static void	flood_iter( int y, int x, t_game *game, char **map )
// {
// 	t_vec	xy;
// 	t_queue	*q;

// 	game->leak = 0;
// 	init_iter(y, x, &xy, &q);
// 	enqueue(q, xy);
// 	while (!is_q_empty(q))
// 	{
// 		xy = dequeue(q);
// 		if (xy.y <= 0 || xy.x <= 0
// 			|| xy.y >= game->msize.y || xy.x >= ft_slen(map[xy.y]))
// 		{
// 			game->leak = 1;
// 			break ;
// 		}
// 		if (map[xy.y][xy.x] == '1' || map[xy.y][xy.x] == 'v')
// 			continue ;
// 		map[xy.y][xy.x] = 'v';
// 		enqueue(q, (t_vec){xy.x, xy.y - 1});
// 		enqueue(q, (t_vec){xy.x, xy.y + 1});
// 		enqueue(q, (t_vec){xy.x - 1, xy.y});
// 		enqueue(q, (t_vec){xy.x + 1, xy.y});
// 	}
// 	free_queue(q);
// }

static char	**copy_tab( char **tab )
{
	char	**copy;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
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
			if (game->map[game->player.y][game->player.x] == 'N'
				|| game->map[game->player.y][game->player.x] == 'S'
				|| game->map[game->player.y][game->player.x] == 'W'
				|| game->map[game->player.y][game->player.x] == 'E')
				break ;
			game->player.x++;
		}
		game->player.y++;
	}
	printf("Making a copy of the map\n");
	copy = copy_tab(game->map);
	printf("Flooding map\n");
	flood_recurse(game->player.y, game->player.x, game, copy);
	// flood_iter(game->player.y, game->player.x, game, copy);
	free_tab(copy);
}
