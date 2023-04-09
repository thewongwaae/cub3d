/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:11:45 by hwong             #+#    #+#             */
/*   Updated: 2023/04/09 12:13:05 by hwong            ###   ########.fr       */
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
			game->leak = 1;
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
static void	init_flood( t_game *game )
{
	char	**copy;

	if (!game->p.found || !game->p.dir)
	{
		free_tab(game->map);
		return ;
	}
	copy = copy_tab(game->map);
	flood_iter(game->p.y, game->p.x, game, copy);
	free_tab(copy);
}

/*
	Find player position
	Start flood from player position
*/
void	check_map( t_game *g )
{
	while (g->map[g->p.y])
	{
		g->p.x = 0;
		while (g->map[g->p.y][g->p.x])
		{
			if (g->map[g->p.y][g->p.x] == 78 || g->map[g->p.y][g->p.x] == 83
				|| g->map[g->p.y][g->p.x] == 87 || g->map[g->p.y][g->p.x] == 69)
			{
				g->p.found = 1;
				g->p.dir = g->map[g->p.y][g->p.x];
				break ;
			}
			g->p.x++;
		}
		if (g->p.found)
			break ;
		g->p.y++;
	}
	init_flood(g);
}
