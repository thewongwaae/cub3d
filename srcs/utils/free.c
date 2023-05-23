/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnorazma <nnorazma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:12:20 by hwong             #+#    #+#             */
/*   Updated: 2023/05/23 18:33:40 by nnorazma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_free(tab[i]);
	free(tab);
}

int	endgame( t_game *game )
{
	free_tab(game->map);
	kill(0, SIGINT);
	mlx_destroy_window(game->mlx, game->win);
	free(game->mlx);
	exit(0);
}
