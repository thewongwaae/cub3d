/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:11:56 by hwong             #+#    #+#             */
/*   Updated: 2023/04/06 17:12:47 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_init( t_game *game )
{
	game->mlx = mlx_init();
	game->winsize.x = 1920;
	game->winsize.y = 1080;
	game->win = mlx_new_window(game->mlx, game->winsize.x,
			game->winsize.y, "cub3D");
	game->player.y = 0;
	game->player.x = 0;
	game->mapsize.y = 0;
	game->mapsize.x = 0;
}

// mlx_key_hook(game.win, move, &game);
// mlx_hook(game.win, 17, (1L << 0), endgame, &game);
// mlx_loop_hook(game.mlx, refresh, &game);
int	main( int ac, char **av )
{
	t_game	game;

	if (ac != 2)
		return (write(2, "Error: Invalid arguments\n", 25));
	game_init(&game);
	if (!checks(av[1], &game))
		return (write(2, ": Invalid map file\n", 24));
	mlx_loop(game.mlx);
	return (0);
}
