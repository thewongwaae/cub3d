/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:11:45 by hwong             #+#    #+#             */
/*   Updated: 2023/05/17 18:21:59 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Do stupid shit to conform to norminette
*/
static void	init_iter( int y, int x, t_vec *xy, t_queue **q )
{
	xy->x = x;
	xy->y = y;
	*q = init_queue();
}

/*
	Iterative flood implementation to prevent
	heap buffer overflow
*/
static void	flood_iter( int y, int x, t_game *game, char **map )
{
	t_vec	xy;
	t_queue	*q;

	init_iter(y, x, &xy, &q);
	enqueue(q, xy);
	while (!is_q_empty(q))
	{
		xy = dequeue(q);
		if (xy.y < 0 || xy.x < 0
			|| xy.y >= game->msize.y || xy.x >= ft_slen(map[xy.y]))
		{
			game->leak = true;
			break ;
		}
		if (map[xy.y][xy.x] == '1' || map[xy.y][xy.x] == 'v')
			continue ;
		map[xy.y][xy.x] = 'v';
		enqueue(q, (t_vec){xy.x, xy.y - 1});
		enqueue(q, (t_vec){xy.x, xy.y + 1});
		enqueue(q, (t_vec){xy.x - 1, xy.y});
		enqueue(q, (t_vec){xy.x + 1, xy.y});
	}
	free_queue(q);
}

/*
	Copy a 2D array into another
*/
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
	Even more stupid shit for norminette
*/
static int	init_flood( t_game *game )
{
	char	**copy;

	if (!game->p.found || !game->p.dir)
		return (0);
	copy = copy_tab(game->map);
	flood_iter(game->p.map_pos.y, game->p.map_pos.x, game, copy);
	free_tab(copy);
	return (0);
}

/*
	Find player position
	Start flood from player position
	If flood node goes out of bounds, found leak
*/
int	check_map( t_game *g )
{
	int	x;
	int	y;

	y = 0;
	while (g->map[y])
	{
		x = 0;
		while (g->map[y][x])
		{
			if (g->map[y][x] == 78 || g->map[y][x] == 83
				|| g->map[y][x] == 87 || g->map[y][x] == 69)
			{
				g->p.found++;
				g->p.map_pos = (t_vec){x, y};
				g->p.dir = g->map[y][x];
			}
			x++;
		}
		y++;
	}
	if (g->p.found != 1)
		return (write(2, "Error: More than 1 player", 26));
	init_flood(g);
	return (g->p.found);
}
