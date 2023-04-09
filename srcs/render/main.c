/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:11:56 by hwong             #+#    #+#             */
/*   Updated: 2023/04/09 12:06:19 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_init( t_game *game )
{
	// game->mlx = mlx_init();
	// game->winsize.x = 1920;
	// game->winsize.y = 1080;
	// game->win = mlx_new_window(game->mlx, game->winsize.x,
	// 		game->winsize.y, "cub3D");
	game->p.found = 0;
	game->p.y = 0;
	game->p.x = 0;
	game->p.dir = 0;
	game->leak = 0;
	game->msize.y = 0;
	game->msize.x = 0;
}

int	main( int ac, char **av )
{
	t_game	game;

	if (ac != 2)
		return (write(2, "Error: Invalid arguments\n", 25));
	game_init(&game);
	if (checks(av[1], &game))
		return (write(2, ": Invalid file\n", 15));

	// mlx_key_hook(game.win, move, &game);
	// mlx_hook(game.win, 17, (1L << 0), endgame, &game);
	// mlx_loop_hook(game.mlx, refresh, &game);
	// mlx_loop(game.mlx);
	free_tab(game.map);
	//system("leaks cub3D");
	return (0);
}
