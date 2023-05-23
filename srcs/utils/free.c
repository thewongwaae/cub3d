/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnorazma <nnorazma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:12:20 by hwong             #+#    #+#             */
/*   Updated: 2023/05/23 12:37:15 by nnorazma         ###   ########.fr       */
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
	mlx_destroy_window(game->mlx, game->win);
	free(game->mlx);
	exit(0);
}
